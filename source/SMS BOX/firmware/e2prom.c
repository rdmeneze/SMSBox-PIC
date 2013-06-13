#include "e2prom.h"
#include "funcoes.h"

//--------------------------------------------------


BYTE e2prom_read( BYTE * dest, WORD addr, size_t size ){
  //  verify in the datasheet for this sequence
  //  7.0 DATA EEPROM MEMORY

  BYTE i;
  
#if ( EEDATA_SIZE > 0 ) 

  if ( (addr + size - 1) > EEDATA_SIZE ){
    return FALSE;
  }

  for ( i = 0; i < size; i++, dest++, addr++ ){
  
    addr &= (EEDATA_SIZE - 1);

    EEADR   = LOBYTE( addr );
    EEADRH  = HIBYTE( addr );

    EECON1bits.EEPGD  = 0;
    EECON1bits.CFGS   = 0;
    EECON1bits.RD     = 1;
 
    *dest = EEDATA;
  }

  EECON1bits.EEPGD  = 1;
  EECON1bits.CFGS   = 1;
  EECON1bits.RD     = 0;

  return TRUE;
#else
  return FALSE;
#endif 
}

//--------------------------------------------------

BYTE e2prom_write( BYTE * src, WORD addr, size_t size ){
  //  verify in the datasheet for this sequence
  //  7.0 DATA EEPROM MEMORY
 
  BYTE i;
  BYTE bTmp;
  
#if ( EEDATA_SIZE > 0 )   

  if ( (addr + size - 1) > EEDATA_SIZE ){
    return FALSE;
  }

  for ( i = 0; i < size; i++, src++, addr++ ){

    addr &= (EEDATA_SIZE - 1);

    EEADR   = LOBYTE( addr );
    EEADRH  = HIBYTE( addr );
    EEDATA = *src;

    EECON1bits.EEPGD  = 0;
    EECON1bits.CFGS   = 0;
    EECON1bits.WREN   = 1;

    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;

    while( PIR2bits.EEIF == 0 );    // espera acabar o processo de escrita
    PIR2bits.EEIF = 0;
    
    e2prom_read( &bTmp, addr, sizeof( BYTE ));  // realiza a leitura do dado escrito para 
                                                // saber se escreveu realmente certo. 
    if ( bTmp != *src ){
      return FALSE;
    }
  }

  EECON1bits.EEPGD  = 1;
  EECON1bits.CFGS   = 1;
  EECON1bits.WREN   = 0;

  return TRUE;
  
#else
  return FALSE;
#endif
}

//--------------------------------------------------

