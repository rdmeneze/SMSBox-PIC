
/**
 * serial
 *  Performs the control of the serial data link
 *  Author: Rafael Dias Menezes
 *  company: Taioba Corporation
 *  email: rdmeneze@yahoo.com.br
 *  Date: ago/2009
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
 *  -- 08/2009 by rdias: Initial version
 */

#include "serial.h"
#include "processor.h"
#include "funcoes.h"
#include <delays.h>

#define BRGH  1
#define BRG16 1


#define BUFFER_TX_LEN  (256L)

#define SEND_BYTE( x )    while( TXSTAbits.TRMT == 0 ); \
                          TXREG = x;

//[rdias - 03/10/2012<]
#define MAX_COM_PORTS   2       //! define the maximum quantity of com ports in the system

#define COMPORT_ID      0x00FDAAAF
#define COMPORT_MAGIC   0xFFAA

//! alias for com ports handles
#define COM0    0
#define COM1    COM0+1
#define COM2    COM1+1
#define COM3    COM2+1
//[rdias - 03/10/2012>]


//! struct to define the prior
typedef struct {
    DWORD   ID;
    int magic;
    SERIALCOMFUNC   *isrSerialFuncRX;      //! function pointer to ISR of serial data in.
    SERIALCOMFUNC   *isrSerialFuncTX;    //! function pointer to ISR of serial data out.
    BYTE        cBaudRate;                      //! Baud Rate utilizado pelo modulo de comunicação serial
    BYTE        cStopBits;                      //! Stop bits utilizado pelo modulo de comunicação serial
    BYTE        cParidade;
    BYTE        *pBufferTX;                     //! buffer de transmissão entre o modem
    BYTE        *pBufferRX;                     //! buffer de transmissão entre o modem
    int         iTXHead;        //! ponter to initial current buffer transmittion position. This position will be modified for each BYTE that will sent by the serial port
    int         iTXTail;        //! ponter to initial current buffer transmittion position. This value will be changed for each write in the buffer;
    int         iRXHead;        //! ponter to initial current buffer reception position. This position will be modified for each BYTE that will sent by the serial port
    int         iRXTail;        //! ponter to initial current buffer reception position. This value will be changed for each write in the buffer;
    void        (*init)(void);
} COMPORT;

/**
 * Possiveis baudrates
 */
const DWORD BaudRate[] = {  
                      300L,
                      1200L,
                      2400L,
                      4800L,
                      9600L,
                      19200L,
                      38400L,
                      57600L,
                      115200L  
                      };
               
#if ( BRGH == 1 ) && (BRG16 == 1)
/**
 * valores prá-calculados para a carga de BRG:BRGU
 */                      
const WORD  BRGValues[] = { 
                      FOSC/(4*300L)    -1,
                      FOSC/(4*1200L)   -1,
                      FOSC/(4*2400L)   -1,
                      FOSC/(4*4800L)   -1,
                      FOSC/(4*9600L)   -1,
                      FOSC/(4*19200L)  -1,
                      FOSC/(4*38400L)  -1,
                      FOSC/(4*57600L)  -1,
                      FOSC/(4*115200L) -1
                    };
#else
  #error  "BRGH or BRG16 don't defined values"
#endif

SERIALCOMFUNC   *isrSerialFunc = NULL;//! ponteiro para função qye será responsável pelo tratamento dos dados recebidos via serial.
                                      //! com isso, a responsabilidade de tratamento de dados será passada para o modulo que chamou o 
                                      //! módulo de comunicaçõao serial
SERIALCOMFUNC   *isrSerialFuncTX = NULL;  //! ponteiro para função qye será responsável pelo envio dos dados presentes no buffer de transmissão
BYTE        cSerialBaudRate;          //! Baud Rate utilizado pelo modulo de comunicação serial
BYTE        cSerialStopBits;          //! Stop bits utilizado pelo modulo de comunicação serial
BYTE        cSerialParidade;          //! Paridade utilizada pelo modulo de comunicação serial
#pragma udata GSM_TX_BUFFER
volatile BYTE BufferTX[BUFFER_TX_LEN];   //! buffer de transmissão entre o modem 
#pragma udata
volatile int        iSerialTXHead = sizeof( BufferTX ) - 2 ;        //! ponter to initial current buffer position. This position will be modified for each BYTE that will sent by the serial port
volatile int        iSerialTXTail = sizeof( BufferTX ) - 2;        //! ponter to initial current buffer position. This value will be changed for each write in the buffer;

void initSerialPort0(void);
void initSerialPort1(void);

COMPORT comport[MAX_COM_PORTS] =
{
    {
        COMPORT_ID + COM0,
        0,
        NULL,
        NULL,
        0,
        0,
        0,
        NULL,
        NULL,
        0,
        0,
        0,
        0,
        initSerialPort0
    },
    {
        COMPORT_ID + COM1,
        0,
        NULL,
        NULL,
        0,
        0,
        0,
        NULL,
        NULL,
        0,
        0,
        0,
        0,
        initSerialPort1
    }
};

//--------------------------------------------------------------------------------------------

/**
 * @brief   send a byte by the serial link. Must be called by the TX ISR
 * @param   port used for communication
 */
void  SendNextByte( BYTE port );

//--------------------------------------------------------------------------------------------

/**
 * @brief   initialize the HAL for serial port 1
 * @param port
 * @param baudRate
 * @param stopBits
 * @param par
 * @param func
 * @return
 */
void initSerialPort1(void)
{
    
}

//--------------------------------------------------------------------------------------------

void initSerialPort2(void)
{

}

//--------------------------------------------------------------------------------------------

BYTE InitSerial( BYTE port, BYTE baudRate, BYTE stopBits, BYTE par, SERIALCOMFUNC*  func )
{
  WORD wTmp;    //! local variable
  COMPORT * pComport = NULL;
  BYTE i;
  
#ifdef __DEBUG
  int i;
#endif
  
  //[rdias<]
  if ( port > 1 )
  {
      return -1;
  }
  //[rdias>]

  pComport = comport + port;
  if ( pComport->magic == COMPORT_MAGIC )
  {
      return 0;     // a porta já está configurada
  }

  // configuração do port serial
  INTCONbits.GIE    = 0;
  INTCONbits.PEIE   = 0;

  switch ( port )
  {
    case COM0:
      PIR1bits.TXIF     = 0;
      PIR1bits.RC1IF    = 0;
      IPR1bits.TX1IP    = 0;
      IPR1bits.RC1IP    = 0;
      RCSTA1bits.OERR   = 0;
      RCSTA1bits.FERR   = 0;
      RCSTA1bits.SPEN   = 0;
    break;

    case COM1:
      PIR3bits.TX2IF    = 0;
      PIR3bits.RC2IF    = 0;
      IPR3bits.TX2IP    = 0;
      IPR3bits.RC2IP    = 0;
      RCSTA2bits.OERR   = 0;
      RCSTA2bits.FERR   = 0;
      RCSTA2bits.SPEN   = 0;
    break;

  default:
      return 0;
  }

  //INTCON  &= ~(BIT6 | BIT7);    //  GIE = 0; PEIE = 0;
  //PIR1    &= ~(BIT4 | BIT5);    //  RCIF = 0
  //PIE1    &= ~(BIT4 | BIT5);    //  RCIE = 0
  //IPR1    &= ~(BIT4 | BIT5);    //  RCIP = 0
  //RCSTA   &= ~(BIT7 | BIT2 | BIT1);

  pComport->magic       =   COMPORT_MAGIC;
  pComport->cBaudRate   =   ( baudRate > GET_VEC_NUM_MEMBERS(BaudRate)) ? BR_9600 : baudRate;
  pComport->cStopBits   =   ( stopBits > ST_2 ) ? ST_1 : stopBits;
  pComport->cParidade   =   ( par > PR_EVEN ) ? ST_1 : par;
  pComport->init();

  #ifdef __DEBUG  
  for ( i = 0; i < GET_VEC_NUM_MEMBERS( BufferTX ); i++ )
  {
    BufferTX[i] = (i % 2) ? 0xAA : 0x55;
  } 
  #endif 
  //[rdias_20121016<]
  //cSerialBaudRate = baudRate;
  //cSerialParidade = par;
  //cSerialStopBits = stopBits;
  //[rdias_20121016>]

  // atribui o valor do baudrate
  wTmp = BRGValues[pComport->cBaudRate];
  //[rdias_20121016<]
  //wTmp = BRGValues[cSerialBaudRate];
  //[rdias_20121016>]
  SPBRG = wTmp;
  
  #if ( BRG16 == 1 )
    SPBRGH = wTmp/256;
  #endif
  
  // configura portas como entrada
  TRISC |= (BIT7 | BIT6);       // TRISC.7 e TRISC.6 => entradas
  
  #if BRG16 == 1
    BAUDCON |= BIT3;      // 16-bit Baud Rate Generator
  #endif

  #ifdef __18F4620_H
    BAUDCONbits.RXDTP  = 0; // porta RX não invertido
    BAUDCONbits.TXCKP = 0;  // estado inativo TX em nível alto
  #endif
  BAUDCONbits.WUE   = 0;  // não usado como Wake-Up.
  BAUDCONbits.ABDEN = 0;  // auto detecção de baudrate desabilitada

  // configura USART para transmitir com 8 bits de dados, sem paridade 
  TXSTAbits.SYNC = 0;
  TXSTAbits.TXEN = 1;

  #if ( BRGH == 1 )
    TXSTA |= BIT2;
  #else
    TXSTA &= ~BIT2;
  #endif
  
  //PIR1    |= BIT5;    //  RCIF = 1
  PIE1    |= BIT5;    //  RCIE = 1
  //...
  
  RCSTAbits.CREN = 1;
  RCSTAbits.SPEN = 1;

  INTCON  |= (BIT6 | BIT7);
                             
  if ( func != NULL )
  {
    isrSerialFunc = func;
  }

  isrSerialFuncTX = SendNextByte;
  
  return 0;
}

//--------------------------------------------------------------------------------------------

BYTE GetSerialBaudRate( void )
{
  return cSerialBaudRate;
}

//--------------------------------------------------------------------------------------------

BYTE GetSerialStopBits( void )
{
  return cSerialStopBits;
}

//--------------------------------------------------------------------------------------------

BYTE GetSerialParidade( void )
{
  return cSerialParidade;
}

//--------------------------------------------------------------------------------------------

BYTE SerialGetchar( void )
{
  return RCREG;
}

//--------------------------------------------------------------------------------------------

void SerialPutc( BYTE c )
{
  //while( TXSTAbits.TRMT == 0 );
  
  //TXREG = c;

  SEND_BYTE( c );
  
  Delay100TCYx( 5 );
}

//--------------------------------------------------------------------------------------------

void ReceiveOff( void )
{
  RCSTAbits.CREN  = 0;
  RCSTAbits.SPEN  = 0;
  PIR1bits.RCIF   = 0;
  PIE1bits.RCIE   = 0;
  
  return;  
}

//--------------------------------------------------------------------------------------------

void ReceiveOn( void )
{
    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;
    PIE1bits.RCIE = 1;

    while ( PIR1bits.RCIF )
    {
  	
        if ( RCSTAbits.FERR )
        {
        RCSTAbits.FERR = 0;
        continue;
        }

        if ( RCSTAbits.OERR )
        {
            RCSTAbits.OERR = 0;
            continue;
        }
        SerialGetchar();
    }
    return;
}

//--------------------------------------------------------------------------------------------

//void SerialPuts( char *  s, BYTE len ){

  //while( len-- > 0 ) {
  //  SerialPutc( *s );    
  //  s++;
  //}

//  WriteTXBuffer( s, len );
//}

//--------------------------------------------------------------------------------------------

DWORD Baud2Int( enum COM_BaudRate c ){

  if ( c > GET_VEC_NUM_MEMBERS( BaudRate ))
  {
    return BaudRate[BR_9600];
  }

  return BaudRate[c];
}

//--------------------------------------------------------------------------------------------

BYTE WriteTXBuffer( BYTE * data, BYTE len )
{
  int iCounter;
  int i;
  BYTE * pData;
  
  iCounter = (int)len ;
  iCounter += iSerialTXTail;

  pData = data;
  for ( i = iSerialTXTail; (i < iCounter) && (i < GET_VEC_NUM_MEMBERS( BufferTX )); i++ )
  {
    *(BufferTX + i) = *pData++;
  }

  if ( i != iCounter )
  {
    iCounter -= GET_VEC_NUM_MEMBERS( BufferTX );
  
    for ( i = 0; i < iCounter; i++ )
    {
      *(BufferTX + i) = *pData++;
    }
  }

  iSerialTXTail = i;

  //PIR1bits.TXIF = 0;
  //PIE1    |= BIT4;    //  TXIE = 1. Habilita a interrupção de buffer de transmissão vazio
  BIT_SET( PIE1, 4 );

  return 0;
}

//--------------------------------------------------------------------------------------------

//BYTE* GetTXBufferPtr( void )
//{
//  return NULL;
//}

//--------------------------------------------------------------------------------------------

//int   GetTXBufferLen( void )
//{
//  return 0;
//}

//--------------------------------------------------------------------------------------------

void  SendNextByte( BYTE  val )
{
  BYTE * pData;

  if ( iSerialTXHead == iSerialTXTail )
  {
    //não há mais nada para enviar
    BIT_CLEAR( PIE1, 4 );
    return;
  }

  pData = BufferTX + iSerialTXHead++;

  TXREG = *pData;  

  if ( iSerialTXHead == sizeof ( BufferTX ) )
  {
    iSerialTXHead = 0;
  }

  return; 
}

//--------------------------------------------------------------------------------------------

