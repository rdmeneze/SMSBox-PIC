
// $Id: WinService.cpp,v 1.4 2010/09/23 21:41:37 rafael.menezes Exp $

#include "WinService.h"
#include <stdio.h>

static bool bService = false;
static char sCurrentPath[_MAX_PATH+1];
static HANDLE hEventExit;
static SERVICE_STATUS_HANDLE hService;

extern void main(int argc, char *argv[]);

SERVICE_TABLE_ENTRY ServiceTableEntry[] = 
{
{ SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION) ServiceMain },
{ NULL, NULL }
};

//------------------------------------------------------------------------------------------------------------------------------------------------------

VOID WINAPI ServiceMain( DWORD dwArgc, LPTSTR *lpszArgv )
{
	bService = true;

	hEventExit = CreateEvent (0, FALSE, FALSE, NULL);

	hService = RegisterServiceCtrlHandler( SERVICE_NAME, ServiceHandler );

	ReportServiceStatus( SERVICE_START_PENDING, 1000, 5000 );

	ServicePath();

	SetCurrentDirectory( sCurrentPath );

	main(0, NULL);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

int InstallService(LPCTSTR lpszBinaryPathName, char * ServiceName, LPCTSTR lpDependencies) 
{  
	SC_HANDLE	schService;
	SC_HANDLE	schSCManager;	

	// Open a handle to the SC Manager database. 
	schSCManager = OpenSCManager( 
			NULL,                    // local machine 
			NULL,                    // ServicesActive database 
			SC_MANAGER_ALL_ACCESS);  // full access rights 
 
	if( schSCManager == NULL ){
		return -1;
	}

	// Verifica se o Servico ja existe
	schService = OpenService(	schSCManager,       // SCManager database 
														ServiceName,        // name of service 
														DELETE);            // only need DELETE access 

  if( schService != NULL ){
		// O servico ja existe
		CloseServiceHandle( schService ); 
	  CloseServiceHandle( schSCManager ); 
		return 0;
	}
	
	schService = CreateService( 
        schSCManager,								// SCManager database 
        ServiceName,								// name of service 
        ServiceName,								// service name to display 
        SERVICE_ALL_ACCESS,					// desired access 
        SERVICE_WIN32_OWN_PROCESS,	// service type 
        SERVICE_AUTO_START,					// start type 
        SERVICE_ERROR_NORMAL,				// error control type 
        lpszBinaryPathName,					// service's binary 
        NULL,											  // no load ordering group 
        NULL,												// no tag identifier 
        lpDependencies,						  // dependencies 
        NULL,												// LocalSystem account 
        NULL);											// no password 
 
  if( schService == NULL ){
	  CloseServiceHandle( schSCManager ); 
		return -1;
	}
 
	CloseServiceHandle( schService ); 
  CloseServiceHandle( schSCManager ); 

	return 1;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

int UnInstallService( char * ServiceName ) 
{ 
	SC_HANDLE	schService;
	SC_HANDLE	schSCManager;

	// Open a handle to the SC Manager database. 
	schSCManager = OpenSCManager( 
			NULL,                    // local machine 
			NULL,                    // ServicesActive database 
			SC_MANAGER_ALL_ACCESS);  // full access rights 
 
	if( schSCManager == NULL ){
		return -1;
	}

	schService = OpenService(	schSCManager,       // SCManager database 
														ServiceName,        // name of service 
														DELETE);            // only need DELETE access 

	if( schService == NULL ) {
	  // O servico nao existe
		CloseServiceHandle( schSCManager ); 
		return 0;
	}

  if( !DeleteService( schService ) ) {
		CloseServiceHandle( schService ); 
	  CloseServiceHandle( schSCManager ); 
		return -1;
	}
 
	CloseServiceHandle( schService ); 
  CloseServiceHandle( schSCManager ); 
	return 1;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

int HandleCommandLine(int argc, char *argv[])
{
	char FileDir[_MAX_PATH+1];
	char sDependencies[4096];
	int iRet, index;
	int i = 0;

	if( bService )
		return 0;

	memset(FileDir, 0, sizeof(FileDir));

	if( argc <= 1 )
	{
		// Sem argumentos, inicia a aplicacao
		return 0;
	}

	// Interpreta os argumentos
	if( argc >= 2 )
	{		
		_strupr(argv[1]);

		if( _stricmp( argv[1], "INSTALL" ) == 0 )
		{
			// Instala o Servico

			// Guarda o caminho para o diretorio corrente
			GetCurrentDirectory( sizeof(FileDir)-1, FileDir);

			//[13_04_2010>]
			// Seta o caminho para o nome de arquivo
			sprintf(FileDir,"%s\\%s.exe", FileDir, SERVICE_NAME);
			//[13_04_2010>]

			memset(sDependencies, 0, sizeof(sDependencies));

			index = 0;

			for(i = 2; i < argc; i++){
				strcpy(sDependencies+index, argv[ i ]);
				index = strlen(sDependencies) + 1;
			}

			iRet = InstallService( FileDir, SERVICE_NAME, (LPCTSTR)sDependencies);

			switch(iRet){

				case 0:
					printf("Service already installed\n");
					index = -1;
				break;
				
				case 1:
					printf("Install OK\n");
					index = 1;
				break;
				
				case -1:
					printf("Install Error\n");
					index = -1;
				break;
			}

			return index;
		}

		if( _stricmp( argv[1], "UNINSTALL" ) == 0 )
		{
			iRet = UnInstallService( SERVICE_NAME );

			switch(iRet){

				case 0:
					printf("Service not found\n");
					index = -1;
				break;
				case 1:
					printf("Uninstall OK\n");
					index = 1;
				break;
				case -1:
					printf("Uninstall Error\n");
					index = -1;
				break;
			}

			return index;
		}
		
		printf("\n");
		printf("Command line to install the service:   %s install <dependencies>\n\n", SERVICE_NAME);
		printf("Command line to remove  the service:   %s uninstall\n", SERVICE_NAME);
		return -1;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void ReportServiceStatus( DWORD dwCurrentState, DWORD dwCheckPoint, DWORD dwWaitHint )
{
	SERVICE_STATUS ServiceStatus;

	if( !bService )
		return;

	if( hService )
	{
		memset( &ServiceStatus, 0, sizeof(ServiceStatus) );
		ServiceStatus.dwServiceType							= SERVICE_WIN32_OWN_PROCESS;
		ServiceStatus.dwCurrentState						= dwCurrentState;
		ServiceStatus.dwControlsAccepted				=	SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
		ServiceStatus.dwWin32ExitCode						= NO_ERROR;
		ServiceStatus.dwServiceSpecificExitCode = 0;
		ServiceStatus.dwCheckPoint							= dwCheckPoint;
		ServiceStatus.dwWaitHint								= dwWaitHint;
		SetServiceStatus( hService, &ServiceStatus );
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

VOID WINAPI ServiceHandler( DWORD fdwControl )
{
	UINT uMsg = 0;
	WPARAM wParam = 0;
	LPARAM lParam = 0;
	int iBufferIndex = 0;
	int rc = 0;
	switch( fdwControl )
	{
		case SERVICE_CONTROL_STOP:
		case SERVICE_CONTROL_SHUTDOWN:
			ReportServiceStatus( SERVICE_STOP_PENDING, 1000, 30000 );
			SetEvent(hEventExit);
		break;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void ServicePath(void)
{
	QUERY_SERVICE_CONFIG query_service_config;
	QUERY_SERVICE_CONFIG *g_psc = NULL;
	SC_HANDLE service, scm;
	BOOL success;
	DWORD dwBytesNeeded;

	scm = OpenSCManager(0, 0,	SC_MANAGER_ALL_ACCESS);

	if( !scm )
		return;
		
	service = OpenService(scm, SERVICE_NAME, SERVICE_QUERY_CONFIG);

	if(!service)
		return;

	// A primeira chamada so serve para saber quantos bytes sao necessarios para coletar toda a informacao
	success = QueryServiceConfig(service,	&query_service_config, sizeof(QUERY_SERVICE_CONFIG), &dwBytesNeeded);

	if( success == 0 )
	{
		DWORD dwBytes = sizeof(QUERY_SERVICE_CONFIG) + dwBytesNeeded;
		
		g_psc = new QUERY_SERVICE_CONFIG[ dwBytesNeeded ];

		BOOL bRetVal = QueryServiceConfig(service, g_psc, dwBytes, &dwBytesNeeded);
			
		if (!bRetVal)
		{
			delete g_psc;
			g_psc = NULL;
			return;
		}

		// Na segunda chamada o tamanho do buffer retornado em dwBytesNeeded e passado para a funcao como o tamnho do buffer real
	}
	else
	{
		g_psc = &query_service_config;
	}

	success = TRUE;

	CloseServiceHandle(service);
	CloseServiceHandle(scm);

	memset(sCurrentPath, 0, sizeof(sCurrentPath));

	if( success )
	{
		strcpy(sCurrentPath, g_psc->lpBinaryPathName);
		_strrev(sCurrentPath);
		strcpy(sCurrentPath, strstr(sCurrentPath, "\\"));
		_strrev(sCurrentPath);
		sCurrentPath[ strlen(sCurrentPath) -1 ] = 0;
	}

	delete g_psc;
	g_psc = NULL;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

int ServiceState(void)
{
	SC_HANDLE service, scm;
	BOOL success;
	SERVICE_STATUS ServiceStatus;

	scm = OpenSCManager(0, 0,	SC_MANAGER_ALL_ACCESS);

	if(!scm)
		return(-1);
		
	service = OpenService(scm, SERVICE_NAME, SERVICE_QUERY_STATUS);

	if(!service)
		return(-1);

	success = QueryServiceStatus(service,	&ServiceStatus );	

	CloseServiceHandle(service);
	CloseServiceHandle(scm);

	return ServiceStatus.dwCurrentState;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void WaitForServiceStop(void)
{
	WaitForSingleObject(hEventExit, INFINITE);
	ReportServiceStatus(SERVICE_STOP_PENDING, 1000, 5000);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool IsService(void)
{
	return bService;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

const char *GetServicePath(void)
{
	return (const char *)sCurrentPath;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

BOOL StartServiceCtrlDispatcher()
{
  return ::StartServiceCtrlDispatcher( (SERVICE_TABLE_ENTRY*)ServiceTableEntry );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
