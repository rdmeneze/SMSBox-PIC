
#include "WinService.h"
#include <Application.h>
#include "tcp_ip.h"
#include "Register.h"
#include "ado_db.H"

using namespace std;
//[6382>]

//------------------------------------------------------------------------------------------------------------------------

//[11_05_2010<]
LogFile						*	Application::pLog = NULL;
//[11_05_2010>]
WORD								Application::IdApp;
WORD								Application::IdTypeApp;
HANDLE							Application::EventThreadReady;
CStdString					Application::sVosProxyHost;
CStdString					Application::sMachineName[];
CStdString					Application::sHostName;
unsigned short			Application::usVosProxyPort;
bool								Application::bCloseLogFiles = false;
tcp_ip_interface *	Application::VosProxy;
CStdString          Application::sVersion;

//------------------------------------------------------------------------------------------------------------------------

int Application::Start()
{
  Register::Read();

  // Carrega a DLL de Winsock2
  if( !LoadWinSock2() )
  {
	  Log("Error Loading Winsock 2 library");
	  return -1;
  }

  // Iniciliza interface COM
  ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
  
	// Inicializa ponteiro da classe de log com a configuracao do diretorio de destino de log
	// lido do arquivo de inicializacao
	pLog = new LogFile("Log.txt", 0, Register::BasePathLog, true);

	Log("");
	Log("Starting...");

	if( ReadInfoFromDataBase() )
		return -1;

	// Reabre o arquivo de log de acordo com o configurado no banco de dados
	pLog->CloseFile();
	delete pLog;
  pLog = new LogFile("Log", Register::LogLevel, Register::BasePathLog, true, true);

	EventThreadReady = CreateEvent (0, FALSE, FALSE, NULL);
	
	ReportServiceStatus(SERVICE_STOP_PENDING, 1000, 5000);

	// Cria o objeto tcp/ip de conexao com o VosProxy
	VosProxy = new tcp_ip((LPCSTR)sVosProxyHost, usVosProxyPort);

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadDelLogFiles, NULL, 0, NULL);

  ReadVersion( );

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------

int Application::ReadInfoFromDataBase()
{
	int iRet, rc, i;
	CStdString sQuery;
	sql_db *db_obj = NULL;

	try
	{
		db_obj = new ado_db();

		iRet = db_obj->Open(	(LPCSTR)Register::sConnectionString,
                          (LPCSTR)Register::sDataSourceName,
													(LPCSTR)Register::sDataBase,
													(LPCSTR)Register::sUser,
													(LPCSTR)Register::sPassword);
		if( iRet )
		{
			Log(db_obj->GetLastError());
			return -1;
		}

		for(i = 0; i < 3; i++)
		{
      sHostName = sMachineName[i];

      sQuery.Format("EXEC sp_UnPbxGetInfoApplication '%s','%s'", SERVICE_NAME, (LPCSTR)sHostName);

			Log((LPCSTR)sQuery);

			rc = db_obj->Query( (LPCSTR)sQuery );

			if( rc < 0 )
			{
				Log(db_obj->GetLastError());
        db_obj->Close();
        delete db_obj;
				return -1;
			}

			IdApp			=	atoi(	db_obj->GetField(0,0) );
			IdTypeApp	=	atoi(	db_obj->GetField(0,1) );

			if( IdApp <= 0 || IdTypeApp <= 0 )
				continue;
			else
				break;
		}

		if( IdApp <= 0 || IdTypeApp <= 0 )
		{
			Log("Invalid Application Id for %s in Database...", SERVICE_NAME);
      db_obj->Close();
      delete db_obj;
			return -1;
		}

		Register::LogLevel	=	atoi(	db_obj->GetField(0,5));
		strcpy(Register::BasePathLog,	db_obj->GetField(0,6));

		// Cria o path para logs lido do banco de dados
    MakePath(Register::BasePathLog);

		Register::NumberOfDaysToKeepLogs = atoi( db_obj->GetField(0,11) );

		if( Register::NumberOfDaysToKeepLogs <= 1 )
		{
			Register::NumberOfDaysToKeepLogs = 2;
		}

		// Le a configuracao do Vosproxy
		sQuery.Format("EXEC Sp_TSysProcessor");

		Log( (LPCSTR)sQuery);

		rc = db_obj->Query( (LPCSTR)sQuery );
		if( rc < 0 )
		{
			Log(db_obj->GetLastError());
      db_obj->Close();
      delete db_obj;
			return -1;
		}

		sVosProxyHost		=	db_obj->GetField(0,0);
		usVosProxyPort	= atoi(	db_obj->GetField(0,1));

		Log("");
		Log("App Name:" SERVICE_NAME  );
		Log("App Type:  %d",                  IdTypeApp                       );
		Log("App Id:    %d",                  IdApp                           );
		Log("Log Level: %d",                  Register::LogLevel              );
		Log("Log Path:  %s",                  Register::BasePathLog           );
    Log("Log DaysToKeepLogs:  %d",        Register::NumberOfDaysToKeepLogs);
    Log("Log HourDelLogFiles:  %d",       Register::HourDelLogFiles       );
		Log("VosProxy Host: %s",              (LPCSTR)sVosProxyHost           );
		Log("VosProxy Port: %d",              usVosProxyPort                  );
    Log("WordSpotting Server: %s",        (LPCSTR)Register::WordSpottingConfiguration.szServerHost  );
    Log("WordSpotting GrammarFile: %s",   (LPCSTR)Register::WordSpottingConfiguration.szGrammarFile );
    Log("WordSpotting Lang: %s",          (LPCSTR)Register::WordSpottingConfiguration.szLang        );
    Log("WordSpotting ConfidenseLevel: %d", Register::WordSpottingConfiguration.ConfidenseLevel     );
		Log("");

    db_obj->Close();
    delete db_obj;

		return 0;
	}
	catch(...)
	{
		Log("EXCEPTION: Application::ReadInfoFromDataBase()");

    if ( db_obj != NULL )
    {
        db_obj->Close();
        delete db_obj;
    }

		return -1;
	}
}

//-----------------------------------------------------------------------------------------------------------------------

bool Application::LoadWinSock2()
{
	HOSTENT *hostent;
	SOCKADDR_IN sockaddr_in;
	WORD wVersionRequested;
	WSADATA wsaData;
	char host[512];
	int err;
 
	wVersionRequested = MAKEWORD( 2, 2 );
 
	err = WSAStartup( wVersionRequested, &wsaData );
	
	if( err != 0 )
	{
		Log("Enable to start Winsock2 DLL");
		return false;
	}

	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
	{
		Log("Winsock2 DLL not found");
    WSACleanup( );
		return false;
	}

  err = 0;
	// Hostname 1	
	memset(host, 0, sizeof(host));
	gethostname(host, sizeof(host)-1);
  sMachineName[err++] = host;

	// Hostname 2	
	hostent = gethostbyname("localhost");
  sMachineName[err++] = hostent->h_name;

	// IP Address
	hostent = gethostbyname(hostent->h_name);
	sockaddr_in.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);
	sMachineName[err++].Format( "%d.%d.%d.%d", 
                  ((*((LPIN_ADDR)*hostent->h_addr_list)).S_un.S_addr >>  0) & 0xFF,
                  ((*((LPIN_ADDR)*hostent->h_addr_list)).S_un.S_addr >>  8) & 0xFF,
                  ((*((LPIN_ADDR)*hostent->h_addr_list)).S_un.S_addr >> 16) & 0xFF,
                  ((*((LPIN_ADDR)*hostent->h_addr_list)).S_un.S_addr >> 24) & 0xFF);

  return true;
}

//------------------------------------------------------------------------------------------------------------------------

void Application::Log(const char *s, ...)
{
	va_list args;
	CStdString sBuffer;

	try
	{
		va_start(args, s);
		sBuffer.FormatV(s, args);
		va_end(args);

    if ( pLog != NULL )
    {
		  pLog->Log(0, (LPCSTR)sBuffer);
    }
	}
	catch(...)
	{
	}
}

//-----------------------------------------------------------------------------------------------------------------------

void Application::Log(int iLogLevel, const char *s, ...)
{
	va_list args;
	CStdString sBuffer;

	try
	{
		va_start(args, s);
		sBuffer.FormatV(s, args);
		va_end(args);

    if ( pLog != NULL )
    {
		  pLog->Log(iLogLevel, (LPCSTR)sBuffer);
    }
	}
	catch(...)
	{
	}
}

//-----------------------------------------------------------------------------------------------------------------------

DWORD Application::ThreadDelLogFiles(void *param)
{
	struct _timeb timeb;
	struct tm *ptime;

	try
	{
		for(;;)
		{
			_ftime( &timeb );
			ptime = localtime( &timeb.time );

			// Comeca a apagar os arquivos a partir da hora configurada no register
      if( ptime->tm_hour == Register::HourDelLogFiles )
			{
				// Liga um flag para avisar as threads que devem fechar seus arquivos de
				// logs, isso e feito porque pode haver um arquivo de log muito antigo aberto
				bCloseLogFiles = true;
				
				// Espera 1 minuto para as threads fecharem os arquivos
				Sleep(60000);

				bCloseLogFiles = false;
				
				Log("Clear log files begin...");
				
				DelLog();
				
				Log("Clear log files end.");
			}

			Sleep(60000);
		}

		return 0;
	}
	catch(...)
	{
		Log("EXCEPTION: ThreadDelLogFiles()");
		return 0;
	}
}

//-----------------------------------------------------------------------------------------------------------------------

void Application::FindDelLog(char *Path, int pcLength, char *pcYear, char *pcMonth, char *pcDay)
{
	WIN32_FIND_DATA findData;
	HANDLE fileHandle;
	CStdString sArquivo;
	CStdString sFinder;
	char sDatePath[256];
	char sDateDelete[256];

	try
	{
		strcpy(sDatePath, "00000000");

		// Montando path para procurar arquivos
		sFinder.Format("%s\\*.*", Path);
        	
		// Obtendo primeiro arquivo/diretório do Path especificado e verificando resultado
		fileHandle = FindFirstFile( sFinder.GetBuffer(0), &findData );

		if( fileHandle == INVALID_HANDLE_VALUE )
		{
			Log("can not find path: %s", sFinder.GetBuffer(0)); 
			return;
		}
        	
		do
		{
			// Caso objeto encontrado dentro do Path seja um arquivo, apagá-lo
			if( !( findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY ) )
			{
				sArquivo.Format("%s\\%s", Path, findData.cFileName );
								
				if( DeleteFile( sArquivo.GetBuffer(0) ) == 0 )
				{
					Log("Problem removing file %s", sArquivo.GetBuffer(0));
				}
			}
			
			// Caso objeto encontrado dentro do Path seja um diretório verificar se deve ser apagado
			// e nesse caso apagá-lo recursivamente
			else
			{
				if( findData.cFileName[0] != '.' )
				{
					// Construindo a data a ser deletada
					strcpy(sDateDelete,pcYear);
					strcat(sDateDelete,pcMonth);
					strcat(sDateDelete,pcDay);
					
					// Caso o diretório corrente é de mês
					if ((int)strlen(Path) > pcLength + 6)
					{
						//Construindo a data do diretório
						memcpy(sDatePath,		(Path + pcLength + 1),	4);
						memcpy(sDatePath+4,	(Path + pcLength + 6),	2);
						memcpy(sDatePath+6,	(findData.cFileName),		2);
					}
					else
					{
						// Caso o diretório corrente é de ano				
						if ((int)strlen(Path) > pcLength + 1)
						{
							// Construindo a data do diretório
							memcpy(sDatePath,		(Path + pcLength + 1),	4);
							memcpy(sDatePath+4,	findData.cFileName,			2);
						}
						else
						{
							// Caso o diretório corrente seja o raiz
							if (strlen(Path) == pcLength)
							{
								// Construindo a data do diretório
								memcpy(sDatePath,	findData.cFileName, 4);
							}
						}
					}
					if( atoi(sDatePath) <= atoi(sDateDelete) )
					{
						sArquivo.Format("%s\\%s", Path, findData.cFileName );
						FindDelLog(sArquivo.GetBuffer(0), pcLength, pcYear, pcMonth, pcDay);
					}
				}
      }  	
			// Para Nao Consumir CPU
			Sleep( 1 );
        	
		}while( FindNextFile( fileHandle, &findData ) );
		
		FindClose(fileHandle);
        	
		// Removendo diretório inicial após ter removido todos os seus dependentes
		_rmdir(Path);
	}
	catch(...)
	{
		Log("EXCEPTION: Application::FindDelLog()");
	}
}

//-----------------------------------------------------------------------------------------------------------------------

void Application::DelLog()
{
	struct tm *tm;
	time_t time_today;
	time_t time_delete;
	CStdString sYear;
	CStdString sMonth;
	CStdString sDay;

	try
	{
		// Pega a data de hoje em segundos
		time(&time_today);

		if( Register::NumberOfDaysToKeepLogs <= 1 )
		{
			// Garante que tenha pelo menos 2 dias de logs
			Register::NumberOfDaysToKeepLogs = 2;
		}
		
		// Subtrai da data de hoje, o número de dias passados no parâmetro
		time_delete = time_today - Register::NumberOfDaysToKeepLogs * 86400;
 
		// Converte a data/hora atual
		tm = localtime( &time_delete );
	
		// Monta a data atual com formatação correta
		sYear.Format	("%04d", tm->tm_year + 1900);
		sMonth.Format	("%02d", tm->tm_mon + 1);
		sDay.Format		("%02d", tm->tm_mday);

		// Chama a função para apagar os diretórios/arquivos que estão antes da data calculada
		FindDelLog( Register::BasePathLog, strlen(Register::BasePathLog), sYear.GetBuffer(0), sMonth.GetBuffer(0), sDay.GetBuffer(0));
	}
	catch(...)
	{
		Log("EXCEPTION: Application::DelLog()");
	}
}

//------------------------------------------------------------------------------------------------------------------------

void Application::ReadVersion()
{
	struct VS_VERSIONINFO 
	{
		WORD  wLength;
		WORD  wValueLength;
		WORD  wType;
		WCHAR szKey[16];
		WORD  Padding1[1];
		VS_FIXEDFILEINFO Value;
		WORD  Padding2[1];
		WORD  Children[1];
	};

	HRSRC		res			=	FindResource(NULL,(LPCTSTR)VS_VERSION_INFO,RT_VERSION);
	HGLOBAL	gres		=	LoadResource(NULL,res);
	LPVOID	lpgres	=	LockResource(gres);

	VS_VERSIONINFO		*vers	=	(VS_VERSIONINFO *)lpgres;
	VS_FIXEDFILEINFO	info	=	vers->Value;
	
	DWORD	dwProductVersionMS	= info.dwProductVersionMS;	// 0x00030075 = "3.75"
	DWORD	dwProductVersionLS	= info.dwProductVersionLS;	// 0x00000031 = "0.31"
	
	WORD	p1	=	(WORD)((dwProductVersionMS&0xffff0000)>>16);
	WORD	p2	=	(WORD)((dwProductVersionMS&0xffff));
	WORD	p3	=	(WORD)((dwProductVersionLS&0xffff0000)>>16);
	WORD	p4	=	(WORD)((dwProductVersionLS&0xffff));

  sVersion.Format( "%d.%1d.%d.%d", p1, p2, p3, p4);
}

//------------------------------------------------------------------------------------------------------------------------
