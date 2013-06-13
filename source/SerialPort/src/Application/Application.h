
#ifndef ApplicationH
	#define ApplicationH

#include <Windows.h>
#include <setjmp.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <direct.h>
#include "Functions.h"
#include "StdString.h"
#include "tcp_ip_interface.h"
#include "LogFile.h"
#include "defs.h"

enum IOCPMessages
{
	LR_EXEC_SCRIPT = 1,
};

// Id do VosProxy
#define VOS_PROXY_ID					MAKELONG(1,1)

#define	LOG_ERROR							1
#define	LOG_INFO							2
#define	LOG_TCP_IP						10
#define	LOG_DB_RESULT					30
#define	LOG_SCRIPT						40
#define	LOG_FUNCTIONS					50
#define	LOG_ALL								100

class Application
{
	public:
		//[11_05_2010<]
		// Ponteiro para a classe de log		
		static LogFile *pLog;
		//[11_05_2010>]
		// Ponteiro para a classe de conexao com o VosProxy
		static tcp_ip_interface *VosProxy;
		// Id da aplicacao para comunicacao TCP_IP
		static WORD IdApp;
		// Tipo de aplicacao para comunicacao TCP_IP
		static WORD IdTypeApp;
		// Evento de thread pronta para operar		
		static HANDLE EventThreadReady;
		// Endereco da maquina do VosProxy		
		static CStdString sVosProxyHost;
		// Nome ou endereco da maquina local valida para consultas ao banco de dados
		static CStdString sHostName;
		// Variaveis para armazenar as tres formas de nome e endereco da maquina local
    static CStdString sMachineName[3];

		// porta do VosProxy		
		static unsigned short usVosProxyPort;
		// Flag indicando para as threads fecharem os arquivos de log
		static bool bCloseLogFiles;

		// le as informacoes da base de dados para inicializar a aplicacao
		static int ReadInfoFromDataBase();
		// Carrega biblioteca Winsock 2
		static bool LoadWinSock2();

		// Funcao de log
		static void Log(const char *s, ...);
    static void Log(int iLogLevel, const char *s, ...);

    // Captura a versão da aplicação
    static CStdString sVersion;
    static void Application::ReadVersion();

		// Inicializa toda a aplicacao
		static int Start();

		static DWORD ThreadDelLogFiles(void *param);
		static void FindDelLog(char *Path, int pcLength, char * pcYear, char * pcMonth , char * pcDay );
		static void DelLog();
};


#endif
