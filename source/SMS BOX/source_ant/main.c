/*********************************************************************************************
 *  Arquivo principal. Projeto de teste para desenvolvimento de módulos de 
 *  controle de dispositivos em uma plataforma ACEPIC com processador PIC18 
 *  Compilador utilizado: PIC C18
 *  Autor : Rafael Dias Menezes
 *  Data  : Ago/2009
 *
 *  Deve ser dada atenção às palavras de configuração para operação 
 *  do sistema. Vide help do MPLAB.
 *
 *********************************************************************************************/

#include "defs.h"
#include "led.h"
#include "processor.h"
#include "delay.h"
#include "serialpc.h"
#include "status.h"
#include "modemGSM.h"
#include "flasheprom.h"
#include "timer.h"
#include "cpu.h"
#include "device.h"
#include "log.h"
#include "flasheprom_loc.h"
#include <stdio.h>
#include <string.h>  
#include <reset.h>  
#include "device.h"
#include "prgmem_access.h"
#include "crc32.h"
#include "interrupt.h"

#include "vectors.h"

#ifdef __DEBUG
  #include "timer0.h"
#endif

//----------------- configuration words   -----------------
#pragma config OSC      = HS
//#pragma config OSC      = INTIO7
#ifdef __DEBUG
  #pragma config PWRT     = OFF
#else
  #pragma config PWRT     = ON
#endif
#pragma config BOREN    = OFF
#pragma config BORV     = 0
#pragma config MCLRE    = ON
#pragma config PBADEN   = OFF
#pragma config LVP      = OFF

#pragma config BBSIZ    = 4096 

/*
// Table Read Protection Block
#pragma config EBTRB    = OFF   // Table Read Protection Boot Block
#pragma config EBTR0    = OFF   // Table Read Protection Block 0
#pragma config EBTR1    = OFF   // Table Read Protection Block 1
#pragma config EBTR2    = OFF   // Table Read Protection Block 2
#pragma config EBTR3    = OFF   // Table Read Protection Block 3

#pragma config WRTC     = OFF   // Configuration Register Write Protection
#pragma config WRTB     = OFF   // Write Protection Boot Block 
#pragma config WRT0     = OFF   // Write Protection Block 0
#pragma config WRT1     = OFF   // Write Protection Block 1
#pragma config WRT2     = OFF   // Write Protection Block 2
#pragma config WRT3     = OFF   // Write Protection Block 3

#pragma config CPB      = OFF
#pragma config CP0      = OFF
#pragma config CP1      = OFF
#pragma config CP2      = OFF
#pragma config CP3      = OFF
*/

#ifdef __DEBUG
  #pragma config WDT      = OFF
#else
  #pragma config WDT      = ON
#endif

//----------------------------------------------------------------------

//BYTE timerHandle = TIMER_NULL;
//void ChangeLeds( void );

//----------------------------------------------------------------------

void __init() {
  return;
}

//----------------------------------------------------------------------

void main( void ){

  // determina a causa do reset
  if ( isBOR() || isLVD() || isWDTTO() ){

    if ( isBOR() == 1 ){
      // reset foi devido a um Brown out reset
      SetStatus( ST_RST_BOR );
    }
  
    if ( isLVD() == 1 ){
      // reset foi devido a um Low Voltage Detect
      SetStatus( ST_RST_LVD );
    }

    if ( isWDTTO() == 1 ){
      // reset foi devido a um evento do Watch dog timer
      SetStatus( ST_RST_WDT );
    }

    LedSetState( 1 );

    for( ;; ){
      CheckLed( );  
      CPU_RstWDT( );  
    }   
  }

#ifdef __DEBUG
  InitTimer0( );
#endif

  Dev_Init( );
  LogInit( );
  LedInit( );
  SerialPCInit( );
  ModemGSM_Init( );
  GetID();

  //SetID( 0x01 );
  
  for (;;){
    ProcessaPacotes( );
    ModemGSM_CheckMSG( );
    CheckLed( );  
    //ChangeLeds( );

    //CheckGSM_ONOffState( );
    CheckDevice( );
    
    CPU_RstWDT( );  
  }
}

//----------------------------------------------------------------------
