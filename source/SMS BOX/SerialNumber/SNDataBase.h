#pragma once

#include <windows.h>
#include "SmartDB.h"
#include "StdString.h"

class CSNDataBase{
private:
  CSmartDB * db;
  CSmartDBRecordSet * rs;
  CStdString sDataBaseName;

public:
  CSNDataBase(const char * cDBN);
  
  BYTE  IsOpen( void );
  BYTE  UpdateSerialNumber( void );
  DWORD GetLastSerialNumber( void );
  DWORD GetNextSerialNumber( void );

  BYTE  InsertVersions( DWORD dwSerialNumber, const char * cFWVersion, const char * cHWVersion, const char * cFilePath );
  BYTE  InsertCustomer( DWORD dwSerialNumber, const char * cCustomerName );
  BYTE  VerifySerialNumber( DWORD dwSerialNumber );

  virtual ~CSNDataBase(void);
};
