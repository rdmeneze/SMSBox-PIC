#pragma once

#include <windows.h>
#include "StdString.h"
#include <map>
#include <deque>


typedef std::map< DWORD, std::deque<BYTE> > _MAPHexFile;

class CIntelHexFile
{
private:
  CStdString sFileName;
  BYTE Parse( void );

  _MAPHexFile _mHexFile;

public:
  CIntelHexFile( const char * cFileName = NULL );
  BYTE Open( const char * cFileName );
  void Close( void );
  inline const char * GetFileName( void );
  BYTE GetValue( DWORD address, char * cBufIn, size_t nBytes );
  BYTE SetValue( DWORD address, char * cBufIn, size_t nBytes );
  void Dump( void );
  virtual ~CIntelHexFile(void);
};
