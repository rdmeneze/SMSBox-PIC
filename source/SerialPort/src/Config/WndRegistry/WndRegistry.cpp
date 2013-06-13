/********************************************************************************
 * 
 *  Implementação da biblioteca WndRegistry. 
 *  Há dependência da biblioteca Shlwapi.lib para a compilação
 *
 ********************************************************************************/

#include "WndRegistry.h"
#include <Shlwapi.h>

//------------------------------------------------------------------------------------------------------------------------

CRegistry::CRegistry(const char * cPath)
{
  if ( cPath )
  {
    SetPath( cPath );
  }
	ulAction = 0;
	hKey = 0;
  memset( cKeyName , 0, sizeof( cKeyName ));
}

//------------------------------------------------------------------------------------------------------------------------

CRegistry::~CRegistry()
{
}

//------------------------------------------------------------------------------------------------------------------------

int CRegistry::GetKey( const char *skey, char *svalue, unsigned long ulsize, DWORD tipo )
{
	int rc = 0;
  CStdString sKeyPath;

  sKeyPath.Format( "%s%s", sPath ,cKeyName );
	if( RegCreateKeyEx( HKEY_LOCAL_MACHINE, (LPCSTR)sKeyPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL, &hKey, &ulAction ) != ERROR_SUCCESS )
	{
		svalue[ 0 ] = 0;
		return -1;
	}
	switch( ulAction )
	{
		case REG_OPENED_EXISTING_KEY:
			if( RegQueryValueEx( hKey, skey, NULL, NULL, (LPBYTE) svalue, &ulsize ) != ERROR_SUCCESS )
			{
				RegCloseKey( hKey );
				svalue[ 0 ] = 0;
				return -2;
			}
		break;
		default:
				RegCloseKey( hKey );
				svalue[ 0 ] = 0;
				return -3;
	}
	RegCloseKey( hKey );
	return rc;
}

//------------------------------------------------------------------------------------------------------------------------

int CRegistry::SetKey( const char *skey, const char *svalue, unsigned int usize, DWORD type )
{
	int rc = 0;
  CStdString sKeyPath;

  sKeyPath.Format( "%s%s", sPath ,cKeyName );

	if( type == REG_SZ )
		usize = strlen( svalue ) + 1;

	if( RegCreateKeyEx( HKEY_LOCAL_MACHINE, (LPCSTR)sKeyPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL, &hKey, &ulAction ) != ERROR_SUCCESS )
	{
		return -1;
	}
	switch( ulAction )
	{
		case REG_CREATED_NEW_KEY:
			RegSetValueEx( hKey, skey, 0, type, (CONST BYTE *) svalue, usize );
			rc = 1;
		break;
		case REG_OPENED_EXISTING_KEY:
			RegSetValueEx( hKey, skey, 0, type, (CONST BYTE *) svalue, usize );
		break;
		default:
			rc = -3;
	}
	RegCloseKey( hKey );
	return rc;
}

//------------------------------------------------------------------------------------------------------------------------

int CRegistry::DeleteKey( const char *skey )
{
  DWORD dwRet;
  CStdString sKeyPath;

  sKeyPath.Format( "%s%s", sPath, skey );

  if( RegOpenKeyEx( HKEY_LOCAL_MACHINE, (LPCSTR)sKeyPath, 0, KEY_ALL_ACCESS , &hKey ) != ERROR_SUCCESS ){
		return -1;
	}

  dwRet = SHDeleteKey( hKey, "" );

	RegCloseKey( hKey );
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------

int CRegistry::GetPath( char *spath, unsigned int usize )
{
	strncpy( spath, sPath, usize-1 );
	spath[ usize-1 ] = 0;
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------

int CRegistry::SetPath( const char *spath )
{
	strncpy( sPath, spath, sizeof(sPath)-1 );
	sPath[ sizeof(sPath)-1 ] = 0;
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------

void CRegistry::SetKeyName(const char * sKey)
{
    memset( cKeyName , 0, sizeof( cKeyName ));
    strncpy( cKeyName, sKey, sizeof( cKeyName ) - 1 );
    return;
}

//------------------------------------------------------------------------------------------------------------------------

const char* CRegistry::GetKeyName(void){
  return (const char*)cKeyName;
}

//------------------------------------------------------------------------------------------------------------------------

void CRegistry::GetValue(const char *sValue, const char *sDefaultValue)
{
	char str[256];

	if(GetKey(sValue, str, sizeof(str)-1) < 0)
		SetKey(sValue, sDefaultValue);
}

//------------------------------------------------------------------------------------------------------------------------

void CRegistry::GetValue(const char *sValue, const char *sDefaultValue, unsigned short &Value)
{
	char str[256];
	
	if(GetKey(sValue, str, sizeof(str)-1) < 0){
		SetKey(sValue, sDefaultValue);
		Value = atoi(sDefaultValue);
	}
	else{
		Value = atoi(str);
	}
}

//------------------------------------------------------------------------------------------------------------------------

void CRegistry::GetValue(const char *sValue, const char *sDefaultValue, int &Value)
{
	char str[256];

	if(GetKey(sValue, str, sizeof(str)-1) < 0){
		SetKey(sValue, sDefaultValue);
		Value = atoi(sDefaultValue);
	}
	else{
		Value = atoi(str);
	}
}

//------------------------------------------------------------------------------------------------------------------------

void CRegistry::GetValue(const char *sValue, const char *sDefaultValue, bool &Value)
{
	char str[256];

	if(GetKey(sValue, str, sizeof(str)-1) < 0){
		SetKey(sValue, sDefaultValue);
		if(atoi(sDefaultValue))
			Value = true;
		else
			Value = false;
	}
	else{
		if(atoi(str))
			Value = true;
		else
			Value = false;
	}
}

//------------------------------------------------------------------------------------------------------------------------

void CRegistry::GetValue(const char *sValue, const char *sDefaultValue, char *Value)
{
	char str[256];

	if(GetKey(sValue, str, sizeof(str)-1) < 0){
		SetKey(sValue, sDefaultValue);
		strcpy(Value, sDefaultValue);
	}
	else{
		strcpy(Value, str);
	}
}

//------------------------------------------------------------------------------------------------------------------------

void CRegistry::GetValue(const char *sValue, const char *sDefaultValue, char& Value)
{
	char str[256];

	if(GetKey(sValue, str, sizeof(str)-1) < 0){
		SetKey(sValue, sDefaultValue);
		Value = toupper(sDefaultValue[0]);
	}
	else{
		Value = toupper(str[0]);
	}
}

//------------------------------------------------------------------------------------------------------------------------

void CRegistry::GetValue(const char *sValue, const char *sDefaultValue, CStdString &Value)
{
	char str[256];

	if(GetKey(sValue, str, sizeof(str)-1) < 0){
		SetKey(sValue, sDefaultValue);
		Value = sDefaultValue;
	}
	else{
		Value = str;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int CRegistry::DeletePath( )
{
  DWORD dwRet;

  if( RegOpenKeyEx( HKEY_LOCAL_MACHINE, sPath , 0, KEY_ALL_ACCESS , &hKey ) != ERROR_SUCCESS ){
		return -1;
	}

  dwRet = SHDeleteKey( hKey, "" );

	RegCloseKey( hKey );
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------