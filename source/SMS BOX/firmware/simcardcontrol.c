#include "simcardcontrol.h"

//------------------------------------------------------------------------------------

BYTE bActiveSIMCard;                    //! SIM card que está ativo atualmente.

//------------------------------------------------------------------------------------

void InitSimCards( void )
{
  bActiveSIMCard = 0xFF;  
#if BOARD_VERSION == 0x01000000

  EN_SIM_CARD_00_DIR = DIR_OUT;  
  EN_SIM_CARD_01_DIR = DIR_OUT;  
  EN_SIM_CARD_02_DIR = DIR_OUT;  
  EN_SIM_CARD_03_DIR = DIR_OUT;  
  EN_SIM_CARD_04_DIR = DIR_OUT;  
  EN_SIM_CARD_05_DIR = DIR_OUT;  
  EN_SIM_CARD_06_DIR = DIR_OUT;  
  EN_SIM_CARD_07_DIR = DIR_OUT;  
  EN_SIM_CARD_08_DIR = DIR_OUT;  
  EN_SIM_CARD_09_DIR = DIR_OUT;  
  EN_SIM_CARD_10_DIR = DIR_OUT;  
  EN_SIM_CARD_11_DIR = DIR_OUT;  
  EN_SIM_CARD_12_DIR = DIR_OUT;  
  EN_SIM_CARD_13_DIR = DIR_OUT;  
  EN_SIM_CARD_14_DIR = DIR_OUT;  
  EN_SIM_CARD_15_DIR = DIR_OUT;  
  
#elif (( BOARD_VERSION == 0x01010000 ) | ( BOARD_VERSION == 0x01020000 ) | ( BOARD_VERSION == 0x02000000 ))

  SIM_SEL_00_DIR = DIR_OUT;
  SIM_SEL_01_DIR = DIR_OUT;
  SIM_SEL_02_DIR = DIR_OUT;
  SIM_SEL_03_DIR = DIR_OUT;
  SIM_SEL_EN_DIR = DIR_OUT;

  SIM_SEL_EN = 1;           // Inicialmente nenhum sim card está habilitado

#else
  #error "BOARD_VERSION indefined"
#endif
}

//------------------------------------------------------------------------------------

BYTE SetSimCard( BYTE ID )
{
  ResetSIMCARD();

  if ( ID < NCARD ){
    bActiveSIMCard = ID + CARD_OFFSET;
  }
  
#if BOARD_VERSION == 0x01000000
  switch( ID ){
    case 0:
      EN_SIM_CARD_00 = 0;
      return TRUE;

    case 1:
      EN_SIM_CARD_01 = 0;
      return TRUE;

    case 2:
      EN_SIM_CARD_02 = 0;
      return TRUE;

    case 3:
      EN_SIM_CARD_03 = 0;
      return TRUE;

    case 4:
      EN_SIM_CARD_04 = 0;
      return TRUE;

    case 5:
      EN_SIM_CARD_05 = 0;
      return TRUE;

    case 6:
      EN_SIM_CARD_06 = 0;
      return TRUE;

    case 7:
      EN_SIM_CARD_07 = 0;
      return TRUE;

    case 8:
      EN_SIM_CARD_08 = 0;
      return TRUE;

    case 9:
      EN_SIM_CARD_09 = 0;
      return TRUE;

    case 10:
      EN_SIM_CARD_10 = 0;
      return TRUE;

    case 11:
      EN_SIM_CARD_11 = 0;
      return TRUE;

    case 12:
      EN_SIM_CARD_12 = 0;
      return TRUE;

    case 13:
      EN_SIM_CARD_13 = 0;
      return TRUE;

    case 14:
      EN_SIM_CARD_14 = 0;
      return TRUE;

    case 15:
      EN_SIM_CARD_15 = 0;
      return TRUE;
  }
 
  return FALSE;
  
#elif (( BOARD_VERSION == 0x01010000 ) | ( BOARD_VERSION == 0x01020000 ) | ( BOARD_VERSION == 0x02000000 ))
//  SIM_SEL_EN = 1;
  
  if ( bActiveSIMCard  != -1 ){
    SIM_SEL &= ~SIM_SEL_MASK;
    SIM_SEL |= (bActiveSIMCard & SIM_SEL_MASK);
    SIM_SEL_EN = 0;
    return TRUE;
  }
  return FALSE;
#else
  #error "BOARD_VERSION indefined"
#endif   
}

//------------------------------------------------------------------------------------

void ResetSIMCARD( void )
{
#if BOARD_VERSION == 0x01000000
  EN_SIM_CARD_00     = 1;
  EN_SIM_CARD_01     = 1;
  EN_SIM_CARD_02     = 1;
  EN_SIM_CARD_03     = 1;
  EN_SIM_CARD_04     = 1;
  EN_SIM_CARD_05     = 1;
  EN_SIM_CARD_06     = 1;
  EN_SIM_CARD_07     = 1;
  EN_SIM_CARD_08     = 1;
  EN_SIM_CARD_09     = 1;
  EN_SIM_CARD_10     = 1;
  EN_SIM_CARD_11     = 1;
  EN_SIM_CARD_12     = 1;
  EN_SIM_CARD_13     = 1;
  EN_SIM_CARD_14     = 1;
  EN_SIM_CARD_15     = 1;
  
#elif (( BOARD_VERSION == 0x01010000 ) | ( BOARD_VERSION == 0x01020000 ) | ( BOARD_VERSION == 0x02000000 ) )
  SIM_SEL_EN = 1;
  bActiveSIMCard = 0xFF;
  SIM_SEL &= ~SIM_SEL_MASK;
  SIM_SEL |= (0 & SIM_SEL_MASK);
#else
  #error "BOARD_VERSION indefined"
#endif  
}

//------------------------------------------------------------------------------------
