//!
//! Modulo para controle e configuração da porta serial
//! Autor : Rafael Dias Menezes
//! Data  : Ago/2009
//! 
//! Changes: 
//!   + 03/03/2011 - add by rdias : interruption to serial tx buffer
//!

#ifndef __SERIAL__
#define __SERIAL__

#include "defs.h"

/**
 *  \brief define alguns tipos utilizados na configuração da paridade
 */
enum COM_Parity{
    PR_NONE = 0,
    PR_ODD, 
    PR_EVEN 
};

/**
 *  \brief define os baudrates possíves
 */
enum COM_BaudRate{
    BR_300 = 0,
    BR_1200,
    BR_2400,
    BR_4800,
    BR_9600,
    BR_19200,
    BR_38400,
    BR_57600,
    BR_115200
};

/**
 *  \brief define os stopbits possíveis.
 */
enum COM_StopBits{
    ST_1 = 0, 
    ST_2
};

//!
//! pointer function to a ISR routine.
//!
typedef void SERIALCOMFUNC(BYTE);

//!
//! data type for manage the comport configuration
typedef struct {
    BYTE bPort;                 //! port handle
    enum COM_BaudRate   bBaud;        //! baud rate configuration
    enum COM_StopBits   bStopBits;    //! stop bits configuration
    enum COM_Parity     bPar;         //! parity configuration
    SERIALCOMFUNC   *funcRX;
    SERIALCOMFUNC   *funcTX;
} COM_PORT_HANDLER;


/** 
 *  \brief  Inicializa a porta 
 *          Pré condição: verificar a configuração dos ports de entrada/saída e 
 *          controle no arquivo rs485.c
 *  \param  port UART que deverá ser utilizada para interface serial
 *  \param  baudRate    baudRate a ser utilizado
 *  \param  stopBits    stop bits utilizados para a interface serial
 *  \param  par         paridade
 *  \param  isrFunc     Ponteiro para função que realizará o tratamento dos dados recebidos pela serial.
 *  \return OK or fail status
 */
BYTE InitSerial( BYTE port, BYTE baudRate, BYTE stopBits, BYTE par, SERIALCOMFUNC*  func );

/**
 *  \brief Retorna o baudrate da interface rs485
 *  \return Baudrate atual
 */
BYTE GetSerialBaudRate( void );

/**
 *  \brief retorna o numero de stop bits da interface rs485
 *  \return stopbits atual
 */
BYTE GetSerialStopBits( void );

/**
 *  \brief retorna a paridade configurada para a inteface rs485
 *  \return paridade atual
 */
BYTE GetSerialParidade( void );

/**
 *  \brief realiza a leitura do último caracter recebido pela interface serial
 *  \return ultimo caracter recebido.
 */
BYTE SerialGetchar( void );

/**
 *  \brief envia um caracter pela intercafe serial
 *  \param c dado a ser enviado
 */
void SerialPutc( BYTE c );

/**
 *  \brief envia uma string pela interface serial
 *  \param s dado a ser enviado
 *  \param len numero de bytes a serem enviados
 */
//void SerialPuts( char *  s, BYTE len );
#define SerialPuts( s, len )  WriteTXBuffer( s, len )


/**
 *  \brief desliga a recepção de dados pela interface serial
 */
void ReceiveOff( void );


/**
 * \brief habilita a recepção de dados pela interface serial, com a limpeza do buffer de recepção
 */
void ReceiveOn( void );

/**
 *  \brief converte do tipo enum COM_BaudRate para DWORD
 *  \param c baudrate a ser convertido
 *  \return DWORD representativo do baudrate passado como parametro
 *  se o baurdare for invalido, retorna 9600
 */
DWORD Baud2Int( enum COM_BaudRate c );

/**
 *  \brief  converte de DWORD para o tipo enum COM_BaudRate
 *  \param  baud baudrate a ser convertido
 *  \return baud convertido para o tipo enum COM_BaudRate. Se o baudrate passado for invalido, retorna BR_9600
 */
enum COM_BaudRate Int2Baud( DWORD baud );

/**
 *  \brief  get a pointer to serial buffer head 
 *  \return 
 */
//BYTE* GetTXBufferPtr( void );

/**
 *  \brief  get a the actual tx buffer length
 *  \return 
 */
//int   GetTXBufferLen( void );

/** 
 *
 */
BYTE WriteTXBuffer( BYTE * data, BYTE len );

#endif  //~ __SERIAL__
