/**
 *    Module for treatment of interrupt routine services
 *    Autor   : Rafael Dias (rdmeneze@yahoo.com.br)
 *    Date    : Ago/2009
 */

#ifndef __INTERUPT__
#define __INTERUPT__

#include "defs.h"

#define LOW_ISR   1
#define HIGH_ISR  0

typedef void ISR_HANDLER_PTR(void);

BYTE RemapInterruptHandler( void );

BYTE RemapISR( BYTE type, ISR_HANDLER_PTR* isrFunc );

#endif
