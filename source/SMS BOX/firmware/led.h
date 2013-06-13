#ifndef __LED__
#define __LED__

#include "defs.h"

/**
 *   Inicializa o hardware de LED 
 */
void LedInit( void );

/**
 * Altera o estado do led para ligado/desligado
 */
void LedSetState( BYTE bState );

/**
 *  checa o estado do led
 */
void CheckLed( void );

#endif
