#include "serialnumber.h"
#include "prgmem_access.h"

//---------------------------------------------

BYTE bIni = FALSE;
DWORD dwSerialNumber;

const rom DWORD SerialNumber = 666;

//---------------------------------------------

DWORD GetSerialNumber( void )
{
  if ( bIni == FALSE )
  {
    memprg_read( (void*)&dwSerialNumber, (DWORD)&SerialNumber, sizeof( SerialNumber ));
    bIni = TRUE;
  }

  return dwSerialNumber;
}

//---------------------------------------------

