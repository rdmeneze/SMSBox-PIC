
#include "status.h"
#include "serialNumber.h"

//-------- local variables --------

WORD  status = 0x0000;
BYTE  devID = -1;
DWORD dwSN = -1;

//----------------------------------------

void SetStatus( WORD st ){
  status |= st;
}

//----------------------------------------

void CleanStatus( WORD st ){
  status &= ~st;
}

//----------------------------------------

WORD GetStatus (void){
  return status;
}

//----------------------------------------

BYTE GetID ( void ){
  
  if ( dwSN == -1 ){
    dwSN = GetSerialNumber( );
    devID = (BYTE)dwSN;
  }
  
  //return devID;
  return 1;
}

//----------------------------------------
