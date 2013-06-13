/*********************************************************************************************
	Functions.h
*********************************************************************************************/

#ifndef Functions_h
	#define Functions_h

#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys\timeb.h>
#include "StdString.h"
#include "types.h"

// separa o parametro time de segundos em minutos e segundos
// retorna -1 se o valor for menor que um minuto, 1 se for um minuto
// e zero se for minutos e segundos
int MinSeg(int time, int &min, int &seg);

int HourMinSec( DWORD dwTime, int * iHour, int * iMin, int * iSec );

// Retira espacos de CStdString
void StripSpace(char *str);

// Retira caracteres de espaco, tabs e linefeed da direita e esquerda de uma CStdString
void TrimAll( CStdString &bs );
// Retorna a data e hora do sistema em formato SQL YYYY-MM-DD HH:MM:SS
void GetDatetime(char *DateTime, time_t NewTime = 0);
// Retorna a data e hora do sistema em formato SQL YYYY-MM-DD HH:MM:SS
time_t DatetimeToTime_t(const char *DateTime );
// Retorna o tamanho de uma arquivo dado o seu path
long MyGetFileSize(const char *sNomeArq);
// Retorna em sDDD o DDD do numero passado em sNumber
void GetDDD(char *sNumber, char *sDDD);
// Recupera comandos dos pacotes TcpIp
int GetDataPacket(const char *datapacket, char *cCommand, char *cValue, int valuesize);
// Recupera comandos dos pacotes TcpIp
int GetDataPacket(const char *datapacket, char *cCommand, CStdString &sValue);
// Recupera comandos dos pacotes TcpIp
int GetDataPacket(const char *datapacket, char *cCommand, int &iValue);
// Recupera comandos dos pacotes TcpIp
int GetDataPacket(const char *datapacket, char *cCommand, unsigned int &iValue);
// Recupera comandos dos pacotes TcpIp
int GetDataPacket(const char *datapacket, char *cCommand, bool &bValue);
// Recupera comandos dos pacotes TcpIp
int GetDataPacket(const char *datapacket, char *cCommand, long &iValue);
// Checa a mudanca de data de criacao do arquivo, retorna true se a data
// mudou e novo time_null para ser guardado ate nova consulta
bool CheckFileDate(const char *sNomeArq, long &lTimeLastChange);
// Verifica o espaco em disco livre em todas as unidades e retorna -1 se
// algum disco nao esta com o espaco em disco livre de acordo com o valor
// de percentagem passado
int CheckDiskSpace(int iPercentagemLivre);
// Procura por um separador dado por "token" em "search", retornando o valor em "key".
// caso begin seja true comeca no inicio de "search", nas chamdas subsequentes, não passar
// o parametro begin para a funcao continuar ate o final da CStdString
bool GetToken(CStdString &search, CStdString &key, const char *token, bool begin);
// Verifica se o paramentro esta em formato timestamp AAAA-MM-DD HH-MM-SS
bool TimeStamp(char *sPar);
// Cria todos os diretorios do path passado
void MakePath(const char *s);
// Se passar o valor true, sinaliza que o programa terminou, retorna se o programa terminou
bool EndProgram(bool b = false);
// Previne o software de ser debugado qunado estive em versao release
void NoDebugger();

int GetListTokens(CStdString strTokens,  CStdString token ,LstString& lstTokens);

//[25664<]
int CreateDateDirStructure(const char *base_path, char *final_path);
//[25664>]

BOOL DeleteDirectory(const TCHAR* sPath);

//[29318<]
time_t GetFileLastWrite(const char *sFile);
//[29318>]

#endif

