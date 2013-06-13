//! 
//!   Modulo para controle da interface serial
//!   Autor : Rafael Dias
//!   Data  : Ago/2009
//!

#include "serial.h"
#include "processor.h"
#include "funcoes.h"
#include <delays.h>

#define BRGH  1
#define BRG16 1


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

SERIALCOMFUNC   *isrSerialFunc;       //! ponteiro para função qye será responsável pelo tratamento dos dados recebidos via serial.
                                      //! com isso, a responsabilidade de tratamento de dados será passada para o modulo que chamou o 
                                      //! módulo de comunicaçõao serial
BYTE        cSerialBaudRate;          //! Baud Rate utilizado pelo modulo de comunicação serial
BYTE        cSerialStopBits;          //! Stop bits utilizado pelo modulo de comunicação serial
BYTE        cSerialParidade;          //! Paridade utilizada pelo modulo de comunicação serial

//--------------------------------------------------------------------------------------------

void InitSerial( BYTE port, BYTE baudRate, BYTE stopBits, BYTE par, SERIALCOMFUNC*  func ){
  
  WORD wTmp;
  BYTE i;
  
  // configuração do port serial
  INTCON  &= ~(BIT6 | BIT7);    //  GIE = 0; PEIE = 0;
  PIR1    &= ~(BIT4 | BIT5);    //  RCIF = 0
  PIE1    &= ~(BIT4 | BIT5);    //  RCIE = 0
  IPR1    &= ~(BIT4 | BIT5);    //  RCIP = 0
  RCSTA   &= ~(BIT7 | BIT2 | BIT1);  
  
  if ( baudRate > GET_VEC_NUM_MEMBERS(BaudRate) ){
    baudRate = BR_9600;
  }
  
  if ( stopBits > ST_2 ){
    stopBits = ST_1;
  }
  
  if ( par > PR_EVEN ){
    par = PR_NONE;
  }
  
  cSerialBaudRate = baudRate;
  cSerialParidade = par;
  cSerialStopBits = stopBits;
  
  // atribui o valor do baudrate
  wTmp = BRGValues[cSerialBaudRate];
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
  
  PIR1    |= BIT5;    //  RCIF = 1
  PIE1    |= BIT5;    //  RCIE = 1

  RCSTAbits.CREN = 1;
  RCSTAbits.SPEN = 1;

  INTCON  |= (BIT6 | BIT7);
                             
  if ( func != NULL ){
    isrSerialFunc = func;
  }
  
  return;
}

//--------------------------------------------------------------------------------------------

BYTE GetSerialBaudRate( void ){
  return cSerialBaudRate;
}

//--------------------------------------------------------------------------------------------

BYTE GetSerialStopBits( void ){
  return cSerialStopBits;
}

//--------------------------------------------------------------------------------------------

BYTE GetSerialParidade( void ){
  return cSerialParidade;
}

//--------------------------------------------------------------------------------------------

BYTE SerialGetchar( void ){
  return RCREG;
}

//--------------------------------------------------------------------------------------------

void SerialPutc( BYTE c ){
  
  while( TXSTAbits.TRMT == 0 );
  
  TXREG = c;
  
  Delay100TCYx( 5 );
}

//--------------------------------------------------------------------------------------------

void ReceiveOff( void ){
  RCSTAbits.CREN  = 0;
  RCSTAbits.SPEN  = 0;
  PIR1bits.RCIF   = 0;
  PIE1bits.RCIE   = 0;
  
  return;  
}

//--------------------------------------------------------------------------------------------

void ReceiveOn( void ){
  RCSTAbits.CREN = 1;
  RCSTAbits.SPEN = 1;
  PIE1bits.RCIE = 1;

	while ( PIR1bits.RCIF ) {
  	
  	if ( RCSTAbits.FERR ) {
    	RCSTAbits.FERR = 0;
    	continue;
    }

    if ( RCSTAbits.OERR ) {
    	RCSTAbits.OERR = 0;
    	continue;
    }
  	SerialGetchar();
  }
  return;
}

//--------------------------------------------------------------------------------------------

void SerialPuts( char *  s, BYTE len ){

  while( len-- > 0 ) {
    SerialPutc( *s );    
    s++;
  }
}

//--------------------------------------------------------------------------------------------

DWORD Baud2Int( enum COM_BaudRate c ){

  if ( c > GET_VEC_NUM_MEMBERS( BaudRate )){
    return BaudRate[BR_9600];
  }

  return BaudRate[c];
}
