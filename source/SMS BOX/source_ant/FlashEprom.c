#include "flasheprom.h"
#include "FlashEprom_loc.h"
#include "funcoes.h"
#include <string.h>

#ifdef AT45DBXX
  #include "AT45DBXX.h"
#endif

//--------------------------------------------

const char cTesteString[FEE_CONFIG_STR_LEN] = {"YHWH-Rapha"}; //Deus que cura
const char cFactorySettings[32] = {  
                                    0xAA, 0xFF, 0x55, 0xFF, 
                                    0xAA, 0xFF, 0x55, 0xFF, 
                                    0xAA, 0xFF, 0x55, 0xFF, 
                                    0xAA, 0xFF, 0x55, 0xFF, 
                                    0xAA, 0xFF, 0x55, 0xFF, 
                                    0xAA, 0xFF, 0x55, 0xFF, 
                                    0xAA, 0xFF, 0x55, 0xFF, 
                                    0xAA, 0xFF, 0x55, 0xFF
                                  };
//--------------------------------------------
BYTE bSem;    //  trial semaphore to protect the access for the flash memory
//--------------------------------------------

BYTE Flash_Test( void );
void ResumeFactorySet( void );
BYTE bInit_Flash = 0x00;

//--------------------------------------------

void FlashInit( void ){
  bSem = 0;
  bInit_Flash = 1;
#ifdef AT45DBXX
  AT45DBXX_Init( );
#endif

  if ( Flash_Test() == FALSE ){
   ResumeFactorySet( );
  } 
  
  return;
}

//--------------------------------------------

BYTE Flash_Read( BYTE * bufOut, DWORD addr, BYTE len ){
  BYTE bRet;

  if ( !bInit_Flash )
  {
    FlashInit();
  }

  while ( bSem );   // espera acabar o último ciclo de leitura ou de escrita
  bSem++;           //trava qualquer outro processo que queira escrever na flash

#ifdef AT45DBXX
  bRet = AT45DBXX_Read( bufOut, addr, len );
#endif
  
  bSem--;           // libera qualquer outro processo requisitante. Não estou criando um processo de semaforo completo.
  return bRet;
}

//--------------------------------------------

BYTE Flash_Write( BYTE * bufIn, DWORD addr, BYTE len ){
  BYTE bRet;

  if ( !bInit_Flash ) {
    FlashInit();
  }

  while ( bSem );   // espera acabar o último ciclo de leitura ou de escrita
  bSem++;           //trava qualquer outro processo que queira escrever na flash

#ifdef AT45DBXX
  // verificar um sistema para verificar integridade dos dados escritos. 
  bRet = AT45DBXX_Write( bufIn, addr, len );
#endif

  bSem--;           // libera qualquer outro processo requisitante. Não estou criando um processo de semaforo completo.
  return bRet;
}

//--------------------------------------------

BYTE Flash_Test( void ){
  char cBuffer[sizeof(cTesteString)];

  Flash_Read( (BYTE*)cBuffer, FEE_CONFIG_STR, sizeof( cBuffer ));

  return (strncmp( (char *)cBuffer, (char*)cTesteString, GET_VEC_NUM_MEMBERS( cTesteString )) == 0) ? TRUE : FALSE;
}

//--------------------------------------------

void ResumeFactorySet( void ) {
  Flash_Write( (BYTE*)cTesteString,       FEE_CONFIG_STR,     sizeof( cTesteString )    );
  Flash_Write( (BYTE*)cFactorySettings,   FEE_FAC_SETTINGS,   sizeof( cFactorySettings ));
  return;
}

//--------------------------------------------
