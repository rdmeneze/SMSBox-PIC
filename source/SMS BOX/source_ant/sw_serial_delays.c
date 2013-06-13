#include "sw_serial_delays.h"
#include "processor.h"
#include "Delay4TCYx.h"
#include <delays.h>

//------------------------------------------------------------------------------------
//    Delay definitions
#define TX_BIT_UART     (((((FOSC/2) / (SWBAUD)) + 1) / 2) - 12)
#define HALF_BIT_UART   (((((FOSC/4) / (SWBAUD)) + 1) / 2) -  9) 
#define RX_BIT_UART     (((((FOSC/2) / (SWBAUD)) + 1) / 2) - 14)
//------------------------------------------------------------------------------------

void DelayTXBitUART( void ){
  //Delay4TCYx( (TX_BIT_UART / 4) - 3 );
  #if ( FOSC == 18432000 )
    #if ( SWBAUD == 19200 )
      // DelayTXBitUART == 228
      Delay10TCYx( 22 );  // 220 ciclos + 2 de chamada e + 2 de retorno
      Delay1TCY();        // 1 ciclo
      Delay1TCY();        // 1 ciclo
      Delay1TCY();        // 1 ciclo
      Delay1TCY();        // 1 ciclo
    #endif
  #else
  #endif
}

//------------------------------------------------------------------------------------

void DelayRXHalfBitUART( void ){
  Delay4TCYx( (HALF_BIT_UART / 4) - 3 );
}

//------------------------------------------------------------------------------------

void DelayRXBitUART( void ){
  Delay4TCYx( (RX_BIT_UART / 4) - 3 );
}

//------------------------------------------------------------------------------------
