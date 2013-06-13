/** 
 *  cpu
 *  Module for control some status of CPU operation
 *  Author : Rafael Dias Menezes
 *  Date   : 11/09
 */

#ifndef __CPU__
#define __CPU__

#include "defs.h"

/**
 *  \brief Disable all interrupts
 */
void CPU_DisableAllInt( void );

/**
 *  \brief Enable glogal interrupts
 */
void CPU_EnableAllInt( void );

/**
 *  \brief Reinicia o Watch Dog Timer
 */
void CPU_RstWDT( void );

/**
 *  \brief Restart the entire CPU
 */
void CPU_Reset( void );

#endif
