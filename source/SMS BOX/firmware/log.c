#include "log.h"
#include "e2prom.h"
#include <string.h>
#include "FlashEprom_loc.h"
#include "FlashEprom.h"
#include "funcoes.h"

//-----------------------

#define LOG_SAVE_PTR_NONE 0
#define LOG_SAVE_PTR_STA  1
#define LOG_SAVE_PTR_END  2

//-----------------------

void WriteLog2Flash( struct LogBuffer * logPtr );
void IncLogPtrStart( void );
void IncLogPtrEnd( void );
void ScaleLogPtr(BYTE bSave);

//---- module locals ----

BYTE bInit = FALSE;
DWORD logPtrSta;          //! ponteiro para o último registro de log da memória flash externa lido pelo Host
DWORD logPtrEnd;          //! ponteiro para o último registro de log da memória flash externa escrito pelo SMS Box
BYTE  bLogLevel;          //! log level
WORD  wLogStamp;
#pragma udata LOG_BUFFER
struct LogBuffer logBuffer;
#pragma udata

//-----------------------

void LogInit( void ){

  if ( bInit == TRUE ){
    return;
  }

  FlashInit( );

  bInit = TRUE;

  e2prom_read( (BYTE*)&logPtrSta, LOG_PTR_STA_ADDR, sizeof( DWORD ));
  e2prom_read( (BYTE*)&logPtrEnd, LOG_PTR_END_ADDR, sizeof( DWORD ));

  ScaleLogPtr(LOG_SAVE_PTR_NONE);

  e2prom_read( (BYTE*)&wLogStamp, LOG_STAMP_ADDR, sizeof( WORD ));
  e2prom_read( (BYTE*)&bLogLevel, LOG_LEVEL_ADDR, sizeof( BYTE ));

  if ( bLogLevel > LOG_ALL ){
    bLogLevel = LOG_ALL;
    e2prom_write( (BYTE*)&bLogLevel, LOG_LEVEL_ADDR, sizeof( BYTE  ));
  }

  if ( bLogLevel > LOG_HW ) {
    bLogLevel = LOG_ALL;
  }
  return;
}

//-----------------------

void LogSetLevel( BYTE bLevel ){

  if ( bInit == FALSE ){
    LogInit();
  }

  bLogLevel = bLevel;  

  return;
}

//-----------------------

void Log( BYTE bCode, BYTE * bMsg, BYTE len ){

  BYTE bLogLen;
  if ( bInit == FALSE ){
    LogInit();
  }

  if ( bCode > EVT_USR ){
    return;
  } 

  bLogLen = len;
  if ( bLogLen > LOG_BUF_LEN )
  {
    bLogLen = LOG_BUF_LEN;
  }

  logBuffer.bCode = bCode;
  memcpy( (void*)logBuffer.bBuffer, (void*)bMsg, bLogLen * sizeof( BYTE ));
  logBuffer.bLen = bLogLen;

  WriteLog2Flash( &logBuffer );

  return;  
}

//--------------------------------

void WriteLog2Flash( struct LogBuffer * logPtr ){
  BYTE bLen;
  DWORD dwAddr;

  logPtr->wStamp = wLogStamp++;

  e2prom_write( (BYTE*)&wLogStamp, LOG_STAMP_ADDR, sizeof( WORD ));

  bLen = logPtr->bLen;
  bLen += (sizeof( logPtr->bCode ) + sizeof( logPtr->wStamp ) + sizeof( logPtr->bLen ));

  dwAddr = logPtrEnd * sizeof ( struct LogBuffer );
  dwAddr += FEE_LOG_ADDR;

  Flash_Write( (BYTE*)logPtr, dwAddr , bLen );
  
  IncLogPtrEnd( );
  return;
}

//--------------------------------

void IncLogPtrEnd( void ){

  logPtrEnd++;
  ScaleLogPtr(LOG_SAVE_PTR_END);

  return;
}

//--------------------------------

void IncLogPtrStart( void ){

  logPtrSta++;
  ScaleLogPtr(LOG_SAVE_PTR_STA);

  return;
}

//--------------------------------

void ScaleLogPtr(BYTE bSave){
  BYTE bUpdateE2Prom = 0x00;
  
  if ( logPtrSta > N_LOG_EVNT ){
    logPtrSta = 0;
    bUpdateE2Prom |= 0x01;
  } 

  if ( logPtrEnd > N_LOG_EVNT ){
    logPtrEnd = 0;
    bUpdateE2Prom |= 0x02;
  } 

  if ( (bUpdateE2Prom & 0x01) || (bSave == LOG_SAVE_PTR_STA) ){
    e2prom_write( (BYTE*)&logPtrSta, LOG_PTR_STA_ADDR, sizeof ( logPtrSta ));
  }

  if ( bUpdateE2Prom & 0x02 || ((bSave == LOG_SAVE_PTR_END)) ){
    e2prom_write( (BYTE*)&logPtrEnd, LOG_PTR_END_ADDR,  sizeof ( logPtrEnd ));
  }

  return;
}

//--------------------------------

BYTE GetLog( far void * LogPtr ){

  if ( logPtrSta != logPtrEnd ) {
    Flash_Read( (BYTE*)&logBuffer, FEE_LOG_ADDR + logPtrSta  * sizeof( struct LogBuffer ), sizeof( struct LogBuffer ) );

    if ( LogPtr != NULL ){
      LogPtr = &logBuffer;
    }

    IncLogPtrStart();
    return TRUE;
  }
  else{
    LogPtr = NULL;
  }

  return FALSE;
}

//--------------------------------

BYTE GetLogLevel( void ){
  return bLogLevel;
}

//--------------------------------
