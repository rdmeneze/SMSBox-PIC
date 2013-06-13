#include "processor.h"
#include "funcoes.h"
#include "cpu.h"

//#define PRGMEM_WRITE_BLOCK_SIZE 64L

//------------------------------------------------------------------------------

BYTE PageWrite( WORD page, BYTE pageOffSet, BYTE * buf, BYTE len );
void ErasePage( WORD page );

//------------------------------------------------------------------------------

BYTE  memprg_read( BYTE * buf, DWORD dwAddr, BYTE bLen )
{
  BYTE  i;  
  TBLPTR = dwAddr;

  for ( i = 0; i < bLen; i++ )
  {
    _asm TBLRDPOSTINC _endasm
    *buf++ = TABLAT;
  }
  
  return bLen; 
}

//------------------------------------------------------------------------------

BYTE  memprg_write( BYTE * buf, DWORD dwAddr, BYTE  bLen ) 
{
  BYTE i;
  WORD page;
  BYTE pageOffSet;
  BYTE n;

  page = dwAddr / PRGMEM_WRITE_BLOCK_SIZE;
  pageOffSet = dwAddr % PRGMEM_WRITE_BLOCK_SIZE;

  if (( pageOffSet + bLen ) > PRGMEM_WRITE_BLOCK_SIZE )
  {
    n = PRGMEM_WRITE_BLOCK_SIZE - pageOffSet;
    if ( PageWrite(page, pageOffSet, buf, n) == FALSE )
    {
      return 0;
    }  

    if ( PageWrite(page + 1, 0, buf + n, bLen - n) == FALSE )
    {
      return 0;
    }
  } 
  else
  {
    if ( PageWrite(page ,pageOffSet ,buf ,bLen ) == FALSE ) 
    {
      return 0;
    } 
  }

  return bLen;
}

//------------------------------------------------------------------------------

BYTE PageWrite( WORD page, BYTE pageOffSet, BYTE * buf, BYTE len )
{
  //
  //  Verify the datasheet for this sequence. 
  //  Chapter 6.0 FLASH PROGRAM MEMORY 
  //   by rdias
  //

  DWORD   dwAddr;
  BYTE    cBuffer[PRGMEM_WRITE_BLOCK_SIZE];
  BYTE *  pBYTE;
  BYTE *  pBuf;
  BYTE    i;  
  BYTE    bCounter;

  CPU_DisableAllInt( );

  //dwAddr = (page * PRGMEM_WRITE_BLOCK_SIZE) + pageOffSet;
  dwAddr = (page * PRGMEM_WRITE_BLOCK_SIZE);

  memprg_read( cBuffer, dwAddr, sizeof( cBuffer ));

  // write buff in the RAM
  pBYTE = cBuffer + pageOffSet;
  pBuf  = buf;
  for ( i = pageOffSet; i < (pageOffSet + len); i++ ) 
  {
    *pBYTE++ = *pBuf++;
  }

  //ErasePage( page );

  TBLPTR = dwAddr;
  //TBLPTRL &= ~(PRGMEM_WRITE_BLOCK_SIZE-1);

  EECON1bits.CFGS   = 0;    // access Flash program memory 
  if ( (TBLPTRU & 0xF0) == 0x30 )  
  {
    EECON1bits.CFGS   = 1;    // access Configuration program memory 
  }
  EECON1bits.EEPGD  = 1;    // point to Flash program memory
  EECON1bits.WREN   = 1;    // enable write to memory
  EECON1bits.FREE   = 1;    //  enable Row Erase operation    

  //CPU_DisableAllInt( );
  EECON2  = 0x55; 
  EECON2  = 0xAA; 
  EECON1bits.WR = 1;  // start erase (CPU stall)
  //CPU_EnableAllInt( );

  //_asm TBLRDPOSTDEC _endasm     // dummy read decrement
  Nop();

  
  // write the buffer into the memory pointed by pBYTE
  TBLPTR = dwAddr-1; // WTF. I got this tip from PIC18bootload code : http://www.microchipc.com/PIC18bootload/
  pBYTE = cBuffer;
  //for ( bCounter = 0; bCounter < 8; bCounter ++ )
  {
    //i = 8;
    //while ( i-- )
    //{
    //  TABLAT = *pBYTE++;
    //  _asm  TBLWTPREINC  _endasm
    //}
    for ( i = 0; i < sizeof( cBuffer ); i++ )
    {  
      TABLAT = *pBYTE++;
      _asm  TBLWTPREINC  _endasm
    }
  
    EECON1bits.CFGS   = 0;            // access Flash program memory 
    if ( (TBLPTRU & 0xF0) == 0x30 )
    {
      EECON1bits.CFGS   = 1;          // access Configuration program memory 
    }
    EECON1bits.EEPGD  = 1;            // point to Flash program memory
    EECON1bits.WREN   = 1;            //enable write to memory
   
    //CPU_DisableAllInt( );
    EECON2  = 0x55; 
    EECON2  = 0xAA; 
    EECON1bits.WR = 1;  // start program (CPU stall)
    //CPU_EnableAllInt( );
  
    EECON1bits.WREN = 0;            // disable write to memory
  }

  // compare the value copied  into the memory with the original buffer
  memprg_read( cBuffer, dwAddr + pageOffSet, len );

  pBYTE = cBuffer;
  pBuf  = buf;
  bCounter = TRUE;
  for ( i = 0; i < len; i++ )
  {
    if ( *pBYTE++ != *pBuf++ )
    {
      //return FALSE;  
      bCounter = FALSE;
      break;
    }
  }
  
  CPU_EnableAllInt( );
  //return TRUE; 

  return bCounter;
}

//------------------------------------------------------------------------------

void ErasePage( WORD page )
{
  DWORD dwAddr;
  dwAddr = page * PRGMEM_WRITE_BLOCK_SIZE; 

  TBLPTR = dwAddr;

  EECON1bits.EEPGD = 0;             //  point to Flash program memory
  if ( (TBLPTRU & 0xF0) == 0x30 )
  {
    EECON1bits.CFGS   = 1;          // access Configuration program memory 
  }

  EECON1bits.CFGS  = 0;       // access Flash program memory
  EECON1bits.WREN  = 1;       // enable write to memory
  EECON1bits.FREE  = 1;       // enable Row Erase operation

  //---  required sequence  ---//
  CPU_DisableAllInt( );       //disable interrupts
  EECON2 = 0x55;
  EECON2 = 0xAA;
  EECON1bits.WR   = 1;        // start erase (CPU stall)
  CPU_EnableAllInt( );        // enable interrupts
  //---  required sequence  ---//

  _asm TBLRDPOSTDEC _endasm
}
