#ifndef __SIMCARDCTRL__
#define __SIMCARDCTRL__

#include "ports.h"
#include "defs.h"


//[rdias<]
//! look for the board version and set-up the SIM card quantity
#if ( ( BOARD_VERSION == 0x01000000 ) | \
      ( BOARD_VERSION == 0x01010000 ) | \
      ( BOARD_VERSION == 0x01020000 ) | \
      ( BOARD_VERSION == 0x02000000 ) ) 
  #define NCARD       16
  #define CARD_OFFSET 0
#else
  #error "BOARD_VERSION indefined"
#endif   

/**
 *  InitSimCards
 *  \brief Initialize the sim cards GPIOs and set the initial status of IOs and control variables
 */
void InitSimCards( void );

/** 
 *  SetSimCard
 *  \brief Put a SIM Card in operation
 */
BYTE SetSimCard( BYTE ID );

/** 
 *  ResetSIMCARD
 *  \brief Put the SIM Cards in IDDLE operation
 */
void ResetSIMCARD( void );

#endif //~ __SIMCARDCTRL__
