
#include "e2prom.h"
#include "e2prom_loc.h"
#include "bootstatus.h"
#include "changefirmware.h"
#include "funcoes.h"
#include "flasheprom.h"
#include "flasheprom_loc.h"
#include "prgmem_access.h"

//---------------------------------------------------------

BYTE VerifyStartUserProgram( void )
{
  BYTE bStatus;

  e2prom_read( (BYTE*)&bStatus, BOOT_LDR_ST_ADDR, sizeof( BYTE ));

  if ( BIT_IS_SET( bStatus, BOOT_LOADER_CHANGE_FW ) )
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

//---------------------------------------------------------

BYTE ChangeFirmware( void )
{
  DWORD dwCounter;
  DWORD dwFlashTotalUpload;
  BYTE  bBuffer[ BOOT_LOADER_FRAME_LEN + sizeof( DWORD ) ];
  WORD  wAddr;
  DWORD dwAddr;
  BYTE  bLen;
  BYTE  bMemType;
  
  e2prom_write( (BYTE*)&dwFlashTotalUpload, BOOT_LDR_PCK_CNTRL_ADDR, sizeof( dwFlashTotalUpload ));

  dwCounter = 0;
  do
  {
    wAddr = Flash_Read( (BYTE*)bBuffer, (DWORD)(FEE_BOOTLOADER + dwCounter), sizeof ( bBuffer )); 
  
    if ( wAddr == -1 )
    {
      return FALSE;
    }
    dwCounter += ((DWORD)wAddr);

    // parse the data in the memory.
    // buffer position  0    1     2    3     4         [4+len]
    // frame format : <adr2|adr1|adr0><len><data_0....data_n>
    bMemType = bBuffer[0];
    wAddr = MAKEWORD( bBuffer[2], bBuffer[1] );
    bLen  = bBuffer[3];

    if ( bLen >= BOOT_LOADER_FRAME_LEN )
    {
      return FALSE;
    }
    else
    {
      switch( bMemType )
      {
        case 0xF0:  // EEDATA
                    // não será atualizado a E2PROM
          e2prom_write( (BYTE*)&bBuffer[4], wAddr, bLen );
          break;

        case 0x20:  // User ID
        case 0x30:  // Configuration Words     
        default:
          if ( bMemType >= 0x00 && bMemType <= 0x1F )  // Program 
          { 
            dwAddr = MAKELONG( wAddr, MAKEWORD( 0, bMemType ));
            memprg_write( (BYTE*)&bBuffer[4], dwAddr, bLen ); 
            break;
          }
          else
          {
            return FALSE;
          }
      }
    }
  }while( dwCounter < dwFlashTotalUpload );
  
  bLen = 0;
  e2prom_write( (BYTE*)0, BOOT_LDR_PCK_CNTRL_ADDR , sizeof(  BYTE ));
  e2prom_write( (BYTE*)0, BOOT_LDR_CRC32_ADDR     , sizeof( DWORD ));

  return TRUE;
}

//---------------------------------------------------------

