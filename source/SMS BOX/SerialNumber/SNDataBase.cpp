#include "SNDataBase.h"
#include <stdio.h>

//--------------------------------------------------------

CSNDataBase::CSNDataBase(const char * cDBN){
  sDataBaseName = cDBN;
  
  db = new CSmartDB();
  rs = new CSmartDBRecordSet();
  
  if ( sDataBaseName.GetLength() ){
    db->Connect( sDataBaseName.c_str() );
  }

  rs->Open( _T( "SELECT * FROM SQLITE_MASTER WHERE Type='table' and name = 'TSerialNumber'" ), db ); 

  if ( rs->RecordCount() == 0 ){
    if ( db->Execute( _T(" CREATE TABLE [TSerialNumber] ( \
                        [SerialNumber] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT, \
                        [Date] TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL )") ) != 0 ) {
      rs->Close();
      return;
    }
  }

  rs->Open( _T( "SELECT * FROM SQLITE_MASTER WHERE Type='table' and name = 'TSerialNumber_Consumer'" ), db ); 

  if ( rs->RecordCount() == 0 )
  {
    if ( db->Execute( _T("CREATE TABLE [TSerialNumber_Consumer] ( \
                          [SerialNumber] INTEGER  NOT NULL, \
                          [Consumer] VARCHAR(256)  NULL \
                          ) " ) ) != 0 )
    {
      rs->Close();
      return;
    }
  }

  rs->Open( _T( "SELECT * FROM SQLITE_MASTER WHERE Type='table' and name = 'TSerialNumber_Versions'" ), db ); 

  if ( rs->RecordCount() == 0 )
  {
    if ( db->Execute( _T("CREATE TABLE [TSerialNumber_Versions] ( \
                          [SerialNumber] INTEGER  NOT NULL, \
                          [FirmwareVersion] VARCHAR(32)  NULL, \
                          [HardwareVersion] VARCHAR(32)  NULL, \
                          [UpdateDate] VARCHAR(32)  NULL, \
                          [FilePath] VARCHAR(512)  NULL \
                          )" ) ) != 0 )
    {
      rs->Close();
      return;
    }
  }

  rs->Close();
  return;
}

//--------------------------------------------------------

CSNDataBase::~CSNDataBase(void){
  rs->Close();

  if ( db->IsConnected() ){
    db->Close();
  }

  delete db;
  delete rs;
}

//--------------------------------------------------------
  
BYTE CSNDataBase::UpdateSerialNumber( void ){
  if ( db->Execute( _T("INSERT INTO TSerialNumber DEFAULT VALUES") ) != 0 ){
    return FALSE;
  }
  return TRUE;
}

//--------------------------------------------------------

DWORD CSNDataBase::GetLastSerialNumber( void ){
  DWORD dwRet;
  WORD wRet;

  wRet = rs->Open( _T("SELECT MAX(SerialNumber) from TSerialNumber") , db );
  
  if ( wRet != RSOPEN_SUCCESS ){
    return 0;
  }

  if ( rs->RecordCount() == 0 ){
    dwRet = 0;
  }
  else{
    dwRet = atoi( (LPCSTR)rs->GetColumnString( 0 ) );
  }

  rs->Close();

  return dwRet;
}

//--------------------------------------------------------

DWORD CSNDataBase::GetNextSerialNumber( void )
{
  return GetLastSerialNumber() + 1;
}

//--------------------------------------------------------

BYTE CSNDataBase::IsOpen( void ){
  return (db->IsConnected() == TRUE);
}

//--------------------------------------------------------


BYTE  CSNDataBase::InsertVersions( DWORD dwSerialNumber, const char * cFWVersion, const char * cHWVersion , const char * cFilePath)
{
  DWORD dwRet;
  CStdString sSQL; 

  sSQL = "INSERT INTO TSerialNumber_Versions ( serialNumber, FirmwareVersion, HardwareVersion, UpdateDate, FilePath ) \n \
                 SELECT TSerialNumber.SerialNumber , \n \
                           '%s', \n \
                           '%s', \n \
                           TSerialNumber.Date, \n \
                           '%s' \n \
                  FROM  TSerialNumber \n \
                  WHERE TSerialNumber.SerialNumber = %d /*dwSerialNumber*/ \n \
                  LIMIT 1";

  sSQL.Format( (LPCSTR)sSQL, cFWVersion, cHWVersion, cFilePath, dwSerialNumber );

  dwRet = db->Execute( (LPCSTR)sSQL );
  if ( dwRet != RSOPEN_SUCCESS )
  {
    return FALSE;
  }

  return TRUE;
}

//--------------------------------------------------------

BYTE  CSNDataBase::InsertCustomer( DWORD dwSerialNumber, const char * cCustomerName )
{
  DWORD dwRet;
  CStdString sSQL; 

  sSQL = "INSERT  INTO TSerialNumber_Consumer (SerialNumber, Consumer) \
                  SELECT TSerialNumber.SerialNumber , \
                         '%s' \
                  FROM  TSerialNumber \
                  WHERE TSerialNumber.SerialNumber = %d /*dwSerialNumber*/ \
                  LIMIT 1";

  sSQL.Format( (LPCSTR)sSQL, cCustomerName, dwSerialNumber );

  dwRet = db->Execute( (LPCSTR)sSQL );
  if ( dwRet != RSOPEN_SUCCESS )
  {
    return FALSE;
  }

  return TRUE;
}

//--------------------------------------------------------

BYTE  CSNDataBase::VerifySerialNumber( DWORD dwSerialNumber )
{
  DWORD dwRet;
  CStdString sSQL;
  BYTE bRetVal = TRUE;

  sSQL = "SELECT COUNT(*) FROM TSerialNumber WHERE TSerialNumber.SerialNumber = %d";

  sSQL.Format( (LPCSTR)sSQL, dwSerialNumber );

  dwRet = rs->Open( (LPCSTR)sSQL, db );
  if ( dwRet != RSOPEN_SUCCESS )
  {
    return FALSE;
  }

  if ( rs->RecordCount() == 0 )
  {
    bRetVal = FALSE;
  }
  else
  {
    dwRet = atoi( (LPCSTR)rs->GetColumnString( 0 ) );
    if ( !dwRet )
    {
      bRetVal = FALSE;
    }
  }

  rs->Close();
  return bRetVal;
}
