#include "IntelHexFile.h"
#include "StdString.h"
#include "funcoes.h"
#include <fstream>

using namespace std;

#define LINE_LEN 64

//------------------------------------------------
BYTE CalcCRC( const char * cLine  );
//------------------------------------------------

CIntelHexFile::CIntelHexFile(const char * cFileName){

  sFileName = cFileName;
  if ( sFileName.GetLength() ){
    Parse();
    Dump();
  }
  return;
}

//------------------------------------------------

CIntelHexFile::~CIntelHexFile(void){
}

//------------------------------------------------

BYTE CIntelHexFile::Open( const char * cFileName ){

  _MAPHexFile::iterator it;
  if ( sFileName.GetLength()){
    sFileName = cFileName;

    _mHexFile.clear();
  } 

  Parse();
  Dump();
  return TRUE;
}

//------------------------------------------------

const char * CIntelHexFile::GetFileName( void ){
  return (const char*) sFileName.c_str();
}

//------------------------------------------------

void CIntelHexFile::Close( void ){
  sFileName.clear();
  return;
}

//------------------------------------------------

BYTE CIntelHexFile::GetValue( DWORD address, char * cBufIn, size_t nBytes ){
  int i;
  int j;
  BYTE nLinBytes;
  char cBuffer[512];
  CStdString sCurrLine;
  CStdString sAddr;
  CStdString sTmp;
  BYTE bCRC;
  fstream fIn;
  DWORD iniAddr;

  fIn.open( sFileName.c_str(), ios_base::in );

  if ( fIn.bad() == true ){
    return FALSE;
  }

  sAddr.Format( "%x", address );
  fIn.seekg( ios_base::beg, 0 );

  while( fIn.eof() == false ){
    fIn.getline( cBuffer, sizeof( cBuffer ) );

    sCurrLine = cBuffer;

    sTmp = sCurrLine.substr( 1, 2 );
    nLinBytes = (BYTE)atohex( sTmp.c_str() );

    bCRC = CalcCRC( sCurrLine.c_str() );

    sTmp = sCurrLine.substr( 3, 4 );
    //if ( sTmp.find( sAddr.c_str() ) != string::npos ){
    //  break;

    iniAddr = atohex( (LPCSTR)sTmp );
    if ( (iniAddr <= address) && (address < (iniAddr + nLinBytes)) )
    {
      break;
    }
  }

  if ( fIn.eof() ){
    fIn.close();
    return FALSE;
  }

  if ( (nBytes / 2) > nLinBytes ){
    fIn.close();
    return FALSE;
  }

  sAddr.clear();

  j = 9 + (( address - iniAddr )<<1);
  nLinBytes = 0;
  memset( cBuffer, 0, sizeof( cBuffer ));
  for ( i = 0; i < (int)(nBytes); i+=2 ){
    sAddr = sCurrLine.substr( j, 2);
    j += 2;
    cBuffer[nBytes - nLinBytes - 2] = sAddr.GetAt( 0 );
    cBuffer[nBytes - nLinBytes - 1] = sAddr.GetAt( 1 );

    nLinBytes += 2;
  }
  
  memcpy( cBufIn, cBuffer, nBytes );
  cBufIn[nBytes] = 0;

  fIn.close();
  return TRUE;
}

//------------------------------------------------

BYTE CIntelHexFile::SetValue( DWORD address, char * cBufIn, size_t nBytes ){
  BYTE bCRC;
  int i;
  BYTE nLinBytes;
  char cBuffer[512];
  CStdString sAux;
  CStdString sAddr;
  CStdString sTmp;
  long pos;

  fstream fOut;

  fOut.open( sFileName.c_str(), ios_base::in | ios_base::out );

  if ( fOut.bad() ){
    return FALSE;
  }

  sAddr.Format( "%X", address );

  while( fOut.eof() == false ){
    pos = fOut.tellg( );
    fOut.getline( cBuffer, sizeof( cBuffer ) );

    if ( fOut.eof() ){
      break;
    }
      
    sAux = cBuffer;

    try{
      sTmp = sAux.substr( 1, 2 );
    }
    catch(...){
      continue;
    }

    nLinBytes = (BYTE)atohex( sTmp.c_str() );

    sTmp = sAux.substr( 3, 4 );
    if ( sTmp.find( sAddr.c_str() ) != string::npos ){
      break;
    }
  }

  if ( fOut.eof() ){
    fOut.close();
    return FALSE;
  }

  sprintf( cBuffer, sAux.c_str() );
  for ( i = 0; i < (int)(nBytes); i+=2 ){
    cBuffer[ 9 + (nBytes - i - 2 )] = cBufIn[i];
    cBuffer[ 9 + (nBytes - i - 1 )] = cBufIn[i+1];
  }

  sAux = cBuffer;

  bCRC = CalcCRC( sAux.c_str() );

  sprintf( &cBuffer[9+nLinBytes*2],"%02X\n", bCRC ); 

  fOut.seekp( -1*(nLinBytes*2+4) , ios_base::cur );
  fOut.write( &cBuffer[9], nLinBytes*2+3 );
  fOut.close();
  
  return TRUE;
}

//------------------------------------------------

BYTE CIntelHexFile::Parse( void ){
  fstream fIn;
  char cBuffer[512];
  BYTE bData[255];
  CStdString sAux;
  BYTE bLineCode;
  WORD wHighAddr;
  WORD wLowAddr;
  BYTE bDataLen;
  BYTE bCRC;
  int i;
  DWORD mapEntryAddr;
  _MAPHexFile::iterator itHexFile;
  std::deque<BYTE> qLine;
  
  fIn.open( sFileName.c_str(), ios_base::in );

  if ( fIn.is_open() == false ){
    return FALSE;
  }

  while ( fIn.eof() == false ){
    fIn.getline( cBuffer, sizeof( cBuffer ) );

    if ( fIn.eof() ){
      break;
    }

    sAux =  cBuffer;
    if ( sAux[0] == ':' ){

      try{
        bDataLen  = (BYTE)atohex( sAux.substr( 1, 2 * sizeof( BYTE )).c_str() );
        wLowAddr  = (WORD)atohex( sAux.substr( 3, 2 * sizeof( WORD )).c_str() );
        bLineCode = (BYTE)atohex( sAux.substr( 7, 2 * sizeof( BYTE )).c_str() );
        bCRC      = (BYTE)atohex( sAux.substr( 9 + (bDataLen * 2), 2 * sizeof( BYTE )).c_str() );

        if (bCRC != CalcCRC( sAux.c_str() )) {
          fIn.close();
          return FALSE;
        }
      }
      catch(...){
        fIn.close();
        return FALSE;
      }

      switch( bLineCode ){
        case 0x00:
          for ( i = 0; i < bDataLen; i++ ){
            bData[i] = (BYTE)atohex( sAux.substr( 9 + i*2, 2 * sizeof( BYTE )).c_str() );
          }
          break;

        case 0x01:
          break;

        case 0x04:
          wHighAddr = (WORD)atohex( sAux.substr( 9, 2 * sizeof( WORD )).c_str() );
          continue;

        default:
          fIn.close();
          return FALSE;
      }

      if ( bLineCode == 0x01 ){
        break;
      }

      for ( i = 0; i < bDataLen; i++ ){

        mapEntryAddr = MAKELONG( ( wLowAddr + i ) & (-LINE_LEN), wHighAddr );
        
        itHexFile = _mHexFile.find( mapEntryAddr );
        if ( itHexFile == _mHexFile.end() ){ 
          _mHexFile.insert( _MAPHexFile :: value_type( mapEntryAddr , qLine	));   
        }

        itHexFile = _mHexFile.find( mapEntryAddr );
        itHexFile->second.push_back( bData[i] );
      }
    }
    else{
      fIn.close();
      return FALSE;
    }
  }

  fIn.close();
  return TRUE;
}

//------------------------------------------------

void CIntelHexFile::Dump( void ){

  _MAPHexFile::iterator itHexFile;
  std::deque<BYTE> qLine;
  BYTE bMemType;
  BYTE bLastMemType = -1;
  char cBuffer[512];
  int iCounter;

  std::fstream fOut;
  fOut.open( "PRG.dmp", ios_base::out );
  fOut.close();

  fOut.open( "UID.dmp", ios_base::out );
  fOut.close();

  fOut.open( "CONFIG.dmp", ios_base::out );
  fOut.close();

  fOut.open( "EEDAT.dmp", ios_base::out );
  fOut.close();

  for ( itHexFile = _mHexFile.begin(); itHexFile != _mHexFile.end(); itHexFile++ ){

    bMemType = LOBYTE( HIWORD( itHexFile->first ));

    if ( bMemType >= 0x00 && bMemType <= 0x1F ){
      if ( bLastMemType != bMemType ){
        if ( fOut.is_open() == true ){
          fOut.close();
        }
        fOut.open( "PRG.dmp", ios_base::out | ios_base::app );
        bLastMemType = bMemType;
      }
    }

    if ( bMemType ==  0x20 ){
      if ( bLastMemType != bMemType ){
        if ( fOut.is_open() == true ){
          fOut.close();
        }
        fOut.open( "UID.dmp", ios_base::out | ios_base::app);
        bLastMemType = bMemType;
      }
    }

    if ( bMemType == 0x30 ){
      if ( bLastMemType != bMemType ){
        if ( fOut.is_open() == true ){
          fOut.close();
        }
        fOut.open( "CONFIG.dmp", ios_base::out | ios_base::app);
        bLastMemType = bMemType;
      }
    }

    if ( bMemType == 0xF0 ){
      if ( bLastMemType != bMemType ){
        if ( fOut.is_open() == true ){
          fOut.close();
        }
        fOut.open( "EEDAT.dmp", ios_base::out | ios_base::app);
        bLastMemType = bMemType;
      }
    }

    iCounter = 0;
    iCounter += sprintf( cBuffer, "%06X : ", itHexFile->first );
    for ( int i = 0; i < (int)itHexFile->second.size(); i++ ){
      iCounter += sprintf( &cBuffer[iCounter], "%02X ", itHexFile->second[i] );
    }
    sprintf( &cBuffer[iCounter], "\n" );

    if ( fOut.is_open() ){
      fOut << cBuffer; 
    }
  }

  return;
}

//------------------------------------------------

BYTE CalcCRC( const char * cLine  ){
  BYTE bCRC = 0;
  CStdString sAux;
  CStdString sTmp;
  int i;

  sAux = cLine;

  for ( i = 1; i < sAux.GetLength()-2; i+=2 ){
    sTmp = sAux.substr( i, 2 );
    bCRC += (BYTE)atohex( sTmp.c_str() );
  }
  bCRC = -bCRC;

  return (bCRC);
}

//------------------------------------------------
