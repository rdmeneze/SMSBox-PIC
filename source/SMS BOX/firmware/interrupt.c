#include "timer.h"
#include "serial.h"
#include "interrupt.h"
#include "sw_uart.h"
#include "SerialPC.h"
#include "modemGSM.h"
#include "vectors.h"
#include "prgmem_access.h"
#include "funcoes.h"

extern SERIALCOMFUNC   *isrSerialFunc;
extern SERIALCOMFUNC   *isrSerialFuncTX;

void InterruptHandler( void );
void InterruptHandlerLow( void );

void isr_HIGH_Vector(void);
void isr_LOW_Vector(void);

//------------------------------------------------------------------------------------
#pragma code high_vector=RM_HIGH_INTERRUPT_VECTOR
void interrupt_at_high_vector(void)
{
  //_asm GOTO InterruptHandler  _endasm
  _asm GOTO isr_HIGH_Vector  _endasm
}
#pragma code /* return to the default code section */
//------------------------------------------------------------------------------------
#pragma code low_vector=RM_LOW_INTERRUPT_VECTOR
void interrupt_at_low_vector(void)
{
  //_asm GOTO InterruptHandlerLow _endasm
  _asm GOTO isr_LOW_Vector _endasm
}
#pragma code /* return to the default code section */
//------------------------------------------------------------------------------------
#pragma code second_HIGH_ISR_Vector=SECOND_HIGH_ISR_VECTOR
void isr_HIGH_Vector(void)
{
  _asm GOTO InterruptHandler  _endasm
}
#pragma code
//------------------------------------------------------------------------------------
#pragma code second_LOW_ISR_Vector=SECOND_LOW_ISR_VECTOR
void isr_LOW_Vector(void)
{
  _asm GOTO InterruptHandlerLow  _endasm
}
#pragma code
//------------------------------------------------------------------------------------
#pragma interrupt InterruptHandler nosave=section(".tmpdata"),section("MATH_DATA")
void InterruptHandler( void )
{
  BYTE bTmp;
  if ( INTCONbits.INT0IF ) {
    // devo rever se é isso mesmo....
    // realiza a leitura do modem
    bTmp = getcUART( );

    ProcessaProtocolo( bTmp );

    INTCONbits.INT0IF = 0;
  }
  
  if ( PIR1bits.TMR2IF )
	{
		IncTickCount( );
		PIR1bits.TMR2IF = 0;
	}

	while ( PIR1bits.RCIF ) {
  	
  	if ( RCSTAbits.FERR ) {
    	//RCSTAbits.FERR = 0;
    	SerialGetchar();
    	break;
    }

    if ( RCSTAbits.OERR ) {
    	//RCSTAbits.OERR = 0;
    	RCSTAbits.CREN ^= 1;
    	Nop();
      RCSTAbits.CREN ^= 1;    	
    	break;
    }
    
  	if ( isrSerialFunc ){
      bTmp = SerialGetchar();
      (*isrSerialFunc)( bTmp ); 
    }  	
  }
}

//--------------------------------------------------------
#pragma interrupt InterruptHandlerLow
void InterruptHandlerLow( void )
{
  if ( PIR1bits.TXIF == 1 )
  {
    if ( isrSerialFuncTX )
    {
      (*isrSerialFuncTX)( 0 );
    }
  }
  return;
}
//--------------------------------------------------------

BYTE RemapISR( BYTE type, ISR_HANDLER_PTR isrFunc )
{
  DWORD dwTmp;
  BYTE bRet;
  BYTE bBuffer[4];

  dwTmp = (DWORD)isrFunc;
  dwTmp >>= 1;
  bBuffer[0] = LOBYTE(dwTmp);
  bBuffer[1] = 0xEF;    // GOTO
  bBuffer[2] = HIBYTE( LOWORD( dwTmp ));
  bBuffer[3] = 0xF0 | LONIBBLE( LOBYTE( HIWORD( dwTmp )));

  dwTmp = (type == LOW_ISR) ? SECOND_LOW_ISR_VECTOR : SECOND_HIGH_ISR_VECTOR;

  bRet = memprg_write( bBuffer, dwTmp, sizeof( bBuffer ));
  if ( bRet != sizeof( bBuffer ) )
  {
    return -1;
  }
  return 0;
}

BYTE RemapInterruptHandler( void )
{
  BYTE bRet;
  
  bRet = RemapISR( LOW_ISR, InterruptHandlerLow );
  if ( bRet )
  {
    // oh oh
    while(1); 
  }
  
  bRet = RemapISR( HIGH_ISR, InterruptHandler );
  if ( bRet )
  {
    // oh oh
    while(1); 
  }
  
  return 0;
}
