/** 
 *  cpu
 *  Module for control some status of CPU operation
 *  Author : Rafael Dias Menezes
 *  Date   : 11/09
 */

#include "cpu.h"
#include "processor.h"

//---------------------------------------------------------------------

void CPU_RstWDT( void ){
#ifndef __DEBUG  
  _asm
    CLRWDT
  _endasm
#endif
  return;
}

//---------------------------------------------------------------------

void CPU_Reset( void ){
  _asm
    RESET
  _endasm
  return;
}

//---------------------------------------------------------------------
