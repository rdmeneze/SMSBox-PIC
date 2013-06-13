
#ifndef SQL_DB_H
	#define SQL_DB_H

#include <windows.h>
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <map>

#include "StdString.h"

using namespace std;

enum SQL_TYPES 
{
	ADO = 0,
	DBLIB,
};

typedef map<int,CStdString> RECORD_SET;

class sql_db {

	public:

		virtual int Open(	const char *ConnectionString,
											const char *DSN,
											const char *DataBase,
											const char *User,
											const char *Password,
											int type = 0) = 0;

		virtual int GetColCount(void) = 0;
		virtual int GetRowCount(void) = 0;
		virtual int Query( const char *sCommand, bool bTransaction = false ) = 0;
		virtual char *GetField(int Row, int Col) = 0;
		virtual const char *GetLastError(void) = 0;
		virtual void Close(void) = 0;
		virtual const char * GetColumnName(int Col) = 0;
		//[11_08_2009<]
		virtual void SetCommandTimeout(int t = 30) = 0;
		//[11_08_2009>]

		//[26473<]
    virtual ~sql_db(){};
		//[26473>]
};

#endif

