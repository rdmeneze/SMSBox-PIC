#include "e2prom_loc.h"
#include "log.h"

//! Note:
//! the order of EEPROM locations must follow the order in the file e2prom_loc.h

//#ifndef __BOOTLOADER_DBG


//[rdias<]
//  note for new processors:
//    when the processador internal E2PROM memory is zero, use the flash external memory
//[rdias>]
#pragma romdata eedata_scn=0xf00000
  rom DWORD LOG_PTR_STA           = 0x00000001;
  rom DWORD LOG_PTR_END           = 0x00000000;
  rom BYTE  LOG_LEVEL             = LOG_ALL;
  rom WORD  LOG_STAMP             = 0x0000;
  rom BYTE  BOOT_LDR_ST           = (0x00);
  rom DWORD BOOT_LDR_PCK_CNTRL    = 0x00000000;
  rom DWORD BOOT_LDR_CRC32        = 0x00000000;
  rom DWORD DWTESTE               = 0x12345678;
  rom DWORD SERIAL_NUMBER         = 0x78564312;
#pragma romdata
//#endif  


