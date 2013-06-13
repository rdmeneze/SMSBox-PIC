#ifndef __HW_SPI__
#define __HW_SPI__

#include "defs.h"

/**
 * \brief Open the hardware SPI communication
 */
void OpenHWSPI(void);

//! macro for definition of HWOpenSPI funcion
#define HWOpenSPI OpenSWSPI

/**
 *  \brief  Do a write in the software SPI
 *  \param output the data for write into the memory
 */
void WriteHWSPI( char output );

//! macro for definition of HWWriteSPI funcion
#define HWWriteSPI WriteHWSPI

/**
 *  \brief  Set the Chip Select (CS)
 */
void SetCSHWSPI(void);

//! macro for definition of HWSetCSSPI funcion
#define HWSetCSSPI SetCSHWSPI

/**
 *  \brief  Clear the Chip Select (CS)
 */
void ClearCSHWSPI(void);
#define HWClearCSSPI ClearCSHWSPI

/**************************************************************************
Macro       : putcSWSPI

Description : macro is identical to WriteSWSPI,#define to WriteSWSPI in sw_spi.h
 
Arguments   : None
 
Remarks     : None 
***************************************************************************/
#define putcHWSPI WriteHWSPI

/**************************************************************************
Macro       : SWputcSPI

Description : macro is identical to WriteSWSPI,#define to WriteSWSPI in sw_spi.h
 
Arguments   : None
 
Remarks     : None 
***************************************************************************/
#define HWputcSPI putcHWSPI

/**
 *  \brief  Read a byte from SPI channel
 *  \return the byte received
 */
BYTE ReadHWSPI( void );



#endif // ~__HW_SPI__
