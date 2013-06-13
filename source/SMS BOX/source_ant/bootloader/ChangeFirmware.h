/********************************************************************
 *
 *  Module : Change firmware
 *  Swap the firmware present in the Flash EPROM by the firmware present in SDRAM
 *  Author : Rafael Dias (rdmeneze@yahoo.com.br)
 *  Date   : 03/2010 
 *
 ********************************************************************/


#ifndef __CHANGEFIRMWARE__
#define __CHANGEFIRMWARE__

#include "defs.h"

/**
 *  \brief Change the firmware present in the Flash EPROM by the firmware present in SDRAM
 */
BYTE ChangeFirmware( void );

/**
 *  \brief  verify if start the user program or copy the program resident in SDRAM
 */
BYTE VerifyStartUserProgram( void );

#endif
