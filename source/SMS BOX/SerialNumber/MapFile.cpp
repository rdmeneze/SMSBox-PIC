#include "MapFile.h"
#include "StdString.h"
#include "funcoes.h"

CMapFile::CMapFile(const char * cFileName){
  CStdString sFileName( cFileName );

  if ( sFileName.GetLength() ){
    fIn.open( sFileName.c_str() );
  }
}

//--------------------------------------------------------------

CMapFile::~CMapFile(void){
  if ( fIn.is_open() == true ){
    fIn.close();
  }
  return;
}

//--------------------------------------------------------------

BYTE CMapFile::GetObjectAddress( const char * cObjName, DWORD * addr ){
  CStdString sAux;
  CStdString sFindObj;
  int i;
  char cBuffer[512];
  int j;
  DWORD dwRet;

  if ( fIn.bad() == true ){
    return FALSE;
  }

  sFindObj.Format( " %s ", cObjName );
  while( fIn.eof() == false ){
    fIn.getline( cBuffer, sizeof( cBuffer ) );

    sAux = cBuffer;

    if ( sAux.find( sFindObj.c_str() ) != std::string::npos ){
      break;
    }
  }

  if ( fIn.eof() ){
    return FALSE;
  }

  i = sAux.find_first_of( "0x" );
  if ( i == std::string::npos ){
    return -1;
  }
  i+= 2;

  j = sAux.find_first_of( " ", i ); 

  sFindObj = sAux.substr( i, j-i );


  dwRet = atohex( sFindObj.c_str() );

  *addr = dwRet;

  return TRUE;
}

//--------------------------------------------------------------