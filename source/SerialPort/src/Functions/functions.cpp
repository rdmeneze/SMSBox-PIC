
#include <io.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include "Functions.h"
#include <sys/stat.h>

#define	SPACE			32

//---------------------------------------------------------------------------------------------

static int iFlagEndprogram = 0;

//---------------------------------------------------------------------------------------------

bool TimeStamp(char *sPar)
{
	try {

		if(strchr(sPar, '-') == NULL)
			return false;
		if(strchr(sPar, '-') == NULL)
			return false;
		if(strchr(sPar, '-') == NULL)
			return false;
		if(strchr(sPar, ' ') == NULL)
			return false;
		if(strchr(sPar, ':') == NULL)
			return false;
		if(strchr(sPar, ':') == NULL)
			return false;

		return true;
	}
	catch(...){
    return false;
	}
}

//---------------------------------------------------------------------------------------------

void TrimAll( CStdString &bs )
{
	try {

		register int iStart, iEnd;

		iStart = bs.find_first_not_of( " \r\n\t\"'", 0 );
		
		if( iStart == bs.npos )
			return;
		
		iEnd = bs.find_last_not_of( " \r\n\t\"'", bs.size()-1 );
		
		if( iEnd == bs.npos )
			return;

		bs = bs.substr( iStart, iEnd - iStart + 1 );
	}
	catch(...){
	}
}

//---------------------------------------------------------------------------------------------

void StripSpace(char *str)
{
	int i, j, l;
	char ras[512];

	try {

		l = strlen(str);

		if(l > 500)
			return;
		
		memset(ras, 0, sizeof(ras));

		for(i = 0, j = 0; i < l; i++){
			
			if(str[i] == SPACE)
				continue;

			ras[j] = str[i];
			j++;
		}	

		l = strlen(ras);

		for(i = 0; i < l; i++){
			str[i] = ras[i];
		}	
		
		str[i] = 0;

	}
	catch(...){
	}
}

//---------------------------------------------------------------------------------------------

int GetDataPacket(const char *datapacket, char *cCommand, char *cValue, int valuesize)
{
  CStdString data, check, strToFind;
  int pos_ini, pos_fim;

  try {

		data = datapacket;

		strToFind = cCommand;
		strToFind += "=";

		pos_ini = data.find(strToFind.c_str(), 0);
		
		if( pos_ini == -1 ){
			strcpy(cValue, "");
			return -1;
		}

		if( pos_ini > 1 ){

			check = data.at( pos_ini - 1 );

			while( check != "&" ){

				pos_ini = data.find(strToFind.c_str(), pos_ini + 1);
				
				if( pos_ini == -1 ){
					strcpy(cValue, "");
					return -1;
				}

				check = data.at( pos_ini - 1 );
			}
		}

		pos_ini += (strlen(strToFind.c_str()));
		pos_fim = data.find("&", pos_ini);

		// Retorna o valor de acordo com o tipo
		strncpy(cValue, data.substr(pos_ini, pos_fim-pos_ini).c_str(), valuesize);

		return 0;
	}
	catch(...){
		strcpy(cValue, "");
		return -1;
	}
}

//---------------------------------------------------------------------------------------------

int GetDataPacket(const char *datapacket, char *cCommand, CStdString &sValue)
{
  CStdString data, check, strToFind;
  int pos_ini, pos_fim;

  try {

		data = datapacket;

		strToFind = cCommand;
		strToFind += "=";

		pos_ini = data.find(strToFind.c_str(), 0);
		
		if( pos_ini == -1 ){
			sValue= "";
			return -1;
		}

		if( pos_ini > 1 ){

			check = data.at( pos_ini - 1 );

			while( check != "&" ){

				pos_ini = data.find(strToFind.c_str(), pos_ini + 1);
				
				if( pos_ini == -1 ){
					sValue= "";
					return -1;
				}

				check = data.at( pos_ini - 1 );
			}
		}

		pos_ini += (strlen(strToFind.c_str()));
		pos_fim = data.find("&", pos_ini);

		// Retorna o valor de acordo com o tipo
		sValue = data.substr(pos_ini, pos_fim-pos_ini).c_str();

    sValue.Trim();

		return 0;
	}
	catch(...){
		sValue= "";
		return -1;
	}
}

//---------------------------------------------------------------------------------------------

int GetDataPacket(const char *datapacket, char *cCommand, int &iValue)
{
  CStdString sData;
  int iRet;
  try
  {
    iRet = GetDataPacket( datapacket, cCommand, sData);
    iValue = atoi( (LPCSTR)sData );

		return iRet;
	}
	catch(...){
		iValue = 0;
		return -1;
	}
}

//---------------------------------------------------------------------------------------------

int GetDataPacket(const char *datapacket, char *cCommand, unsigned int &iValue)
{
  CStdString sData;
  int iRet;
  try
  {
    iRet = GetDataPacket( datapacket, cCommand, sData);
    iValue = atoi( (LPCSTR)sData );

    return iRet;
	}
	catch(...){
		iValue = 0;
		return -1;
	}
}

//---------------------------------------------------------------------------------------------

int GetDataPacket(const char *datapacket, char *cCommand, bool &bValue)
{
  int iData;
  int iRet;
  try
  {
    iRet = GetDataPacket( datapacket, cCommand, iData);
    bValue = ( iData == 0 ) ? false : true;

		return iRet;
	}
	catch(...){
		bValue = false;
		return -1;
	}
}

//---------------------------------------------------------------------------------------------

int GetDataPacket(const char *datapacket, char *cCommand, long &iValue)
{
  CStdString sData;
  int iRet;
  try
  {
    iRet = GetDataPacket( datapacket, cCommand, sData);
    iValue = atoi( (LPCSTR)sData );

    return iRet;
	}
	catch(...){
		iValue = 0;
		return -1;
	}
}

//---------------------------------------------------------------------------------------------

int MinSeg(int time, int &min, int &seg)
{
	try {

		if(time < 60){
			// menos de 1 minuto
			return -1;
		}
		else
			if(time == 60){
				// 1 minuto	
				return 1;
			}
		else{
			
			min = time / 60;
			seg = time % 60;
		}
		return 0;
	}
	catch(...){
		return -1;
	}
}

//---------------------------------------------------------------------------------------------

int HourMinSec( DWORD dwTime, int * iHour, int * iMin, int * iSec )
{
  try
  {
    *iSec = dwTime % 60L;
    *iMin = dwTime / 60;
    *iHour = *iMin / 60L;
    *iMin %= 60L;
    return 0;
  }
  catch(...)
  {
    return -1;
  }
}

//---------------------------------------------------------------------------------------------

void GetDatetime(char *DateTime, time_t NewTime)
{
	struct tm *t;

	try {

    if( NewTime == 0 )
  		time((time_t*)&NewTime);

		t = localtime((time_t*)&NewTime);

											// Ex: 2001-01-14 13:05:00",
		sprintf(DateTime, "%04d-%02d-%02d %02d:%02d:%02d",
									t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	}
	catch(...){
	}	
}

//---------------------------------------------------------------------------------------------

time_t DatetimeToTime_t(const char *DateTime )
{
  // Ex: 2001-01-14 13:05:00",
  int   iTime[6] = {0}; 
  char  cFindChars[6] = {'-', '-', ' ', ':', ':', 0 };
  char * pChar;
  struct tm tm;
  time_t tm_Ret = 0;
  int i;

  try
  {
    if ( TimeStamp( (char*)DateTime ) == false )
    {
      return tm_Ret;
    }

    for ( i = 0, pChar = (char*)&DateTime[0];
          i < sizeof( cFindChars ) - 1 ; 
          i++ )
    {
      iTime[i] = atoi( pChar ); 
      pChar = strchr( pChar+1, cFindChars[i] );
      pChar++;
    }

    tm.tm_year = iTime[0] - 1900;
    tm.tm_mon  = iTime[1] - 1;
    tm.tm_mday = iTime[2];
    tm.tm_hour = iTime[3];
    tm.tm_min  = iTime[4];
    tm.tm_sec =  iTime[5];

    tm_Ret = mktime( &tm );
  }
  catch(...)
  {
  }
  return tm_Ret;
}

//---------------------------------------------------------------------------------------------

long MyGetFileSize(const char *sNomeArq)
{
	WIN32_FIND_DATA find_data;
	HANDLE h_file = INVALID_HANDLE_VALUE;

	try {

		h_file = FindFirstFile(sNomeArq, &find_data);

		if(h_file == INVALID_HANDLE_VALUE){
			FindClose(h_file );
			return 0;
		}

		FindClose(h_file );

		return find_data.nFileSizeLow;
	}
	catch(...){
	}	
  return 0;
}

//---------------------------------------------------------------------------------------------

bool CheckFileDate(const char *sNomeArq, long &lTimeLastChange)
{
	WIN32_FIND_DATA find_data;
	SYSTEMTIME system_time;
	SYSTEMTIME system_time_aux;
	TIME_ZONE_INFORMATION time_zone_information;
	long lTime;
	struct tm tm;
	
	HANDLE h_file = INVALID_HANDLE_VALUE;

	try {

		h_file = FindFirstFile(sNomeArq, &find_data);

		if(h_file == INVALID_HANDLE_VALUE){
			FindClose(h_file );
			return false;
		}

		FindClose(h_file );


		// converte time do arquivo para time do sistema
		FileTimeToSystemTime(&find_data.ftLastWriteTime, &system_time_aux);
		// obtem informacao do time local
		GetTimeZoneInformation(&time_zone_information);
		// converte time do sistema para time local
		SystemTimeToTzSpecificLocalTime(&time_zone_information, &system_time_aux, &system_time);

		tm.tm_year	=	system_time.wYear - 1900;
		tm.tm_mon		=	system_time.wMonth -	1;
		tm.tm_mday	=	system_time.wDay;
		tm.tm_hour	=	system_time.wHour;
		tm.tm_min		=	system_time.wMinute;
		tm.tm_sec		=	system_time.wSecond;
		tm.tm_isdst	=	-1;

		lTime				=	(long)mktime(&tm);

		if( lTime != lTimeLastChange ){
			lTimeLastChange = lTime;
			return true;
		}

		return false;
	}
	catch(...){
		return true;
	}	
}

//---------------------------------------------------------------------------------------------

void GetDDD(char *sNumber, char *sDDD)
{
	try {
		
		int iLen = strlen( sNumber );
		
		if( iLen <= 8 ){
			return;
		}
		if( iLen == 9 ){
			// Numero de 7 digitos com 2 de DDD
			sDDD[0] = sNumber[0];
			sDDD[1] = sNumber[1];
			sDDD[2] = 0;
			return;
		}
		if( iLen == 10 ){
			// Numero de 8 digitos com 2 de DDD
			sDDD[0] = sNumber[0];
			sDDD[1] = sNumber[1];
			sDDD[2] = 0;
			return;
		}
		if( iLen >= 12 ){
			// Numero de com 2 de DDD e 3 de operadora
			sDDD[0] = sNumber[3];
			sDDD[1] = sNumber[4];
			sDDD[2] = 0;
			return;
		}
		return;
	}
	catch(...){
	}	
}

//---------------------------------------------------------------------------------------------

int CheckDiskSpace(int iPercentagemLivre)
{
	int i;
	unsigned int DriveType;
	unsigned long setores_p_cluster, bytes_p_setor, free_cluster, cluster;
	float size_real, size_div, free_real, free_div, disk_size, free_space, fFreeSpaceRequired;
	char sPath[20];
	char unidade_size[20];
	char unidade_free[20];

	try {

		for(i = 0; i < 26; i++){

			sprintf(sPath, "%c:\\", 65+i);

			DriveType = GetDriveType(sPath);
			
			if(DriveType != DRIVE_FIXED)
				continue;

			if(GetDiskFreeSpace(sPath, &setores_p_cluster, &bytes_p_setor, &free_cluster, &cluster) == FALSE)
				continue;

			size_real	= (float)setores_p_cluster * (float)bytes_p_setor * (float)cluster;
			size_div	= (float)(((float)setores_p_cluster * (float)bytes_p_setor * (float)cluster) / 1000);

			if(size_div >= 1){

				disk_size = size_div;

				if(disk_size > 999999){	// giga
					disk_size = disk_size / 1000;
					disk_size = disk_size / 1000;
					strcpy(unidade_size, "GB");
				}
				else{
					if(disk_size <= 999999 && disk_size > 999 ){ // mega
						disk_size = disk_size / 1000;
						strcpy(unidade_size, "MB");
					}
					else{
						if(disk_size <= 999){ // kilo
							disk_size = disk_size;
							strcpy(unidade_size, "KB");
						}
					}
				}					
			}
			else{	// bytes
				disk_size = size_real;
				strcpy(unidade_size, "BY");
			}

			free_real	= (float)setores_p_cluster * (float)bytes_p_setor * (float)free_cluster;
			free_div	= (float)(((float)setores_p_cluster * (float)bytes_p_setor * (float)free_cluster) / 1000);

			if(free_div >= 1){

				free_space = free_div;

				if(free_space > 999999){	// giga
					free_space = free_space / 1000;
					free_space = free_space / 1000;
					strcpy(unidade_free, "GB");
				}
				else{
					if(free_space <= 999999 && free_space > 999 ){ // mega
						free_space = free_space / 1000;
						strcpy(unidade_free, "MB");
					}
					else{
						if(free_space <= 999){ // kilo
							free_space = free_space;
							strcpy(unidade_free, "KB");
						}
					}
				}
			}
			else{ // bytes
				free_space = free_real;
				strcpy(unidade_free, "BY");
			}

			// Descobre o valor em bytes da porcentagem desejada de espaco livre em realacao ao tamanho do disco
			fFreeSpaceRequired = (iPercentagemLivre * disk_size) / 100;

			if( free_space >= fFreeSpaceRequired ){
				// Espaco em disco OK
				continue;
			}
			else{
				// Espaco em disco nao e suficiente
				return -1;
			}
		}
		
		// Todos os discos estao com espaco livre suficiente para atender a percentagem
		// passada para a funcao
		return 0;
	}
	catch(...){
		// Espaco em disco nao e suficiente
		return -1;
	}
}

//---------------------------------------------------------------------------------------------

bool GetToken(CStdString &search, CStdString &key, const char *token, bool begin)
{
	try {

		static int index	= 0;
		static int pos		= 0;

		if( begin ){
			index = 0;
			pos		= 0;
		}

		key.erase();

		if( pos < 0 ){
			return false;
		}
		if( search.empty() ){
			return false;
		}
		// procura o elemento separador
		pos = search.find(token, pos);
		// copia o conteudo anterior ao separador
		key = search.substr(index, pos - index);

		if( pos >= 0 ){
			index = pos;
			index++;
			pos++;
		}

		return true;
	}
	catch(...){
		return false;
	}
}

//---------------------------------------------------------------------------------------------

void MakePath(const char *s)
{
	//[25664<]
	char sPath[ _MAX_PATH + 512 ];
	//[25664>]
	char *p;

	try {

		strcpy(sPath, s);

		p = strchr(sPath, '\\' );
		
		while( p ){				
			p[0] = 0;
			_mkdir( sPath );
			p[0] = '\\';
			p = strchr( p+1, '\\' );		
		};

		_mkdir( sPath );
	}
	catch(...){
	}
}

//---------------------------------------------------------------------------------------------

bool EndProgram(bool b)
{
	Sleep(1);

	if( b )
	{
		iFlagEndprogram = 1;
	}

	if( iFlagEndprogram )
		return true;

	return false;
}

//---------------------------------------------------------------------------------------------

void NoDebugger()
{
	#ifndef _DEBUG
		if( IsDebuggerPresent() )
			DebugBreak();
	#endif
}

//---------------------------------------------------------------------------------------------

int GetListTokens(CStdString strTokens,  CStdString token ,LstString& lstTokens)
{
	CStdString sAux,sTmp;
	char buffer[512];
	int i,j;

	if ( strTokens != "" ){
		sAux = strTokens.GetAt( strTokens.GetLength( ) - 1 ) ;
		if ( sAux != token ){
			sAux = strTokens + token;
		}
		else{
			sAux = strTokens;
		}

		i = 0;
		j = sAux.find_first_of( token );

		for ( ;; ){
			memset( (char *)buffer, 0, sizeof( buffer ) );

			if ( j-i > 1 ){
				sAux.copy( buffer, j-i, i );
			}

			sTmp = buffer;

			if ( sTmp != "" )
			{
				lstTokens.push_back( (LPCSTR)sTmp );
			}

			i = ++j;
			j = sAux.find_first_of( token, i );

			if ( j == -1 ) {
				break;
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------
//[25664<]
/*
Cria uma estrutura de diretorios como: base\ano\mes\dia, retorna o caminho completo criado no parametro "final_path"

retornos:

0				- Success
EACCES	-	Access denied: the file's permission setting does not allow specified access.
ENOENT	-	File name or path not found.
EINVAL	-	Invalid parameter.
-1			- Unknow error
*/
int CreateDateDirStructure(const char *base_path, char *final_path)
{
	struct timeb TimeBuffer;
	struct tm *Time;
	char temp[ _MAX_PATH + 512 ];

	try
	{
		ftime( &TimeBuffer );
		Time = localtime( &TimeBuffer.time );

		sprintf(temp, "%s\\%04d\\%02d\\%02d\\", base_path, Time->tm_year + 1900, Time->tm_mon + 1, Time->tm_mday );

		MakePath( (const char *)temp );

		strcpy(final_path, temp);

		if( _access(temp, 6) != 0 )
		{
			if( errno == EACCES )
				return errno;

			if( errno == ENOENT )
				return errno;

			if( errno == EINVAL )
				return errno;

			return -1;
		}
	}
	catch(...)
	{
		return -1;
	}
	return 0;
}
//[25664>]
//------------------------------------------------------------------------------------------------------------------------

BOOL IsDots(const TCHAR* str) 
{
   if(_tcscmp(str,".") && _tcscmp(str,"..")) return FALSE;
   return TRUE;
}

//------------------------------------------------------------------------------------------------------------------------

BOOL DeleteDirectory(const TCHAR* sPath) 
{
   HANDLE hFind;    // file handle
   WIN32_FIND_DATA FindFileData;

   TCHAR DirPath[MAX_PATH];
   TCHAR FileName[MAX_PATH];

   _tcscpy(DirPath,sPath);
   _tcscat(DirPath,"\\*");    // searching all files
   _tcscpy(FileName,sPath);
   _tcscat(FileName,"\\");

   // find the first file
   hFind = FindFirstFile(DirPath,&FindFileData);
   if(hFind == INVALID_HANDLE_VALUE) return FALSE;
   _tcscpy(DirPath,FileName);

   bool bSearch = true;
   while(bSearch) // until we find an entry
   {    
      if(FindNextFile(hFind,&FindFileData)) 
      {
         if(IsDots(FindFileData.cFileName)) 
           continue;

         _tcscat(FileName,FindFileData.cFileName);
         if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
         {
            // we have found a directory, recurse
            if(!DeleteDirectory(FileName)) 
            {
                FindClose(hFind);
                return FALSE;    // directory couldn't be deleted
            }
            // remove the empty directory
            RemoveDirectory(FileName);
             _tcscpy(FileName,DirPath);
         }
         else 
         {
            if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
               // change read-only file mode
            _chmod(FileName, _S_IWRITE);
            if(!DeleteFile(FileName)) 
            {    // delete the file
              FindClose(hFind);
              return FALSE;
            }
            _tcscpy(FileName,DirPath);
         }
      }
      else  // no more files there
      {
         
         if(GetLastError() == ERROR_NO_MORE_FILES)
         bSearch = false;
         else 
         {
        // some error occurred; close the handle and return FALSE
           FindClose(hFind);
           return FALSE;
         }
      }
   }
   FindClose(hFind);                  // close the file handle

   return RemoveDirectory(sPath);     // remove the empty directory
}

//------------------------------------------------------------------------------------------------------------------------

//[29318<]
time_t GetFileLastWrite(const char *sFile)
{
	WIN32_FIND_DATA findData;
  SYSTEMTIME SystemTime;
	struct tm tm;
	time_t t;
	HANDLE fileHandle;

	try
	{
		fileHandle = FindFirstFile(sFile, &findData );

		if( fileHandle == INVALID_HANDLE_VALUE )
		{
			return 0;
		}

		FindClose(fileHandle);

		if( FileTimeToSystemTime( &findData.ftLastWriteTime, &SystemTime) == 0 )
			return 0;

		tm.tm_year	=	SystemTime.wYear	-	1900;
		tm.tm_mon		=	SystemTime.wMonth	-	1;
		tm.tm_mday	=	SystemTime.wDay;
		tm.tm_hour	=	SystemTime.wHour;
		tm.tm_min		=	SystemTime.wMinute;
		tm.tm_sec		=	SystemTime.wSecond;
		tm.tm_isdst	=	-1;

		t = mktime( &tm );

		return t;
	}
	catch(...)
	{
		return 0;
	}
}
//[29318>]
//------------------------------------------------------------------------------------------------------------------------

