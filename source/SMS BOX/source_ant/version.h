#ifndef __VERSION__
#define __VERSION__

#include "defs.h"

//#define BOARD_VERSION  0x01000000     //  0x<XX>.<XX>.<XX>.<XX>
//#define BOARD_VERSION  0x01010000       //  0x<XX>.<XX>.<XX>.<XX>
#define BOARD_VERSION  0x01020000     //  0x<XX>.<XX>.<XX>.<XX>

//#define FW_VERSION          0x01000100  //  0x<XX>.<XX>.<XX>.<XX>
//#define FW_VERSION          0x01000300  //  0x<XX>.<XX>.<XX>.<XX>
//#define FW_VERSION          0x01000400  //  0x<XX>.<XX>.<XX>.<XX>
#define FW_VERSION          0x01000500  //  0x<XX>.<XX>.<XX>.<XX>

#define BOOT_LOADER_VERSION 0x00000100    

/**
 *  \brief  Get the board version
 *  \return a pointer to board version information
 */
DWORD* GetBoardVersion( void );

/**
 *  \brief  Get the firmware version
 *  \return a pointer to firmware version information
 */
DWORD* GetFirmwareVersion( void );


/**
 *  \brief  Get the bootloader version
 *  \return a pointer to bootloader version number
 */
DWORD* GetBootLoaderVersion( void );


#endif
