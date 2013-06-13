#ifndef __PORTS__
#define __PORTS__

#include "processor.h"

// software serial
#define PC_RXD          PORTBbits.RB0
#define PC_RXD_DIR      TRISBbits.TRISB0
#define PC_TXD          LATCbits.LATC1
#define PC_TXD_DIR      TRISCbits.TRISC1

//  GSM_CONTROL
#define GSM_PWRKEY            LATDbits.LATD5
#define GSM_PWRKEY_DIR        TRISDbits.TRISD5 
#define GSM_STATUS            PORTDbits.RD6
#define GSM_STATUS_DIR        TRISDbits.TRISD6
#define GSM_AC_SIM_PRES       LATDbits.LATD7
#define GSM_AC_SIM_PRES_DIR   TRISDbits.TRISD7

// LED Status
#define LED                 LATCbits.LATC0
#define LED_DIR             TRISCbits.TRISC0

// flash memory pinout interface
//#define FLASH_SDO         LATCbits.LATC5
//#define FLASH_SDO_DIR     TRISCbits.TRISC5
//#define FLASH_SDI         PORTCbits.RC4
//#define FLASH_SDI_DIR     TRISCbits.TRISC4
//#define FLASH_SCL         LATCbits.LATC3
//#define FLASH_SCL_DIR     TRISCbits.TRISC3
//#define FLASH_SPI_CS      LATCbits.LATC2
//#define FLASH_SPI_CS_DIR  TRISCbits.TRISC2

// SIMs Cards

#if BOARD_VERSION == 0x01000000
  
  #define EN_SIM_CARD_00       LATAbits.LATA0
  #define EN_SIM_CARD_00_DIR   TRISAbits.TRISA0
  #define EN_SIM_CARD_01       LATAbits.LATA1
  #define EN_SIM_CARD_01_DIR   TRISAbits.TRISA1
  #define EN_SIM_CARD_02       LATAbits.LATA2
  #define EN_SIM_CARD_02_DIR   TRISAbits.TRISA2
  #define EN_SIM_CARD_03       LATAbits.LATA3
  #define EN_SIM_CARD_03_DIR   TRISAbits.TRISA3
  #define EN_SIM_CARD_04       LATAbits.LATA4
  #define EN_SIM_CARD_04_DIR   TRISAbits.TRISA4
  #define EN_SIM_CARD_05       LATAbits.LATA5
  #define EN_SIM_CARD_05_DIR   TRISAbits.TRISA5
  #define EN_SIM_CARD_06       LATBbits.LATB1
  #define EN_SIM_CARD_06_DIR   TRISBbits.TRISB1
  #define EN_SIM_CARD_07       LATBbits.LATB2
  #define EN_SIM_CARD_07_DIR   TRISBbits.TRISB2
  #define EN_SIM_CARD_08       LATBbits.LATB3
  #define EN_SIM_CARD_08_DIR   TRISBbits.TRISB3
  #define EN_SIM_CARD_09       LATBbits.LATB4
  #define EN_SIM_CARD_09_DIR   TRISBbits.TRISB4
  #define EN_SIM_CARD_10       LATBbits.LATB5
  #define EN_SIM_CARD_10_DIR   TRISBbits.TRISB5
  #define EN_SIM_CARD_11       LATDbits.LATD0
  #define EN_SIM_CARD_11_DIR   TRISDbits.TRISD0
  #define EN_SIM_CARD_12       LATDbits.LATD1
  #define EN_SIM_CARD_12_DIR   TRISDbits.TRISD1
  #define EN_SIM_CARD_13       LATDbits.LATD2
  #define EN_SIM_CARD_13_DIR   TRISDbits.TRISD2
  #define EN_SIM_CARD_14       LATDbits.LATD3
  #define EN_SIM_CARD_14_DIR   TRISDbits.TRISD3
  #define EN_SIM_CARD_15       LATDbits.LATD4
  #define EN_SIM_CARD_15_DIR   TRISDbits.TRISD4

#elif (  ( BOARD_VERSION == 0x01010000 ) | \
         ( BOARD_VERSION == 0x01020000 )   \
      )
  
  #define SIM_SEL              LATA
  #define SIM_SEL_MASK         0x0F
  #define SIM_SEL_SHIFT        0
  #define SIM_SEL_00           LATAbits.LATA0
  #define SIM_SEL_00_DIR       TRISAbits.TRISA0
  #define SIM_SEL_01           LATAbits.LATA1
  #define SIM_SEL_01_DIR       TRISAbits.TRISA1
  #define SIM_SEL_02           LATAbits.LATA2
  #define SIM_SEL_02_DIR       TRISAbits.TRISA2
  #define SIM_SEL_03           LATAbits.LATA3
  #define SIM_SEL_03_DIR       TRISAbits.TRISA3
  #define SIM_SEL_EN           LATAbits.LATA4
  #define SIM_SEL_EN_DIR       TRISAbits.TRISA4
#else
  #error "BOARD_VERSION indefined"
#endif

#endif
