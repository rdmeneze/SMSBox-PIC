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

static BYTE bStartCondition;

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
  if ( bStartCondition != 0xAA )
  {
    // add by rdias
    RemapInterruptHandler();
    LogInit();
    SerialPCInit( );
    GetID();
    // add by rdias
  }
  
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