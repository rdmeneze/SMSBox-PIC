#ifndef __SW_SPI_H
#define __SW_SPI_H
/******************************************************************************
 // *                   SW_SPI PERIPHERAL LIBRARY HEADER FILE
 ******************************************************************************
 * FileName:        		sw_spi.h
 * Dependencies:    	See include below
 * Processor:       		PIC18
 * Compiler:        		MCC18
 * Company:         		Microchip Technology, Inc.
 *
 * Software License Agreement
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *****************************************************************************/
 
#include <pconfig.h>
#include "defs.h"
#include "processor.h"
#include "version.h"

/* PIC18 Software SPI library header
 *
 * To use the software spi routines, the user must define
 * the port and tris register for each of the CS, DIN, DOUT,
 * and SCK pins.  The SPI mode must also be defined (MODE0,
 * MODE1, MODE2, MODE3).
 *
 * Define the port and pin for each of the software SPI pins
 *  - Chip select pin CS must have a port and tris definition.
 *  - Data in pin DIN must have a port and tris definition.
 *  - Data out pin DOUT must have a port and tris definition.
 *  - Clock pin SCK must have a port and tris definition.
 */

#if defined (SW_SPI_IO_V1)
  #define SW_CS_PIN         PORTCbits.RC3      // Chip Select
  #define TRIS_SW_CS_PIN    TRISCbits.TRISC3
  #define SW_DIN_PIN        PORTCbits.RC4     // Data in
  #define TRIS_SW_DIN_PIN   TRISCbits.TRISC4
  #define SW_DOUT_PIN       PORTCbits.RC6    // Data out
  #define TRIS_SW_DOUT_PIN  TRISCbits.TRISC6
  #define SW_SCK_PIN        PORTCbits.RC5     // Clock
  #define TRIS_SW_SCK_PIN   TRISCbits.TRISC5
#else
  #if ( BOARD_VERSION == 0x01020000 )
    #define SW_CS_PIN         PORTCbits.RC2      // Chip Select
    #define TRIS_SW_CS_PIN    TRISCbits.TRISC2
    #define SW_DIN_PIN        PORTCbits.RC4     // Data in
    #define TRIS_SW_DIN_PIN   TRISCbits.TRISC4
    #define SW_DOUT_PIN       PORTCbits.RC5    // Data out
    #define TRIS_SW_DOUT_PIN  TRISCbits.TRISC5
    #define SW_SCK_PIN        PORTCbits.RC3     // Clock
    #define TRIS_SW_SCK_PIN   TRISCbits.TRISC3
  #else
    #define SW_CS_PIN         PORTCbits.RC2      // Chip Select
    #define TRIS_SW_CS_PIN    TRISCbits.TRISC2
    #define SW_DIN_PIN        PORTCbits.RC5     // Data in
    #define TRIS_SW_DIN_PIN   TRISCbits.TRISC5
    #define SW_DOUT_PIN       PORTCbits.RC4    // Data out
    #define TRIS_SW_DOUT_PIN  TRISCbits.TRISC4
    #define SW_SCK_PIN        PORTCbits.RC3     // Clock
    #define TRIS_SW_SCK_PIN   TRISCbits.TRISC3
  #endif
#endif

// Define the mode for software SPI
// Refer to the SPI module for PIC17C756 for definitions of CKP and CKE
// Only one mode can be uncommented, otherwise the software will not work

#ifndef MODE0
#define MODE0  		// Setting for SPI bus Mode 0,0
#endif

//#define MODE1  		// Setting for SPI bus Mode 0,1
//#define MODE2  		// Setting for SPI bus Mode 1,0
//#define MODE3  		// Setting for SPI bus Mode 1,1


/**
 * \brief Open the software SPI communication
 */
void OpenSWSPI(void);

//! macro for definition of SWOpenSPI funcion
#define SWOpenSPI OpenSWSPI

/**
 *  \brief  Do a write in the software SPI
 *  \param output the data for write into the memory
 */
void WriteSWSPI( char output );

//! macro for definition of SWWriteSPI funcion
#define SWWriteSPI WriteSWSPI

/**
 *  \brief  Set the Chip Select (CS)
 */
void SetCSSWSPI(void);

//! macro for definition of SWSetCSSPI funcion
#define SWSetCSSPI SetCSSWSPI

/**
 *  \brief  Clear the Chip Select (CS)
 */
void ClearCSSWSPI(void);
#define SWClearCSSPI ClearCSSWSPI

/**************************************************************************
Macro       : putcSWSPI

Description : macro is identical to WriteSWSPI,#define to WriteSWSPI in sw_spi.h
 
Arguments   : None
 
Remarks     : None 
***************************************************************************/
#define putcSWSPI WriteSWSPI

/**************************************************************************
Macro       : SWputcSPI

Description : macro is identical to WriteSWSPI,#define to WriteSWSPI in sw_spi.h
 
Arguments   : None
 
Remarks     : None 
***************************************************************************/
#define SWputcSPI putcSWSPI

/**
 *  \brief  Read a byte from SPI channel
 *  \return the byte received
 */
BYTE ReadSWSPI( void );

#endif /* __SW_SPI_H */
