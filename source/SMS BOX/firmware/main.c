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
#include "SerialPC.h"
#include "status.h"
#include "modemGSM.h"
#include "FlashEprom.h"
#include "timer.h"
#include "cpu.h"
#include "device.h"
#include "log.h"
#include "FlashEprom_loc.h"
#include <stdio.h>
#include <string.h>  
#include <reset.h>  
#include "device.h"
#include "prgmem_access.h"
#include "crc32.h"
#include "interrupt.h"

#include "vectors.h"

#ifdef __DEBUG
  #include "Timer0.h"
#endif

//----------------- configuration words   -----------------

#if defined(__18F4680)
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
  
  #ifdef __DEBUG
    #pragma config WDT      = OFF
  #else
    #pragma config WDT      = ON
  #endif

#elif defined(__18F27J13)
    #pragma config OSC      =   HSPLL
    #pragma config IESO     =   OFF
    #pragma config XINST    =   OFF
    //#pragma config PLLSEL   =   PLL96
    #pragma config STVREN   =   ON

    #if defined ( __DEBUG )
        #pragma config WDTEN = OFF
    #else
        #pragma config WDTEN = ON
    #endif
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
