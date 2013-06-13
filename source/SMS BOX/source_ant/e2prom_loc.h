#ifndef _E2PROM_LOC_
#define _E2PROM_LOC_

/**
 *  e2prom_loc.h
 *  Localizations of variables into internal e2prom 
 *  Author: Rafael Dias Menezes
 *  company: Taioba Corporation
 *  email: rdmeneze@yahoo.com.br
 *  Date: dez/2009
 *
 *  Copyright (C) 2009  Rafael Dias
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 
 * - Modificatios
 *  -- 23/12/2009 by rdias: Initial version
 */

#include "processor.h"

//#define BASE_ADR  0x0000
//#define LOG_PTR_STA_ADDR    BASE_ADR                                    
//#define LOG_PTR_END_ADDR    ( LOG_PTR_STA_ADDR        + sizeof( DWORD ))
//#define LOG_LEVEL_ADDR      ( LOG_PTR_END_ADDR        + sizeof( DWORD ))
//#define LOG_STAMP_ADDR      ( LOG_LEVEL_ADDR          + sizeof( BYTE ))
//#define BOOT_LDR_ST_ADDR    ( LOG_STAMP_ADDR          + sizeof( WORD  ))
//#define BOOT_LDR_PCK_CNTRL_ADDR  ( BOOT_LDR_ST_ADDR    + sizeof( BYTE  ))
//#define BOOT_LDR_CRC32_ADDR      ( BOOT_LDR_PCK_CNTRL_ADDR  + sizeof( DWORD ))
//#define DW_TESTE_ADDR       ( BOOT_LDR_CRC32_ADDR      + sizeof( DWORD ))
//#define SERIAL_NUMBER_ADDR  ( DW_TESTE_ADDR       + sizeof( DWORD ))
//#define MEM_IN_USE          ( LOG_STAMP_ADDR - BASE_ADR )

#define LOG_PTR_STA_ADDR          0 
#define LOG_PTR_END_ADDR          4
#define LOG_LEVEL_ADDR            8
#define LOG_STAMP_ADDR            9
#define BOOT_LDR_ST_ADDR          11
#define BOOT_LDR_PCK_CNTRL_ADDR   12
#define BOOT_LDR_CRC32_ADDR       16
#define DW_TESTE_ADDR             20
#define SERIAL_NUMBER_ADDR        24
#define NEXT_FREE_ADDR            28
#define MEM_IN_USE                NEXT_FREE_ADDR


#endif //~_E2PROM_LOC_
