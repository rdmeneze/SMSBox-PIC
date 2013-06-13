/**
 * AT45DBxx
 *  Performs the control of communication between the controller and the serial flash memory
 *  Author: Rafael Dias Menezes
 *  company: Taioba Corporation
 *  email: rdmeneze@yahoo.com.br
 *  Date: sep/2009
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
 *  -- 09/2009 by rdias: Initial version
 */

#include "AT45DBxx.h"
#include <string.h>
#include "sw_spi.h"
//------------------------------------------------------------------------------------

#define MAX_TENT  16

//------------------------------------------------------------------------------------
#if ( AT_45_PAGE_SIZE == 256L )
#elif ( AT_45_PAGE_SIZE == 264L )
#else
  #error "AT_45_PAGE_SIZE length error"
#endif
//------------------------------------------------------------------------------------

//-- Flash operation commands
//-- Read commands
#define FLASH_CMD_MAIN_MEM_PAGE_RD                          0xd2 
#define FLASH_CMD_MAIN_MEM_PAGE_RD_DMY_BYTE                 4
#define FLASH_CMD_LEGACY_CONTINUOUS_ARRAY_RD                0xe8 
#define FLASH_CMD_LEGACY_CONTINUOUS_ARRAY_RD_DMY_BYTE       4
#define FLASH_CMD_LOW_FREQ_CONTINUOUS_ARRAY_RD              0x03 
#define FLASH_CMD_LOW_FREQ_CONTINUOUS_ARRAY_RD_DMY_BYTE     0
#define FLASH_CMD_HIGH_FREQ_CONTINUOUS_ARRAY_RD             0x0b 
#define FLASH_CMD_HIGH_FREQ_CONTINUOUS_ARRAY_RD_DMY_BYTE    1
#define FLASH_CMD_LOW_FREQ_BUFFER1_RD                       0xd1 
#define FLASH_CMD_LOW_FREQ_BUFFER1_RD_DMY_BYTE              0
#define FLASH_CMD_LOW_FREQ_BUFFER2_RD                       0xd3 
#define FLASH_CMD_LOW_FREQ_BUFFER2_RD_DMY_BYTE              0
#define FLASH_CMD_BUFFER1_RD                                0xd4 
#define FLASH_CMD_BUFFER1_RD_DMY_BYTE                       1
#define FLASH_CMD_BUFFER2_RD                                0xd6 
#define FLASH_CMD_BUFFER2_RD_DMY_BYTE                       1

//-- Program and Erase Commands
#define FLASH_CMD_BUFFER1_WR                                0x84 
#define FLASH_CMD_BUFFER1_WR_DMY_BYTE                       0
#define FLASH_CMD_BUFFER2_WR                                0x87 
#define FLASH_CMD_BUFFER2_WR_DMY_BYTE                       0
#define FLASH_CMD_BUFFER1_2_MAINMEMORY_PAGE_ERASE           0x83 
#define FLASH_CMD_BUFFER1_2_MAINMEMORY_PAGE_ERASE_DMY_BYTE  0
#define FLASH_CMD_BUFFER2_2_MAINMEMORY_PAGE_ERASE           0x86}
#define FLASH_CMD_BUFFER2_2_MAINMEMORY_PAGE_ERASE_DMY_BYTE  0
#define FLASH_CMD_BUFFER1_2_MAINMEMORY_PAGE_NOERASE         0x88  
#define FLASH_CMD_BUFFER2_2_MAINMEMORY_PAGE_NOERASE_DMY_BYTE  0
#define FLASH_CMD_PAGE_ERASE                                0x81  
#define FLASH_CMD_PAGE_ERASE_DMY_BYTE                       0
#define FLASH_CMD_BLOCK_ERASE                               0x50  
#define FLASH_CMD_BLOCK_ERASE_DMY_BYTE                      0
#define FLASH_CMD_SECTOR_ERASE                              0x7C  
#define FLASH_CMD_SECTOR_ERASE_DMY_BYTE                     0
#define FLASH_CMD_CHIP_ERASE                                0xC7  
#define FLASH_CMD_CHIP_ERASE_DMY_BYTE                       0
#define FLASH_CMD_MMPage_2_BUFFER1                          0x82  
#define FLASH_CMD_MMPage_2_BUFFER1_DMY_BYTE                 0
#define FLASH_CMD_MMPage_2_BUFFER2                          0x85  
#define FLASH_CMD_MMPage_2_BUFFER2_DMY_BYTE                 0


//-- Protection and Security Commands
//const BYTE FLASH_CMD_EN_SECTOR_PROT[] =                       {0x3D, 0x2A, 0x7F, 0xA9};
//#define FLASH_CMD_EN_SECTOR_PROT_DMY_BYTE                     0
//const BYTE FLASH_CMD_DIS_SECTOR_PROT[] =                      {0x3D, 0x2A, 0x7F, 0x9A};
//#define FLASH_CMD_DIS_SECTOR_PROT_DMY_BYTE                    0
//const BYTE FLASH_CMD_ERASE_SECTOR_PROT_REG[] =                {0x3D, 0x2A, 0x7F, 0xCF};
//#define FLASH_CMD_ERASE_SECTOR_PROT_REG_DMY_BYTE              0
//const BYTE FLASH_CMD_PROGRAM_SECTOR_PROT_REG[] =              {0x3D, 0x2A, 0x7F, 0xFC};
//#define FLASH_CMD_PROGRAM_SECTOR_PROT_REG_DMY_BYTE            0
//const BYTE FLASH_CMD_READ_SECTOR_PROT_REG[] =                 {0x32};
//#define FLASH_CMD_READ_SECTOR_PROT_REG_DMY_BYTE               0
//const BYTE FLASH_CMD_SECTOR_LOCKDOWN[] =                      {0x3D, 0x2A, 0x7F, 0x30};
//#define FLASH_CMD_SECTOR_LOCKDOWN_DMY_BYTE                    0
//const BYTE FLASH_CMD_READ_SECTOR_LOCKDOWN_REG[] =             {0x35};
//#define FLASH_CMD_READ_SECTOR_LOCKDOWN_REG_DMY_BYTE           0
//const BYTE FLASH_CMD_PROGRAM_SEC_REG[] =                      {0x9B, 0x00, 0x00, 0x00};
//#define FLASH_CMD_PROGRAM_SEC_REG_DMY_BYTE                    0
//const BYTE FLASH_CMD_READ_SEC_REG[] =                         {0x77};
//#define FLASH_CMD_READ_SEC_REG_DMY_BYTE                       0

//-- Additional Commands
#define FLASH_CMD_MAIN_MEM_PAGE_2_BUFFER1_TRANSFER            0x53 
#define FLASH_CMD_MAIN_MEM_PAGE_2_BUFFER1_TRANSFER_DMY_BYTE   0
#define FLASH_CMD_MAIN_MEM_PAGE_2_BUFFER2_TRANSFER            0x55 
#define FLASH_CMD_MAIN_MEM_PAGE_2_BUFFER2_TRANSFER_DMY_BYTE   0
#define FLASH_CMD_MAIN_MEM_PAGE_2_BUFFER1_COMPARE             0x60 
#define FLASH_CMD_MAIN_MEM_PAGE_2_BUFFER1_COMPARE_DMY_BYTE    0
#define FLASH_CMD_MAIN_MEM_PAGE_2_BUFFER2_COMPARE             0x61 
#define FLASH_CMD_MAIN_MEM_PAGE_2_BUFFER2_COMPARE_DMY_BYTE    0
#define FLASH_CMD_AUTO_PAGE_REWRITE_BUFFER1                   0x58 
#define FLASH_CMD_AUTO_PAGE_REWRITE_BUFFER1_DMY_BYTE          0
#define FLASH_CMD_AUTO_PAGE_REWRITE_BUFFER2                   0x59 
#define FLASH_CMD_AUTO_PAGE_REWRITE_BUFFER2_DMY_BYTE          0
#define FLASH_CMD_DEEP_PWR_DOWN                               0xB9 
#define FLASH_CMD_DEEP_PWR_DOWN_DMY_BYTE                      0
#define FLASH_CMD_RESUME_DEEP_PWR_DOWN                        0xAB 
#define FLASH_CMD_RESUME_DEEP_PWR_DOWN_DMY_BYTE               0
#define FLASH_CMD_READ_STATUS_REG                             0xD7 
#define FLASH_CMD_READ_STATUS_REG_DMY_BYTE                    0
#define FLASH_CMD_READ_DEVICE_ID                              0x9F 
#define FLASH_CMD_READ_DEVICE_ID_DMY_BYTE                     0
//------------------------------------------------------------------------------------


//------   Auxiliary functions  ------
BYTE WaitBusy( void );
void WriteFlashAddr(DWORD addr);
void Write24BitAddr(DWORD addr);
void PageWriteMainMemo(WORD page,WORD p_addr,BYTE  num,BYTE *dat);
void WriteBuffer1(BYTE addr, BYTE num, BYTE *dat);
void WriteMainMemoToBuffer1(WORD page);
void WriteBuffer1ToMainMemo(WORD page);
//------------------------------------------------------------------------------------

void AT45DBXX_Init( void ){
  OpenSWSPI();
  return;
}

//------------------------------------------------------------------------------------

#if AT_45_PAGE_SIZE == 256L
  BYTE AT45DBXX_Read( BYTE * bufOut, DWORD addr, BYTE len ){
#elif AT_45_PAGE_SIZE == 264L
  BYTE AT45DBXX_Read( BYTE * bufOut, DWORD addr, WORD len ){
#endif

  WORD i;
  BYTE * pByte;

  if ( WaitBusy() == FALSE ){
    return -1;
  }

  if ( !len ){
    return 0;
  }

  ClearCSSWSPI();

  // comando de leitura diretamente da SDRAM
  WriteSWSPI( FLASH_CMD_MAIN_MEM_PAGE_RD );

  // endereços e páginas concatenados
  WriteFlashAddr( addr );

  // envia DUMMY_BYTES
  i = FLASH_CMD_MAIN_MEM_PAGE_RD_DMY_BYTE;
  do{
    WriteSWSPI( 0xFF );
  }while( --i );

   pByte = bufOut;
  do{
    *pByte++ = ReadSWSPI();
  }while( --len );

  SetCSSWSPI();
  return i;
}

//------------------------------------------------------------------------------------

#if AT_45_PAGE_SIZE == 256L
  BYTE AT45DBXX_Write( BYTE * bufIn, DWORD addr, BYTE len ){
#elif AT_45_PAGE_SIZE == 264L
  BYTE AT45DBXX_Write( BYTE * bufIn, DWORD addr, WORD len ){
#endif

	WORD page;
  WORD p_addr; 
	BYTE n; 

	if ((bufIn == NULL) || (len == 0)) { 
		return 0; 
	} 

	p_addr = addr % AT_45_PAGE_SIZE;						
	page = addr / AT_45_PAGE_SIZE;							

	if ((p_addr + len) > AT_45_PAGE_SIZE) {  
		n = AT_45_PAGE_SIZE - p_addr; 
		PageWriteMainMemo(page ,p_addr ,n ,bufIn ); 

		//len -= n; 
    
		PageWriteMainMemo( page+1, 0, len - n, bufIn + n ); 
	} 
	else { 
		PageWriteMainMemo(page,p_addr,len,bufIn); 
	}   

  return len;
}

//------------------------------------------------------------------------------------

BYTE WaitBusy( void ){
  BYTE data;
  BYTE i;

  ClearCSSWSPI();
  WriteSWSPI( FLASH_CMD_READ_STATUS_REG );

  i = 0;
  do { 
    data = ReadSWSPI( );
    i++;

    if ( i == MAX_TENT ) {
      SetCSSWSPI();  
      return FALSE;
    }

  }while(data < 0x80); 
  
  SetCSSWSPI();  

  return TRUE;
}

//------------------------------------------------------------------------------------

void WriteFlashAddr(DWORD addr){ 
	DWORD m; 
	WORD  k; 

	k = addr % AT_45_PAGE_SIZE;							
	m = addr / AT_45_PAGE_SIZE;							

#if ( AT_45_PAGE_SIZE == 264L )
	m = k + (m << 9);						
#elif ( AT_45_PAGE_SIZE == 256L )
#endif

	Write24BitAddr(m); 
} 

//------------------------------------------------------------------------------------

void Write24BitAddr(DWORD addr) { 
	BYTE dat[3]; 
  BYTE i; 

	for (i = 0; i < 3; i++) { 
		dat[i] = (BYTE)addr; 
		addr >>= 8; 
	} 
	for (i = 0; i < 3; i++) { 
    WriteSWSPI(dat[2-i]); 
	} 
}

//------------------------------------------------------------------------------------

void PageWriteMainMemo(WORD page,WORD p_addr,BYTE  num,BYTE *dat) { 
	if (( num == 0 ) || (dat == NULL))
    return; 

	if ((p_addr + num) > AT_45_PAGE_SIZE) {
    num = AT_45_PAGE_SIZE - p_addr; 
  }

  WaitBusy();
	ClearCSSWSPI(); 
	WriteMainMemoToBuffer1(page); 
	WaitBusy(); 
	WriteBuffer1(p_addr, num, dat); 
	WriteBuffer1ToMainMemo(page); 
	SetCSSWSPI(); 
} 

//------------------------------------------------------------------------------------

void WriteBuffer1(BYTE addr, BYTE num, BYTE *dat)  { 
	BYTE i; 

	ClearCSSWSPI(); 
	WriteSWSPI( FLASH_CMD_BUFFER1_WR );		 				
	Write24BitAddr(addr);	 					
	for (i = 0; i < num; i++) { 
		WriteSWSPI(*(dat+i)); 
	} 
	SetCSSWSPI(); 
} 

//------------------------------------------------------------------------------------

void WriteBuffer1ToMainMemo(WORD page) { 
	DWORD b_addr; 

	ClearCSSWSPI();		 
	WriteSWSPI( FLASH_CMD_BUFFER1_2_MAINMEMORY_PAGE_ERASE );
	b_addr = (DWORD)((page) << 9); 
	Write24BitAddr(b_addr); 
	SetCSSWSPI(); 
} 

//------------------------------------------------------------------------------------

void WriteMainMemoToBuffer1(WORD page) { 
	DWORD b_addr; 

	ClearCSSWSPI();		 
	WriteSWSPI( FLASH_CMD_MAIN_MEM_PAGE_2_BUFFER1_TRANSFER );		 					
	b_addr = (DWORD)((page) << 9); 
	Write24BitAddr(b_addr); 
	SetCSSWSPI(); 
} 

//------------------------------------------------------------------------------------
