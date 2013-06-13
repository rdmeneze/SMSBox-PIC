#include "version.h"
//#include <string.h>
#include "funcoes.h"
#include "prgmem_access.h"

//----------------------------------------------------------------------------------------------------------

#pragma romdata VERSION=0x005000
  const rom DWORD BoardVersion        = BOARD_VERSION;
  #if defined( __BOOTLOADER)
    const rom DWORD FirmwareVersion     = (-1);
  #else
    const rom DWORD FirmwareVersion     = FW_VERSION;
  #endif
  const rom DWORD BootLoaderVersion   = BOOT_LOADER_VERSION;
#pragma romdata

//----------------------------------------------------------------------------------------------------------

DWORD dwBoardVersion;
DWORD dwFirmwareVersion;
DWORD dwBootLoaderVersion;

//----------------------------------------------------------------------------------------------------------

BYTE bIniV = 0x00;

//----------------------------------------------------------------------------------------------------------

DWORD* GetBoardVersion( void )
{
  if ( BIT_IS_NOT_SET(bIniV, 0) )
  {
    memprg_read( (void*)&dwBoardVersion, (DWORD)&BoardVersion, sizeof( BoardVersion ));
    BIT_SET( bIniV, 0 );
  }
  return &dwBoardVersion;
}

//----------------------------------------------------------------------------------------------------------

DWORD* GetFirmwareVersion( void )
{
  if ( BIT_IS_NOT_SET(bIniV, 1) )
  {
    memprg_read( (void*)&dwFirmwareVersion, (DWORD)&FirmwareVersion, sizeof( FirmwareVersion ));
    BIT_SET( bIniV, 1 );
  }
  return &dwFirmwareVersion;
}

//----------------------------------------------------------------------------------------------------------

DWORD* GetBootLoaderVersion( void )
{
  if ( BIT_IS_NOT_SET(bIniV, 2) )
  {
    memprg_read( (void*)&dwBootLoaderVersion, (DWORD)&BootLoaderVersion, sizeof( BootLoaderVersion ));
    BIT_SET( bIniV, 2 );
  }
  return &dwBootLoaderVersion;
}

//----------------------------------------------------------------------------------------------------------

