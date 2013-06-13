#ifndef __VERSION__
#define __VERSION__

#include "defs.h"

// 0xXX.XX.XX.XX  - board version:
//#define BOARD_VERSION  0x01000000
//#define BOARD_VERSION  0x01010000
//#define BOARD_VERSION  0x01020000
#define BOARD_VERSION  0x02000000     //  versão com alteração de processador para o PIC18F47J13 e melhorias de hardware


// firmware version on the same format of BOARD_VERSION parameter
//#define FW_VERSION          0x01000100  //  0x<XX>.<XX>.<XX>.<XX>
//#define FW_VERSION          0x01000300  //  0x<XX>.<XX>.<XX>.<XX>
//#define FW_VERSION          0x01000400  //  0x<XX>.<XX>.<XX>.<XX>
//#define FW_VERSION          0x01000500  //  0x<XX>.<XX>.<XX>.<XX>
#define FW_VERSION          0x02000000  

//! to be defined
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
