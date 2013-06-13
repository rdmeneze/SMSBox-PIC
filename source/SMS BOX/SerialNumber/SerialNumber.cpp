#include "Config.h"
#include "inifile.h"
#include "MapFile.h"
#include "IntelHexFile.h"
#include "funcoes.h"
#include "CSerialNumber.h"
#include "SNDataBase.h"
#include <vector>

CSerialNumber::CSerialNumber( void ) {
  return;
}

BYTE CSerialNumber::doFiles( void ) {
  CStdString sQuery;
  CSNDataBase * database = NULL;
  CIniFile * iniFile;
  CStdString sWorkDir;
  CStdString sProject;
  CStdString sDBFile;
  CStdString sDestFileName;
  int  nCopy;
  DWORD curSerialNumber;
  DWORD dwAddr;
  DWORD dwAddrBoardVersion;
  DWORD dwAddrFirmwareVersion;
  char cBuffer[9];
  char cIniParam[64];
  int iStartBoard = 0;
  std::vector<int> lstBoards;
  int iUpdate;
  CStdString sFirmwareVersion;
  CStdString sHardwareVersion;
  CStdString sCustomer;

  char cFirmwareVersion[9];
  char cBoardVersion[9];
  

  iniFile = new CIniFile( "serialNumber.ini" );
  iniFile->SetKeyName( "GENERAL" );
  iniFile->GetValue( "WORKDIR", ".", cIniParam );
  sWorkDir = cIniParam;
  iniFile->GetValue( "PROJECT", "SMS BOX", cIniParam );
  sProject = cIniParam;
  iniFile->GetValue( "DBFILE", "serialNumber.sqlite", cIniParam );
  sDBFile = cIniParam;
  iniFile->GetValue( "COPIES", "10", cIniParam );
  nCopy     = atoi( cIniParam );
  iniFile->GetValue( "STARTBOARD", "0", iStartBoard );

  iniFile->GetValue( "UPDATE", "NO", cIniParam );

  _strupr( cIniParam );
  if ( (strcmp( cIniParam, "YES" ) != 0) && 
       (strcmp( cIniParam, "NO" ) != 0) ){
    strncpy( cIniParam, "NO", sizeof( "NO" ) );
  }

  iUpdate = strcmp( cIniParam, "YES" ) == 0 ? 1: 0;

  iniFile->GetValue( "BOARDS", "", cIniParam );
  ParseIntList( cIniParam, lstBoards );

  iniFile->GetValue( "FW_VERSION", "1.00.00.00", cIniParam );
  sFirmwareVersion = cIniParam;

  iniFile->GetValue( "HW_VERSION", "1.00.00.00", cIniParam );
  sHardwareVersion = cIniParam;

  iniFile->GetValue( "CUSTOMER", "VoxAge", cIniParam );
  sCustomer = cIniParam;

  delete iniFile;

  if ( sDBFile.GetLength() ){
    database = new CSNDataBase( sDBFile.c_str() );
  }
  else{
    return FALSE;
  }
  
  if ( database->IsOpen() == FALSE ){
    return FALSE;
  }

  sQuery.Format( "%s.map", sProject.c_str() );
  CMapFile mapFile( (char*)sQuery.c_str() );

  sQuery.Format( "%s.hex", sProject.c_str() );
  CIntelHexFile intelHex( (char*)sQuery.c_str() );

  mapFile.GetObjectAddress( "SerialNumber", &dwAddr );

  if ( mapFile.GetObjectAddress( "BoardVersion", &dwAddrBoardVersion ) == TRUE )
  {
    if ( intelHex.GetValue( dwAddrBoardVersion, cBoardVersion, sizeof( cBoardVersion ) - 1 ) == TRUE )
    {
      sHardwareVersion.clear();
      for( nCopy = 0; nCopy < 3; nCopy++ )
      {
        memset( cBuffer, 0, 4 );
        memcpy( cBuffer, &cBoardVersion[nCopy<<1], 2 );
        sHardwareVersion += (CStdString)(cBuffer);
        sHardwareVersion += ".";
      }

      memset( cBuffer, 0, 4 );
      memcpy( cBuffer, &cBoardVersion[nCopy<<1], 2 );
      sHardwareVersion += (CStdString)(cBuffer);
    }
  }

  if ( mapFile.GetObjectAddress( "FirmwareVersion", &dwAddrFirmwareVersion ) == TRUE )
  {
    if ( intelHex.GetValue( dwAddrFirmwareVersion, cFirmwareVersion, sizeof( cFirmwareVersion ) - 1 ) == TRUE )
    {
      //sFirmwareVersion = cFirmwareVersion;
      sFirmwareVersion.clear();
      for( nCopy = 0; nCopy < 3; nCopy++ )
      {
        memset( cBuffer, 0, 4 );
        memcpy( cBuffer, &cFirmwareVersion[nCopy<<1], 2 );
        sFirmwareVersion += (CStdString)(cBuffer);
        sFirmwareVersion += ".";
      }

      memset( cBuffer, 0, 4 );
      memcpy( cBuffer, &cFirmwareVersion[nCopy<<1], 2 );
      sFirmwareVersion += (CStdString)(cBuffer);
    }
  }

  if ( iUpdate == 1 )
  {
    nCopy = lstBoards.size();
  }

  for ( int i = 0; i < nCopy; i++ ){

    if ( iUpdate == 0 )
    {
      curSerialNumber = database->GetNextSerialNumber();
    }
    else
    {
      curSerialNumber = lstBoards[i];
      if (database->VerifySerialNumber( curSerialNumber ) == FALSE )
      {
        curSerialNumber = database->GetNextSerialNumber();
      }
    }

    sprintf( cBuffer, "%08X", curSerialNumber );

    sQuery.Format( "%s.hex", sProject.c_str() );

    sDestFileName.Format( "%s_%08d_%011s_%011s.hex", sProject.c_str(), atohex( cBuffer ), (LPCSTR)sHardwareVersion, (LPCSTR)sFirmwareVersion);

    if ( intelHex.SetValue( dwAddr, cBuffer, sizeof( cBuffer ) - 1 ) == FALSE ){
      continue;
    }

    if (database->VerifySerialNumber( curSerialNumber ) == FALSE )
    {
      if ( database->UpdateSerialNumber() == FALSE )
      {
        return FALSE;
      }
    }

    if ( database->InsertVersions( curSerialNumber,  (LPCSTR)sFirmwareVersion, (LPCSTR)sHardwareVersion, (LPCSTR)sDestFileName) == FALSE )
    {
      return FALSE;
    }

    if ( database->InsertCustomer( curSerialNumber, (LPCSTR)sCustomer ) == FALSE )
    {
      return FALSE;
    }


    if ( CopyFile( sQuery.c_str(), sDestFileName.c_str(), TRUE ) == FALSE ){
      return FALSE;
    }
  }

  return TRUE;
}

CSerialNumber::~CSerialNumber( void ) {

  return;
}
