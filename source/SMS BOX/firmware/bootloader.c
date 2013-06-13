#include "bootloader.h"
#include "crc32.h"
#include "FlashEprom.h"
#include "FlashEprom_loc.h"
#include "e2prom_loc.h"
#include "e2prom.h"
#include "cpu.h"
#include "bootstatus.h"

//----------------------------------------------------
DWORD dwCRC32;                          //! calculated CRC32
//----------------------------------------------------

BYTE CheckBootLoader( void ){
  BYTE bStatus;

  e2prom_read( (BYTE*)&bStatus, BOOT_LDR_ST_ADDR, sizeof( BYTE ));

  if ( bStatus & BOOT_LOADER_CHANGE_FW ){
    return TRUE;
  }

  return FALSE;
}

//----------------------------------------------------

BYTE  UpLoad2Flash( BYTE * buffer, BYTE len )
{
  DWORD dwActualBootLoaderUpLoadAddr;     //! last uploaded address into the firmware

  //! calcula o CRC32 do buffer recebido 
  if ( e2prom_read( (BYTE*)&dwCRC32, BOOT_LDR_CRC32_ADDR, sizeof( DWORD )) == FALSE )
  {
    return BOOT_LOADER_E2PROM_ERR;
  }

  dwCRC32 = crc32c( dwCRC32, buffer, len );
  
  if ( e2prom_write( (BYTE*)&dwCRC32, BOOT_LDR_CRC32_ADDR, sizeof( DWORD )) == FALSE )
  {
    return BOOT_LOADER_E2PROM_ERR;
  } 

  CPU_RstWDT();

  if ( e2prom_read( (BYTE*)&dwActualBootLoaderUpLoadAddr, BOOT_LDR_PCK_CNTRL_ADDR, sizeof( DWORD )) == FALSE )
  {
    return BOOT_LOADER_E2PROM_ERR;
  }

  // salva o buffer recebido na Flash EEPROM
  if ( Flash_Write( buffer, FEE_BOOTLOADER + dwActualBootLoaderUpLoadAddr, len ) != len )
  {
    return BOOT_LOADER_FLASH_ERR;
  }

  dwActualBootLoaderUpLoadAddr += len;

  if ( e2prom_write( (BYTE*)&dwActualBootLoaderUpLoadAddr, BOOT_LDR_PCK_CNTRL_ADDR, sizeof( DWORD )) == FALSE )
  {
    return BOOT_LOADER_E2PROM_ERR;
  }

  return ERROR_SUCCESS;
}

//----------------------------------------------------

DWORD GetCalcCRC32( void ){
  return dwCRC32;
}

//----------------------------------------------------

BYTE ResetCRC32( void ){
  dwCRC32 = 0;

  return e2prom_write( (BYTE*)&dwCRC32, BOOT_LDR_CRC32_ADDR, sizeof( DWORD ));
}

//----------------------------------------------------

BYTE StartChangeFirmware( void ){
  BYTE bStatus;

  if ( e2prom_read( (BYTE*)&bStatus, BOOT_LDR_ST_ADDR, sizeof( BYTE )) == FALSE ){
    return FALSE;
  }

  bStatus |= BOOT_LOADER_CHANGE_FW;

  if ( e2prom_write( (BYTE*)&bStatus, BOOT_LDR_ST_ADDR, sizeof( BYTE )) == FALSE ){
    return FALSE;
  }

  CPU_Reset();
 
  return TRUE;
}

//----------------------------------------------------
