#ifndef __SERIALNUMBER__
#define __SERIALNUMBER__

#include <windows.h>
#include "StdString.h"

class CSerialNumber{

public:
  CSerialNumber( void );

  BYTE doFiles( void );

  virtual ~CSerialNumber(void);
};

#endif