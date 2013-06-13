/*********************************************************************************************
 *  Projeto de sistema de bootloader da SMS Box. 
 *
 *  Autor : Rafael Dias Menezes
 *  Data  : Mar�o/2010
 *
 *  Deve ser dada aten��o �s palavras de configura��o para opera��o 
 *  do sistema. Vide help do MPLAB.
 * 
 *  Release Notes:
 *    + log functions
 *    + serialPC optimized for bootloader operation
 *    + boot loader functions 
 *
 *********************************************************************************************/
#include "defs.h"
#include "processor.h"
#include "flasheprom.h"
#include "timer.h"
#include "cpu.h"
#include "log.h"
#include "flasheprom_loc.h"
#include <stdio.h>
#include <string.h>  
#include <reset.h>  
#include "changefirmware.h"
#include "vectors.h"
#include "interrupt.h"
#include "serialpc.h"
#include "simcardcontrol.h"
#include "funcoes.h"

//----------------- configuration words   -----------------
#pragma config OSC      = HS
//#pragma config OSC      = INTIO7
#pragma config PWRT     = OFF
#pragma config BOREN    = OFF
#pragma config BORV     = 0
#pragma config MCLRE    = ON
#pragma config PBADEN   = OFF
#pragma config LVP      = OFF  

#ifdef __DEBUG
  #pragma config WDT      = OFF
#else
  #pragma config WDT      = ON
#endif

//----------------------------------------------------------------------

static BYTE bStartCondition;

//----------------------------------------------------------------------
void ChangeLeds( void );
//----------------------------------------------------------------------

#if ((defined ( _USE_BOOT_LOADER) ) || (defined (__DEBUG)))
  #pragma code NULL_START=RM_USER_PROGRAM
  void startNULL(void)
  {
    CPU_Reset();
  }
  #pragma code
#endif

//----------------------------------------------------------------------

void __init() 
{
  return;
}

//----------------------------------------------------------------------

void main( void )
{
  
  BYTE a[] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0};
  DWORD crc = 0;
  int u = 60;  

  crc = crc32c( &crc, a, 60L );


  if ( bStartCondition != 0xAA )
  {
    // add by rdias
    RemapInterruptHandler();
    // add by rdias
  }

  //LogInit();
  FlashInit( );
  SerialPCInit( );
  GetID();
  
  for (;;)
  {
    if ( VerifyStartUserProgram() == FALSE )
    {
      // inicia o programa do usu�rio. 
      // tem que haver uma imagem j� gravada na �rea de usu�rio da mem�ria. Isso pressup�e que o 
      // firmware deve ter sido carregado na flash.
      if ( bStartCondition != 0xAA )
      {
        bStartCondition = 0xAA;   // no reset esta vari�vel n�o perder� o valor. 
                                  // N�o tendo firmware de usu�rio, estar� presente na 
                                  //  posi��o RM_USER_PROGRAM da mem�ria uma instru��o de reset
        GotoUserProgram();
      }
      else
      {
        while( 1 )
        {
          // n�o h� firmware novo na mem�ria flash. Bootloader deve operar no modo de espera de firmware
          ProcessaPacotes( );
          ChangeLeds( );
          CPU_RstWDT( );  
        }
      }
    }
    else
    {
      //  Inicia o processo de c�pia do firmware presente na SDRAM 
      //    para a Flash E2PROM
      ChangeFirmware();
    } 
  }

}

//----------------------------------------------------------------------

void ChangeLeds( void )
{
  static BYTE bTimer = TIMER_NULL;
  static BYTE sStatus = 0;
  static BYTE bLeds = 1;

  if ( bTimer == TIMER_NULL )
  {
    bTimer = GetTimer( 500 ); 
    InitSimCards( );
    return;
  }

  if ( IsTimerTimeOut( bTimer ) == TRUE )
  {
    RestartTimer( bTimer, 500 );
    SetSimCard( bLeds );
    bLeds <<= 1;
    if ( BIT_IS_SET( bLeds, 4 ) )
    {
      bLeds = 1;
    } 
  }
  
  return;
}

//----------------------------------------------------------------------
