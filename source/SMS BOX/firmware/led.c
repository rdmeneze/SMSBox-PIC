#include "led.h"
#include "ports.h"
#include "status.h"
#include "timer.h"

//---------------------------------------------------------
#define TOTALTIME       3000
#define TIME_COM_PC    (TOTALTIME/4)
#define TIME_IDLE      (TOTALTIME/2)
#define PULSE_TIME      150
#define PULSE_COM_PC    1
#define PULSE_MODEM_RDY 2
#define PULSE_RST_BOR   3
#define PULSE_RST_WDT   4
#define PULSE_RST_LVD   5 

BYTE pulseLED[] = { //! Quantidade de pulsos que deve dar o led para indicação dos diversos estados de operação do SMS Box
    PULSE_COM_PC    << 1  ,  
    PULSE_MODEM_RDY << 1  ,  
    PULSE_RST_BOR   << 1  ,  
    PULSE_RST_WDT   << 1  ,  
    PULSE_RST_LVD   << 1  
};  

BYTE statesLED[] = {  //! Possíveis estados de indicação do SMS Box
    ST_COM_PC_OK  ,       
    ST_MODEM_RDY  ,       
    ST_RST_BOR    ,       
    ST_RST_WDT    ,       
    ST_RST_LVD          
};  

//---------------------------------------------------------

BYTE  ledTimer;  //! timer de controle de piscadas do LED
BYTE  ledState = 0;
BYTE  ledCountPulse = 0;
BYTE  bLedInit = FALSE;

//---------------------------------------------------------

void LedInit( void ){

  if ( bLedInit == TRUE ){
    return;
  }

  LED_DIR = 0;
  LED = 0;
  
  ledTimer = GetTimer( 0 );
  ledState = 0;
  bLedInit = TRUE;

  return;
}

//---------------------------------------------------------
  
void LedSetState( BYTE bState ){
  LED = bState & 0x01;
}

//---------------------------------------------------------

void CheckLed( void ){
#ifndef __BOOTLOADER
  WORD wStatus;
  WORD wTime;

  if ( bLedInit == FALSE ){
    LedInit();
  }

  if ( IsTimerTimeOut( ledTimer ) ) {
    wStatus = GetStatus( );

    if ( wStatus ){
      RestartTimer( ledTimer, PULSE_TIME );
    }
    else{
      RestartTimer( ledTimer, TOTALTIME / 2 );
    }


    if ( (ledState % 2) == 0 ){
      if ( wStatus & statesLED[ ledState >> 1 ] ){
        ledCountPulse = pulseLED[ ledState >> 1 ];
        ledState++;
      }        
      else{
        ledState+= 2;
      }
    }
    else{
      if ( wStatus & statesLED[ ledState >> 1 ] ){
        LED = !LED;
        ledCountPulse--;
        if ( !ledCountPulse ){
          ledState++;
          RestartTimer( ledTimer , TOTALTIME - pulseLED[ ledState >> 1 ] * PULSE_TIME );
        }
      }     
    }

    if ( ledState > (NSTATE << 1) ){
      ledState = 0;
    }  
  }
#endif
}

//---------------------------------------------------------
