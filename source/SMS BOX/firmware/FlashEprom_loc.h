#ifndef __FLASHEPROM_LOC__
#define __FLASHEPROM_LOC__

#include "log.h"
#include "FlashEprom.h"

#define FEE_CONFIG_STR        0x00000000                                  //! position flash integrity settings 
#define FEE_CONFIG_STR_LEN    11L
#define FEE_FAC_SETTINGS      (FEE_CONFIG_STR + FEE_CONFIG_STR_LEN)       //! position of factory config settings 
#define FEE_FAC_SETTINGS_LEN  32L
#define FEE_LOG_ADDR          (FEE_FAC_SETTINGS + FEE_FAC_SETTINGS_LEN)
#define FEE_NLOG_EVNT         N_LOG_EVNT
#define FEE_TESTE_ADDR        (FEE_LOG_ADDR + FEE_NLOG_EVNT * sizeof( struct LogBuffer ))
#define FEE_TESTE_ADDR_LEN    sizeof( DWORD )
#define FEE_BOOTLOADER        (FEE_TESTE_ADDR + sizeof( DWORD ))
#define FEE_BOOTLOADER_LEN    BOOT_LOADER_LEN
// FEE_MEM_IN_USE calcules the total ammount of memory that the system can use
#define FEE_MEM_IN_USE        ( (FEE_TESTE_ADDR + FEE_TESTE_ADDR_LEN) - ( FEE_CONFIG_STR ) )

#endif //~__FLASHEPROM_LOC__
