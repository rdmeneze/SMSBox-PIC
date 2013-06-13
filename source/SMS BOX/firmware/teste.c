#include "sw_uart.h"
#include "serialPC.h"
#include "timer.h"

char BufferTest[75];

char counterTest;
char timerTest;


void InitTest( void ){
  timerTest = GetTimer( 5000 );
  counterTest = 0;   
  OpenUART();
}

void ParseSerialChar( BYTE bTmp ){
  BufferTest[counterTest] = bTmp; 
  RestartTimer( timerTest, 5000 );
  counterTest++;
}


void TesteProcessa( void ){
  if ( counterTest ){
    if ( (IsTimerTimeOut( timerTest ) == TRUE) || (counterTest == sizeof( BufferTest )) ){
      enviarPacotePC( (BYTE*)BufferTest, counterTest );    
      counterTest = 0;
    }   
  }
}
