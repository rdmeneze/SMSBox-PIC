#ifndef __BOOTLOADER__
#define __BOOTLOADER__

#include "defs.h"
#include "bootstatus.h"

#define BOOT_LOADER_OK            0
#define BOOT_LOADER_E2PROM_ERR    1
#define BOOT_LOADER_FLASH_ERR     2
#define BOOT_LOADER_FLASH_FRAME_TOO_LONG  3

/**
 *  \brief  Verify if the bootloader system is ready to work
 *  \return ready state
 */
BYTE CheckBootLoader( void );

/**
 *  \brief  Enable the engine to change the firmware
 *  \return the OK or fail state
 */
BYTE StartChangeFirmware( void );

/** 
 *  \brief Do the flush of the data received by the serial port
 *  \param buffer received buffer
 *  \param len  length of buffer to write
 *  \return status of operation
 */
BYTE  UpLoad2Flash( BYTE * buffer, BYTE len );

/**
 *  \brief  Get the CRC32 calculated from the last downloaded firmware
 *  \return last CRC32 calculated
 */
DWORD GetCalcCRC32( void );

/**
 *  \brief  Reset the CRC32 calculated value
 *  \return SUCCESS or FAIL state
 */
BYTE ResetCRC32( void );


#endif //~ __BOOTLOADER__
