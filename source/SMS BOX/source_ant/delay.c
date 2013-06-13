#include "timer.h"

//------------------------------------------------

void delay( DWORD dwTime ){
  BYTE bTime;
  
  bTime = GetTimer( dwTime );
  while ( !IsTimerTimeOut( bTime ) );
  ReleaseTimer( &bTime );
  
  return;
}

//------------------------------------------------
