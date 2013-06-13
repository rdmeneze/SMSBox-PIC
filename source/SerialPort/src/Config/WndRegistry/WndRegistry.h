// Config.h

#ifndef CRegistry_H
#define CRegistry_H

#include <windows.h>
#include <stdio.h>
#include "StdString.h"
#include "ConfigInterface.h"

// Class to manage the Windows Registry.
class CRegistry : public IConfig
{
	// Path to the key, i. e. "HKEY_LOCAL_MACHINE\SOFTWARE\Voxage".
	char sPath[256];

	// Action to take in the operations like read, write, create, etc.
	unsigned long ulAction;

	// Handle to manage the key.
	HKEY hKey;

  char cKeyName[256];
public:

	// Parameters:
	//	none.
	// Return Value:
	//	none.
	// Description:
	//	Constructor.
	CRegistry(const char * cPath = NULL);

	// Parameters:
	//	none.
	// Return Value:
	//	none.
	// Description:
	//	Destructor.
	~CRegistry();

	// Parameters:
	//	spath	- [out] Pointer to the buffer that receives the retrieved path.
	//	usize	- [in] Specifies the size, in bytes, of the buffer pointed to by the spath parameter.
	// Return Value:
	//	The return value is zero if the function suceeds or non-zero if the function fails.
	// Description:
	//	The GetPath function gets the path to the key.
	int GetPath( char *spath, unsigned int usize );

	// Parameters:
	//	spath	- [in] Pointer to the null-terminated CStdString specifying the name of the path to be set.
	// Return Value:
	//	The return value is zero if the function suceeds or non-zero if the function fails.
	// Description:
	//	The SetPath function sets the path to the key.
	int SetPath( const char *spath );

	// Parameters:
	//	skey		- [in] Pointer to the null-terminated CStdString specifying the name of the key to be retrieved.
	//	svalue	- [out] Pointer to the buffer that receives the retrieved key value.
	//	ulsize	- [in] Specifies the size, in bytes, of the buffer pointed to by the svalue parameter.
	//	type		- [in] Specifies the type of the value to be retrieved. The default value is REG_SZ.
	// Return Value:
	//	The return value is zero if the function suceeds or non-zero if the function fails.
	// Description:
	//	The GetKey function gets the key value located at the path previously set.
	int GetKey( const char *skey, char *svalue, unsigned long ulsize, DWORD type = REG_SZ );

	// Parameters:
	//	skey		- [in] Pointer to the null-terminated CStdString specifying the name of the key to be retrieved.
	//	svalue	- [in] Pointer to the null-terminated CStdString specifying the value of the key to be set.
	//	ulsize	- [in] Specifies the size, in bytes, of the buffer pointed to by the svalue parameter.
	//	type		- [in] Specifies the type of the value to be retrieved. The default value is REG_SZ.
	// Return Value:
	//	The return value is zero if the key already exists or 1 if the key was created. The return value is less than zero if the function fails.
	// Description:
	//	The SetKey function sets the key value located at the path previously set.
	int SetKey( const char *skey, const char *svalue, unsigned int usize = 0, DWORD type = REG_SZ );

	// Parameters:
	//	skey		- [in] Pointer to the null-terminated CStdString specifying the name of the key to be deleted.
	// Return Value:
	//	The return value is zero if the function suceeds or non-zero if the function fails.
	// Description:
	//	The DeleteKey function deletes the key value located at the path previously set.
	int DeleteKey( const char *skey );

  int DeletePath( );

  void SetKeyName(const char * sKey);
  const char* GetKeyName(void);

	void GetValue(const char *sValue, const char *sDefaultValue, unsigned short &Value);
  void GetValue(const char *sValue, const char *sDefaultValue, int &Value);
  void GetValue(const char *sValue, const char *sDefaultValue, bool &Value);
  void GetValue(const char *sValue, const char *sDefaultValue, char *Value);
  void GetValue(const char *sValue, const char *sDefaultValue, char& Value);
  void GetValue(const char *sValue, const char *sDefaultValue, CStdString &Value);
  void GetValue(const char *sValue, const char *sDefaultValue);
};

#endif // CRegistry_H
