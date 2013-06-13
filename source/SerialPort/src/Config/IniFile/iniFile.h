// IniFile.cpp:  Implementation of the CIniFile class.
// Written by:   Adam Clauss
// Email: cabadam@tamu.edu
// You may use this class/code as you wish in your programs.  Feel free to distribute it, and
// email suggested changes to me.
//
// Rewritten by: Shane Hill
// Date:         21/08/2001
// Email:        Shane.Hill@dsto.defence.gov.au
// Reason:       Remove dependancy on MFC. Code should compile on any
//               platform. Tested on Windows/Linux/Irix
//
// Reedited by Rafael Dias Menezes
// Date:         Ago/2009
// Email:        rdmeneze@yahoo.com.br
// Reason:       Add the CStdString class.
//////////////////////////////////////////////////////////////////////

#ifndef CIniFile_H
#define CIniFile_H

#include <stdlib.h>
#include "StdString.h"
#include "ConfigInterface.h"

#include <vector>

using namespace std;

#define MAX_KEYNAME    128
#define MAX_VALUENAME  128
#define MAX_VALUEDATA 2048

class CIniFile  : public IConfig
{
private:
  bool   caseInsensitive;
  CStdString path;
  //[10082009<]
  CStdString  sKeyName;
  //[10082009>]
  struct key {
    vector<CStdString> names;
    vector<CStdString> values; 
    vector<CStdString> comments;
  };
  vector<key>    keys; 
  vector<CStdString> names; 
  vector<CStdString> comments;
  CStdString CheckCase( CStdString s) const;

public:
  enum errors{ noID = -1};
  CIniFile( const CStdString iniPath = "");
  ~CIniFile();

  // Sets whether or not keynames and valuenames should be case sensitive.
  // The default is case insensitive.
  void CaseSensitive()                           {caseInsensitive = false;}
  void CaseInsensitive()                         {caseInsensitive = true;}

  void SetKeyName(const char * sKey) {sKeyName = sKey;}
  const char* GetKeyName(void) {return (const char*)sKeyName.c_str(); }

  // Sets path of ini file to read and write from.
  void Path(CStdString const newPath)                {path = newPath;}
  CStdString Path() const                            {return path;}
  void SetPath(CStdString const newPath)             {Path( newPath);}

  // Reads ini file specified using path.
  // Returns true if successful, false otherwise.
  bool ReadFile();
  
  // Writes data stored in class to ini file.
  bool WriteFile(); 
  
  // Deletes all stored ini data.
  void Erase();
  void Clear()                                   {Erase();}
  void Reset()                                   {Erase();}

  // Returns index of specified key, or noID if not found.
  long FindKey( const CStdString keyname) const;

  // Returns index of specified value, in the specified key, or noID if not found.
  long FindValue( unsigned const keyID, CStdString const valuename) const;

  // Returns number of keys currently in the ini.
  unsigned NumKeys() const                       {return names.size();}
  unsigned GetNumKeys() const                    {return NumKeys();}

  // Add a key name.
  unsigned AddKeyName( CStdString const keyname);

  // Returns key names by index.
  CStdString KeyName( unsigned const keyID) const;
  CStdString GetKeyName( unsigned const keyID) const {return KeyName(keyID);}

  // Returns number of values stored for specified key.
  unsigned NumValues( unsigned const keyID);
  unsigned GetNumValues( unsigned const keyID)   {return NumValues( keyID);}
  unsigned NumValues( CStdString const keyname);
  unsigned GetNumValues( CStdString const keyname)   {return NumValues( keyname);}

  // Returns value name by index for a given keyname or keyID.
  CStdString ValueName( unsigned const keyID, unsigned const valueID) const;
  CStdString GetValueName( unsigned const keyID, unsigned const valueID) const {
    return ValueName( keyID, valueID);
  }
  CStdString ValueName( CStdString const keyname, unsigned const valueID) const;
  CStdString GetValueName( CStdString const keyname, unsigned const valueID) const {
    return ValueName( keyname, valueID);
  }

  // Sets value of [keyname] valuename =.
  // Specify the optional paramter as false (0) if you do not want it to create
  // the key if it doesn't exist. Returns true if data entered, false otherwise.
  // Overloaded to accept CStdString, int, and double.
  bool SetValue( unsigned const keyID, unsigned const valueID, CStdString const value);
  bool SetValue( CStdString const keyname, CStdString const valuename, CStdString const value, bool const create = true);
  bool SetValueI( CStdString const keyname, CStdString const valuename, int const value, bool const create = true);
  bool SetValueB( CStdString const keyname, CStdString const valuename, bool const value, bool const create = true) {
    return SetValueI( keyname, valuename, int(value), create);
  }
  bool SetValueF( CStdString const keyname, CStdString const valuename, double const value, bool const create = true);
  bool SetValueV( CStdString const keyname, CStdString const valuename, char *format, ...);

  // Deletes specified value.
  // Returns true if value existed and deleted, false otherwise.
  bool DeleteValue( CStdString const keyname, CStdString const valuename);
  
  // Deletes specified key and all values contained within.
  // Returns true if key existed and deleted, false otherwise.
  bool DeleteKey(CStdString keyname);

  // Header comment functions.
  // Header comments are those comments before the first key.
  //
  // Number of header comments.
  unsigned NumHeaderComments()                  {return comments.size();}
  // Add a header comment.
  void     HeaderComment( CStdString const comment);
  // Return a header comment.
  CStdString   HeaderComment( unsigned const commentID) const;
  // Delete a header comment.
  bool     DeleteHeaderComment( unsigned commentID);
  // Delete all header comments.
  void     DeleteHeaderComments()               {comments.clear();}

  // Key comment functions.
  // Key comments are those comments within a key. Any comments
  // defined within value names will be added to this list. Therefore,
  // these comments will be moved to the top of the key definition when
  // the CIniFile::WriteFile() is called.
  //
  // Number of key comments.
  unsigned NumKeyComments( unsigned const keyID) const;
  unsigned NumKeyComments( CStdString const keyname) const;
  // Add a key comment.
  bool     KeyComment( unsigned const keyID, CStdString const comment);
  bool     KeyComment( CStdString const keyname, CStdString const comment);
  // Return a key comment.
  CStdString   KeyComment( unsigned const keyID, unsigned const commentID) const;
  CStdString   KeyComment( CStdString const keyname, unsigned const commentID) const;
  // Delete a key comment.
  bool     DeleteKeyComment( unsigned const keyID, unsigned const commentID);
  bool     DeleteKeyComment( CStdString const keyname, unsigned const commentID);
  // Delete all comments for a key.
  bool     DeleteKeyComments( unsigned const keyID);
  bool     DeleteKeyComments( CStdString const keyname);

  void GetValue(const char *sValue, const char *sDefaultValue, int &Value);
  void GetValue(const char *sValue, const char *sDefaultValue, bool &Value);
  void GetValue(const char *sValue, const char *sDefaultValue, char *Value);
  void GetValue(const char *sValue, const char *sDefaultValue, CStdString &Value);

	void GetValue(const char *sValue, const char *sDefaultValue, unsigned short &Value);
	void GetValue(const char *sValue, const char *sDefaultValue, char& Value);
};

#endif
