#pragma once

#include <windows.h>
#include <fstream>
#include "StdString.h"

class CMapFile {
private:
  std::ifstream fIn;
public:
  CMapFile(const char * cFileName);
  BYTE GetObjectAddress( const char * cObjName, DWORD * addr );
  virtual ~CMapFile(void);
};
