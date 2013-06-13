
#ifndef LogFile_H
 #define LogFile_H

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <time.h>
#include <sys\timeb.h>
#include <stdarg.h>
#include <direct.h>

#include "CriticalSection.h"

// Maximo valor para o contador unico de linas de log entre as threads
#define MAX_COUNT_VALUE				999999999

class LogFile {

	private:

		// Mantem o nivel de log
		int iLevel;
		// Valor unico para o indice das linhas de log 
		long lUnique;
		// Falg indicando se a classe esta em modo multithread
		bool bMultiThread;
		// Flag indicando se havera divisao por hora nos arquivos
		bool bHour;
		// Variaveis para obter o valor da data
		struct timeb TimeBuffer;
		struct tm *Time;
		struct tm ActualTime;
		// Ponteiro para o arquivo de log aberto
		FILE *pFile;
		// Secao critica caso a classe trabalhe em modo multithread
		CriticalSection crit;
		// Diretorio base para o log
		char sBasePath[_MAX_PATH+1];
		// Path completo montado 
		char sPath[_MAX_PATH+1];
		// mantem o nome do arquivo
		char sFilename[_MAX_PATH+1];
		// mantem o caminho comleto mais o nome do arquivo
		char sPathPlusFileName[_MAX_PATH+1];

		// Cria o diretorio do dia
		void CreateDirectoryDay(void);
		// Cria o diretorio do mes
		void CreateDirectoryMonth(void);
		// Cria o diretorio do ano
		void CreateDirectoryYear(void);

	public:

		// Contador estatico que mantem o valor do index unico
		static long lCount;
		// Valor a ser alterado pela funcao InterlockedCompareExchange()
		static long lExchange;
		// Valor a ser comaprado pela funcao InterlockedCompareExchange()
		static long lComperand;
		// variavel para o valor final depois do incremento do index unico
		static long *lpDestination;
		// Obtem um valor unico para a classe toda de indexador para as linhas de log
		static long GetUniqueCount(void);

		// Coloca a CStdString final no arquivo aberto e cria toda a estrutura de diretorios
		void Log(int level, const char *sInfo);
		void Log(const char *sPath, const char *sName, const char *sInfo);

		// Fecha o arquivo de log
		void CloseFile(void);
		// Modica o nivel de log
		void SetLevel(int level);
		// Retorna o nivel de log
		int GetLevel(void);
		// Retorna true se o nivel passado esta ativado
		bool CheckLevel(int level);
		// Contrutor
		LogFile(const char *name, int level, const char *base_path, bool flag = false);
		LogFile(const char *name, int level, const char *base_path, bool flag, bool hour);
		LogFile();
		// Destrutor
		~LogFile();
};


#endif

