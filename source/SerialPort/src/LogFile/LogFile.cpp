
#include "LogFile.h"
#include "functions.h"

//--------------------------------------------------------------------------------------------------------------------------

long LogFile::lCount			=	0;
long LogFile::lExchange		=	0;
long LogFile::lComperand	=	MAX_COUNT_VALUE;
long *LogFile::lpDestination = &LogFile::lCount;

//--------------------------------------------------------------------------------------------------------------------------

LogFile::LogFile(const char *name, int level, const char *base_path, bool flag)
{
	bMultiThread				= flag;
	iLevel							= level;
	pFile								= NULL;
	bHour								=	false;

	ActualTime.tm_year	= -1;
	ActualTime.tm_mon		= -1;
	ActualTime.tm_mday	= -1;

	strcpy(sBasePath, base_path);
	strcpy(sFilename, name);

	// Cria o diretorio base
	if( _access( sBasePath, 0) != 0 )
		_mkdir( sBasePath );
}

//--------------------------------------------------------------------------------------------------------------------------

LogFile::LogFile(const char *name, int level, const char *base_path, bool flag, bool hour)
{
	bMultiThread				= flag;
	iLevel							= level;
	pFile								= NULL;
	bHour								=	hour;

	ActualTime.tm_year	= -1;
	ActualTime.tm_mon		= -1;
	ActualTime.tm_mday	= -1;

	strcpy(sBasePath, base_path);
	strcpy(sFilename, name);

	// Cria o diretorio base
	if( _access( sBasePath, 0) != 0 )
		_mkdir( sBasePath );
}

//--------------------------------------------------------------------------------------------------------------------------

LogFile::LogFile()
{
	bMultiThread				= false;
	iLevel							= 0;
	pFile								= NULL;
	bHour								=	false;

	ActualTime.tm_year	= -1;
	ActualTime.tm_mon		= -1;
	ActualTime.tm_mday	= -1;

	memset(sBasePath, 0, sizeof(sBasePath));
	memset(sFilename, 0, sizeof(sFilename));
}

//--------------------------------------------------------------------------------------------------------------------------

LogFile::~LogFile()
{
	CloseFile();
}

//--------------------------------------------------------------------------------------------------------------------------

long LogFile::GetUniqueCount(void)
{
  InterlockedCompareExchange( lpDestination, (LONG)lExchange, (LONG)lComperand);
	return ( InterlockedIncrement(&lCount) );
}

//--------------------------------------------------------------------------------------------------------------------------

void LogFile::SetLevel(int level)
{
	iLevel = level;
}

//--------------------------------------------------------------------------------------------------------------------------

int LogFile::GetLevel(void)
{
  return LogFile::iLevel;
}

//--------------------------------------------------------------------------------------------------------------------------

bool LogFile::CheckLevel(int level)
{
	if( iLevel >= level )
		return true;

	return false;
}

//--------------------------------------------------------------------------------------------------------------------------

void LogFile::Log(int level, const char *sInfo)
{
	try {

		if( level > iLevel )
			return;

		if(bMultiThread)
		{
			CriticalSection::Scope scope( crit );
		}

		ftime( &TimeBuffer );
		Time = localtime( &TimeBuffer.time );

		if( bHour ){

			if( ActualTime.tm_hour != Time->tm_hour )
			{
				ActualTime.tm_hour = Time->tm_hour;
				// Fecha o arquivo atual para abrir no novo diretorio
				if( pFile != NULL ){
					fclose( pFile );
					pFile = NULL;
				}
				if( ActualTime.tm_mday != Time->tm_mday )
				{
					if( ActualTime.tm_mon != Time->tm_mon )
					{
						if( ActualTime.tm_year != Time->tm_year )
						{
							ActualTime.tm_year = Time->tm_year;
							CreateDirectoryYear();
						}
						ActualTime.tm_mon = Time->tm_mon;
						CreateDirectoryMonth();
					}
					ActualTime.tm_mday = Time->tm_mday;
					CreateDirectoryDay();
				}
			}

			if( pFile == NULL ){
				
				sprintf(sPathPlusFileName, "%s%02d_%s.txt", sPath, ActualTime.tm_hour, sFilename);

				pFile = fopen(sPathPlusFileName, "at");

				if( pFile == NULL )
				{
					return;
				}
			}
		}
		else{

			if( ActualTime.tm_mday != Time->tm_mday )
			{
				// Fecha o arquivo atual para abrir no novo diretorio
				CloseFile();

				if( ActualTime.tm_mon != Time->tm_mon )
				{
					if( ActualTime.tm_year != Time->tm_year )
					{
						ActualTime.tm_year = Time->tm_year;
						CreateDirectoryYear();
					}
					ActualTime.tm_mon = Time->tm_mon;
					CreateDirectoryMonth();
				}
				ActualTime.tm_mday = Time->tm_mday;
				CreateDirectoryDay();
			}

			if( pFile == NULL ){

				sprintf(sPathPlusFileName, "%s%s", sPath, sFilename);

				pFile = fopen(sPathPlusFileName, "at");

				if( pFile == NULL )
				{
					return;
				}
			}
		}

		// Obtem um valor unico para a classe toda de indexador para as linhas de log
		lUnique = GetUniqueCount();

		fprintf(pFile, "%09d %02d:%02d:%02d.%03d %s\n", 
										lUnique,
										Time->tm_hour,
										Time->tm_min,
										Time->tm_sec,
										TimeBuffer.millitm,
										sInfo);

		fflush(pFile);
	}
	catch(...)
	{
	}
}

//--------------------------------------------------------------------------------------------------------------------------

void LogFile::Log(const char *sPath, const char *sName, const char *sInfo)
{
	try {

		strcpy(sBasePath, sPath);
		strcpy(sFilename, sName);

		ftime( &TimeBuffer );
		Time = localtime( &TimeBuffer.time );

		if( ActualTime.tm_mday != Time->tm_mday )
		{
			// Fecha o arquivo atual para abrir no novo diretorio
			CloseFile();

			if( ActualTime.tm_mon != Time->tm_mon )
			{
				if( ActualTime.tm_year != Time->tm_year )
				{
					ActualTime.tm_year = Time->tm_year;
					CreateDirectoryYear();
				}
				ActualTime.tm_mon = Time->tm_mon;
				CreateDirectoryMonth();
			}
			ActualTime.tm_mday = Time->tm_mday;
			CreateDirectoryDay();
		}

		if( pFile == NULL ){
			
			sprintf(sPathPlusFileName, "%s%s", sPath, sFilename);

			pFile = fopen(sPathPlusFileName, "at");

			if( pFile == NULL )
				return;
		}

		fprintf(pFile, "%s\n", sInfo);

		fflush(pFile);
	}
	catch(...){
	}
}



//--------------------------------------------------------------------------------------------------------------------------

void LogFile::CreateDirectoryYear(void)
{
	try {
		sprintf(sPath, "%s\\%04d\\", sBasePath, ActualTime.tm_year + 1900 );
    MakePath( sPath );
	}
	catch(...){
	}
}

//------------------------------------------------------------------------------------------------------------------------

void LogFile::CreateDirectoryMonth(void)
{
	try {
		sprintf(sPath,"%s\\%04d\\%02d\\", sBasePath, ActualTime.tm_year + 1900, ActualTime.tm_mon + 1 );
    MakePath( sPath );
	}
	catch(...){
	}
}

//------------------------------------------------------------------------------------------------------------------------

void LogFile::CreateDirectoryDay(void)
{
	try {
		sprintf(sPath, "%s\\%04d\\%02d\\%02d\\", sBasePath, ActualTime.tm_year + 1900, ActualTime.tm_mon + 1, ActualTime.tm_mday );
    MakePath( sPath );
	}
	catch(...){
	}
}

//------------------------------------------------------------------------------------------------------------------------

void LogFile::CloseFile(void)
{
	try {

		if( pFile != NULL ){
			fclose( pFile );
			pFile = NULL;
		}
	}
	catch(...){
	}
}

//------------------------------------------------------------------------------------------------------------------------

