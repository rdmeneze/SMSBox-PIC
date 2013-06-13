/**
 * SerialPC
 *  Performs the control of communication protocol between the host computer and the GSM control module.
 *  Author: Rafael Dias Menezes
 *  company: Taioba Corporation
 *  email: rdmeneze@yahoo.com.br
 *  Date: sep/2009
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
 * - Modifications
 *  -- 09/2009 by rdias: Initial version
 *  -- 10/2009 by rdias: Timer overflow between host messages
 *  -- 15/12/2009 by rdias : implementation of version and sonda packages
 *  -- 02/02/2010 by rdias : log schema
 *  -- 28/02/2011 by rdias : updates, new implementations and optimizations in the Version, HELLO and bootloader comands
 */


#include "serialPC.h"
#include "serial.h"
#include "defs.h"
#include "cmd_serialPC.h"
#include "sw_uart.h"
#include <string.h>
#include "status.h"
#include "cpu.h"
#include "timer.h"
#include "version.h"
#include "log.h"
#include "funcoes.h"
#include "serialNumber.h"
#include "cpu.h"
#include "delay.h"
#include "bootloader.h"
#include "changefirmware.h"

/*******************************************************************************************************************************************************
	
	FORMATO DA MENSAGEM	DE DADOS

	 ------------------------------------------------
	| STX | ED | EO | LEN | DO D1 ... DN | LRC | ETX |
	 ------------------------------------------------

	STX		start of text (0x02)

	ED		endereço de destino em uma rede 485

	EO		endereço de origem em uma rede 485

	LEN		tamanho do dados da mensagem

	DO .. DN	dados da mensagem

	LRC		XOR de todos os bytes a partir do campo ED até o campo DN inclusive, excluir STX e ETX.

	ETX		end text (0x03)

	O endereço 0x00 é utilizado pelo servidor que é a máquina onde fica a Switch.

	*******************************************************************************************************************************************************/


//----------------------------------------
//  
// state machine definitions
#define ST_STX  0
#define ST_DATA 1
#define ST_ED   2
#define ST_EO   3
#define ST_LEN  4
#define ST_LRC  5    
#define ST_ETX  6 
#define ST_DLE  7

// 
#define STX         0x02
#define ETX         0x03
#define DLE         0x10        // novo
#define DLE_CHAR    0x20
//
#define CHAR_DELAY        64L
#define DELAY_INT_CHAR    10L
#define TIMEOUT_COM_PC    (((CHAR_DELAY*11L*1000L)/SWBAUD) + DELAY_INT_CHAR)

#define SONDA_TIMEOUT     5000L   // timeout para considerar host desconectado
//----------------------------------------
#pragma udata SERIALPC_BUFFER
volatile BYTE serialPC_Buffer[BUFFER_DATA_LEN];
//BYTE bVarzea1[32];
#pragma udata
#pragma udata SERIALPC_CMD_BUFFER
BYTE cmdBuffer[BUFFER_DATA_LEN];
//BYTE bVarzea2[32];
#pragma udata


volatile BYTE serialPC_ProcessaPkt;            //! flag indicativa de que pode processar o pacote
volatile BYTE stSerialPC;                      //! estado de operação da máquina de estado da recepção serial. 
volatile BYTE serialPC_CRC;                    //! CRC acumulado no pacote recebido. 
volatile BYTE serialPC_DLE = 0;                //! indica se chegou um caracter DLE
volatile BYTE serialPC_DataLen;                //! tamanho da última mensagem recebida
volatile BYTE serialPC_DataCounter;            //! controle de onde se deve escrever no buffer de recepção

volatile BYTE serialPC_ContPackages = 0;

extern struct LogBuffer logBuffer;    //! declarado em log.c. Tentei acessar via ponteiro far e não funcionou. 
                                      //! Estarei usando na função GET_LOG

#ifdef _USE_SERIALPC_TIMEOUT
  TIMER_HANDLE serialPC_timer;        //! timer de timeout de recepção
#endif

#ifdef USE_SONDA
  TIMER_HANDLE serialPC_SondaTimer;   //! timer SONDA. Quando o mesmo estoura, o estado do SMS Box passa para 
                                      //!   OffLine, não aceitando mais comandos via interface serial até que HOST 
                                      //!   envie um HELLO
#endif

//----------------------------------------
BYTE enviarPacotePC(BYTE * buffer, BYTE len );      //! envia mensagem para o HOST

//! funções de processamento dos pacotes do protocolo de comunicação serial entre o HOST e o SMS BOX
void ProcessaCMD_HELLO( BYTE * buffer );
void ProcessaCMD_SONDA( BYTE * buffer );
void ProcessaCMD_STATUS( BYTE * buffer );
void ProcessaCMD_VERSION( BYTE * buffer );
void ProcessaCMD_GET_LOG( BYTE * buffer );
void ProcessaCMD_BOOTLOADER_UPLOAD_FW( BYTE * buffer );
void ProcessaCMD_BOOTLOADER_GETCRC32( BYTE * buffer );
void ProcessaCMD_BOOTLOADER_CHANGEFW( BYTE * buffer );
void enviaACK( BYTE dest );
void enviaNACK( BYTE dest, BYTE errCode );
void MakeHeader( BYTE * bufOut, BYTE bLen, BYTE bIDDest, BYTE bCmd );
//----------------------------------------

void SerialPCInit( void ){
  serialPC_ProcessaPkt = FALSE;
  stSerialPC = ST_STX;
  serialPC_CRC = 0;
  serialPC_DataLen = 0;

#ifdef _USE_SERIALPC_TIMEOUT
  serialPC_timer = TIMER_NULL;
#endif

#ifdef USE_SONDA
  serialPC_SondaTimer = TIMER_NULL;
#endif
  
  OpenUART();
  return;
}

//----------------------------------------
//CDantas -> Alterada função para trabalhar com Serial Emulada
void ProcessaProtocolo( BYTE bData ){

  if ( serialPC_DataCounter >= sizeof( serialPC_Buffer ) ) {
    serialPC_DataCounter = 0;
    stSerialPC = ST_STX;
    return;
  }

  switch( stSerialPC  ) {
    case ST_STX:
      serialPC_CRC = 0;
      serialPC_DataLen = 0;
      serialPC_DataCounter = 0;

      #ifdef _USE_SERIALPC_TIMEOUT
      serialPC_timer = GetTimer( TIMEOUT_COM_PC );
      #endif

      if ( bData == STX ){
        stSerialPC = ST_ED;
      }
      break;

    case ST_ED:
    case ST_EO:
    case ST_LEN:
    case ST_DATA:
    case ST_LRC:
      
      if ( stSerialPC == ST_DATA ) {

        if ( serialPC_DLE == 1 ){
          serialPC_Buffer[serialPC_DataCounter] = bData ^ DLE_CHAR;
          serialPC_CRC ^= bData;
          serialPC_DataCounter++;

          serialPC_DLE = 0;
        }     
        else{
          if ( (bData == DLE)||(bData == ETX)||(bData == STX) ){
            serialPC_DLE = 1;
          }
          else{
            serialPC_Buffer[serialPC_DataCounter] = bData;
            serialPC_CRC ^= bData;
            serialPC_DataCounter++;
          }
        }
      }
      else{
        serialPC_Buffer[serialPC_DataCounter] = bData;
        serialPC_CRC ^= bData;
        serialPC_DataCounter++;
      }

      #ifdef _USE_SERIALPC_TIMEOUT
      RestartTimer( serialPC_timer , TIMEOUT_COM_PC );
      #endif

      switch( stSerialPC ){ 
        case ST_ED:
          if ( bData != GetID() ){
            //pacote não é para este SMS Box
            serialPC_CRC = 0;
            serialPC_DataCounter = 0;
            stSerialPC = ST_STX;
            serialPC_ProcessaPkt = FALSE;
      
            #ifdef _USE_SERIALPC_TIMEOUT
            ReleaseTimer( &serialPC_timer  );        
            #endif
          }
          else{
            stSerialPC = ST_EO;
          }
          break;

        case ST_EO:
          stSerialPC = ST_LEN;
          break;
        case ST_LEN:
          stSerialPC = ST_DATA;
          break; 
        case ST_DATA:
          if ( serialPC_Buffer[LEN_FIELD] == ( serialPC_DataCounter - DATA_FIELD )){
            stSerialPC = ST_LRC;          
          }
          break; 
        
        case ST_LRC:
          if ( serialPC_CRC ){
            serialPC_CRC = 0;
            serialPC_DataCounter = 0;
            stSerialPC = ST_STX;
            serialPC_ProcessaPkt = FALSE;
          }
          stSerialPC = ST_ETX;
          break;
      }
      break;


   case ST_ETX:
      serialPC_CRC = 0;
      serialPC_DataCounter = 0;
      stSerialPC = ST_STX;
      serialPC_ProcessaPkt = TRUE;

      if ( bData != ETX ){
        serialPC_ProcessaPkt = FALSE;
      }
      
      #ifdef _USE_SERIALPC_TIMEOUT  
      ReleaseTimer( &serialPC_timer  );
      #endif

      break;

    default:
      serialPC_CRC = 0;
      serialPC_DataCounter = 0;
      stSerialPC = ST_STX;
      serialPC_ProcessaPkt = FALSE;

      #ifdef _USE_SERIALPC_TIMEOUT
      ReleaseTimer( &serialPC_timer  );
      #endif
  }
  return;
}

//----------------------------------------

void ProcessaPacotes( void ){
  BYTE dataLen;

  //if ( serialPC_timer != TIMER_NULL ){
  //  // verifica se houve um timeout entre a recepção de caracteres em uma mensagem
  //  // se houver, descarta o pacote
  //  if ( IsTimerTimeOut( serialPC_timer ) == TRUE ){
  //    serialPC_CRC = 0;
  //    serialPC_DataCounter = 0;
  //    stSerialPC = ST_STX;
  //    serialPC_ProcessaPkt = FALSE;
  //    ReleaseTimer( &serialPC_timer );
  //    return;
  //  }
  //}

#ifdef USE_SONDA
  if ( serialPC_SondaTimer != TIMER_NULL ){
    if ( IsTimerTimeOut( serialPC_SondaTimer ) == TRUE ){
      // ocorreu um timeout no timer SONDA. Altera o estado do SMS Box para offline     
      CleanStatus( ST_COM_PC_OK );

      // libera o recurso do timer
      ReleaseTimer( &serialPC_SondaTimer );
    }
  }
  else{
    // não está conectado e deve ignorar pacote
    return;
  }
#endif

  
  #ifdef _USE_SERIALPC_TIMEOUT
  if ( IsTimerTimeOut( serialPC_timer ) == TRUE ){
    serialPC_CRC = 0;
    serialPC_DataCounter = 0;
    stSerialPC = ST_STX;
    serialPC_ProcessaPkt = FALSE;
    ReleaseTimer( &serialPC_timer );
    return;
  }
  #endif


  if ( serialPC_ProcessaPkt == FALSE ){
    return;
  }

  serialPC_ProcessaPkt = FALSE;
  dataLen = serialPC_Buffer[LEN_FIELD];
  memcpy( (void*)cmdBuffer, (void*)(serialPC_Buffer + ED_FIELD), dataLen + 4 );

  switch( cmdBuffer[CMD_FIELD] ) {
    case  CMD_HELLO :
      ProcessaCMD_HELLO( cmdBuffer );
      return;

#ifdef USE_SONDA
    case CMD_SONDA:
      ProcessaCMD_SONDA( cmdBuffer );
      return;
#endif

    case CMD_STATUS:
      ProcessaCMD_STATUS( cmdBuffer );
      return;

    case CMD_VERSION:
      ProcessaCMD_VERSION( cmdBuffer );
      return;

    case CMD_GET_LOG:
      ProcessaCMD_GET_LOG( cmdBuffer );
      return;

    //! Upload firmware command
    case CMD_BOOTLOADER_UPLOAD_FW:
      enviaNACK( cmdBuffer[ED_FIELD] , DONT_NOT_FUNC );
      //ProcessaCMD_BOOTLOADER_UPLOAD_FW( cmdBuffer );
      return;

    //! get the CRC32 for validate the firmware upload
    case CMD_BOOTLOADER_GETCRC32:
      enviaNACK( cmdBuffer[ED_FIELD] , DONT_NOT_FUNC );
      //ProcessaCMD_BOOTLOADER_GETCRC32( cmdBuffer );
      return;

    //! call the firmware change routine
    case CMD_BOOTLOADER_CHANGEFW:
      enviaNACK( cmdBuffer[ED_FIELD] , DONT_NOT_FUNC );
      //ProcessaCMD_BOOTLOADER_CHANGEFW( cmdBuffer );
      return;

    default:
      return;
  }
}

//----------------------------------------

void ProcessaCMD_HELLO( BYTE * buffer ){

  BYTE bufOut[8];
  BYTE bLog;
  DWORD dwSerNum;
  char i;

  bLog = EVT_SW_HELLO;
  Log( EVT_SW, &bLog, sizeof( BYTE ));  

  dwSerNum = GetSerialNumber();

  // altera o estado do SMS Box para conectado com o Host
  SetStatus( ST_COM_PC_OK );
  
#ifdef USE_SONDA
  // timer para controle de conexão do host
  serialPC_SondaTimer = GetTimer( SONDA_TIMEOUT );
#endif
  
  MakeHeader( bufOut, sizeof( bufOut ), buffer[EO_FIELD], CMD_HELLO );

  for ( i = sizeof( DWORD ) ; i ; i-- )
  {
    bufOut[ CMD_FIELD + (sizeof(DWORD) - (i - 1)) ] = ((BYTE*)&dwSerNum)[(i - 1)];
  } 

  enviarPacotePC( bufOut, sizeof( bufOut ));
}

//----------------------------------------

BYTE enviarPacotePC(BYTE * buffer, BYTE len ){
  
  BYTE crc = 0;
  BYTE bData;
  BYTE i;

  putcUART( STX );
  for( i = 0 ; i < len; i++ ){
    bData = buffer[i];
    
    if ( i >= DATA_FIELD ){
      if ( ( bData == STX ) || ( bData == ETX ) || ( bData == DLE )){
        putcUART( DLE );
        putcUART( bData ^ DLE_CHAR );
        crc ^= bData;
        continue;
      }
    }

    putcUART( bData );
    crc ^= bData;
  }
  putcUART( crc );
  putcUART( ETX );
  return TRUE;
}

//----------------------------------------


void enviaACK( BYTE dest ){
  BYTE buffer[4];

  MakeHeader( buffer, sizeof( buffer ), dest, ACK );
  enviarPacotePC( buffer, sizeof( buffer ));
}

//----------------------------------------

void enviaNACK( BYTE dest, BYTE errCode ){
  BYTE buffer[5];

  MakeHeader( buffer, sizeof( buffer ), dest, NACK );

  buffer[ CMD_FIELD+1 ] = errCode;

  enviarPacotePC( buffer, sizeof( buffer ));
}

//----------------------------------------

BYTE IsConnected( void ){
  return ((GetStatus( ) & ST_COM_PC_OK) ? 1 : 0);
}

//----------------------------------------

void EnviaCMD_MODEM( BYTE * buffer, int len ){
  BYTE bLen;
  int i;

  if ( !IsConnected() ){
    return;          
  }

  Log( EVT_USR, buffer, len);

  for( i = len-1; i >= 0; i-- ){
    buffer[CMD_FIELD + 1 + i] = buffer[i];
  }

  buffer[ ED_FIELD  ] = SERVER_ID;
  buffer[ EO_FIELD  ] = GetID();
  buffer[ LEN_FIELD ] = len + 1;
  if ( buffer[ LEN_FIELD ] > 247 )
  {
    
  }

  buffer[ CMD_FIELD ] = CMD_MODEM;

  enviarPacotePC( buffer, buffer[ LEN_FIELD ] + 3 );
}

//----------------------------------------

void ProcessaCMD_SONDA( BYTE * buffer ){
#ifdef USE_SONDA
  BYTE bufOut[4];
  BYTE bLog;

  if ( !IsConnected() ){
    return;          
  }
  
  bLog = EVT_SW_SONDA;
  Log( EVT_SW, &bLog, sizeof( BYTE ));

  RestartTimer( serialPC_SondaTimer, SONDA_TIMEOUT );

  MakeHeader( bufOut, sizeof( bufOut ), buffer[EO_FIELD], CMD_SONDA );

  enviarPacotePC( bufOut, sizeof( bufOut ));
#endif
}

//----------------------------------------

void ProcessaCMD_STATUS( BYTE * buffer ){
  BYTE bufOut[6];
  WORD wStatus;
  BYTE bLog;

  if ( !IsConnected() ){
    return;          
  }

  bLog = EVT_SW_STATUS;
  Log( EVT_SW, &bLog, sizeof( BYTE ));

  wStatus = GetStatus();

  MakeHeader( bufOut, sizeof( bufOut ), buffer[EO_FIELD], CMD_STATUS );

  bufOut[ CMD_FIELD + 1 ] = HIBYTE( wStatus );
  bufOut[ CMD_FIELD + 2 ] = LOBYTE( wStatus );

  enviarPacotePC( bufOut, sizeof( bufOut ));
}

//----------------------------------------

void ProcessaCMD_VERSION( BYTE * buffer )
{
  BYTE bufOut[16];
  BYTE  bLog;
  DWORD* dwTmp[3];
  BYTE bTmp;
  char i;

  if ( !IsConnected() )
  {
    return;          
  }

  bLog = EVT_SW_VERSION;
  Log( EVT_SW, &bLog, sizeof( BYTE ));

  MakeHeader( bufOut, sizeof( bufOut ), buffer[EO_FIELD], CMD_VERSION );

  dwTmp[0] = GetBoardVersion();
  dwTmp[1] = GetFirmwareVersion();
  dwTmp[2] = GetBootLoaderVersion();

  for ( bLog = 0; bLog < GET_VEC_NUM_MEMBERS(dwTmp); bLog++ )
  {
    for ( i = sizeof( DWORD ) ; i ; i-- )
    {
      bTmp = CMD_FIELD + (bLog << 2) + (sizeof(DWORD) - (i - 1));
      bufOut[ bTmp ] = ((BYTE*)dwTmp[bLog])[(i - 1)];
    } 
  }

  enviarPacotePC( bufOut, sizeof( bufOut ));    
}

//----------------------------------------


void ProcessaCMD_GET_LOG( BYTE * buffer ){

  if ( !IsConnected()){
    return;
  } 
  
  if ( GetLog( NULL ) == TRUE ){    // get a pointer to log structure
    buffer[ ED_FIELD ]  = buffer[ EO_FIELD ];
    buffer[ EO_FIELD ]  = GetID();
    buffer[ CMD_FIELD ] = CMD_GET_LOG;
    buffer[ LEN_FIELD ] = logBuffer.bLen + 5;  

    buffer[ CMD_FIELD + 1 ] = logBuffer.bCode;
    buffer[ CMD_FIELD + 2 ] = logBuffer.bLen;  
    buffer[ CMD_FIELD + 3 ] = HIBYTE( logBuffer.wStamp );  
    buffer[ CMD_FIELD + 4 ] = LOBYTE( logBuffer.wStamp );  
    memcpy( (void*)&buffer[CMD_FIELD + 5],  (void*)logBuffer.bBuffer,  logBuffer.bLen );

    enviarPacotePC( buffer, buffer[ LEN_FIELD ] + 3 ); 
    return;
  }

  enviaNACK( buffer[ EO_FIELD ], NO_MORE_DATA );
  return;
}

//----------------------------------------

void ProcessaCMD_BOOTLOADER_UPLOAD_FW( BYTE * buffer ){
  
  BYTE bufOut[5];
  BYTE bLen;

  if ( !IsConnected()){
    return;
  } 

  serialPC_ContPackages++;

  //enviaACK( buffer[EO_FIELD] );
  bLen = buffer[LEN_FIELD]-1; // retirado do comprimento o equivalente ao campo CMD

  MakeHeader( bufOut, sizeof( bufOut ), buffer[EO_FIELD], CMD_BOOTLOADER_UPLOAD_FW );
 
  if ( bLen > (BOOT_LOADER_FRAME_LEN + sizeof( DWORD )) ){
    bufOut[CMD_FIELD+1] = BOOT_LOADER_FLASH_FRAME_TOO_LONG;  
  }
  else{
    bufOut[CMD_FIELD+1] = UpLoad2Flash( (BYTE*)&buffer[CMD_FIELD+1], bLen );
    //bufOut[CMD_FIELD+1] = 1;
  }

  enviarPacotePC( bufOut, sizeof( bufOut ));

  serialPC_ContPackages--;
  return;
}

//----------------------------------------

void ProcessaCMD_BOOTLOADER_GETCRC32( BYTE * buffer ){
  BYTE bufOut[8];
  DWORD crc32;

  if ( !IsConnected( ) ){
    return;
  }  

  MakeHeader( bufOut, sizeof( bufOut ), buffer[EO_FIELD], CMD_BOOTLOADER_GETCRC32 );

  crc32 = GetCalcCRC32();
  ResetCRC32( );

  bufOut[CMD_FIELD + 1] = HIBYTE( HIWORD( crc32 ) );
  bufOut[CMD_FIELD + 2] = LOBYTE( HIWORD( crc32 ) );
  bufOut[CMD_FIELD + 3] = HIBYTE( LOWORD( crc32 ) );
  bufOut[CMD_FIELD + 4] = LOBYTE( LOWORD( crc32 ) );

  enviarPacotePC( bufOut, sizeof( bufOut ));
}

//----------------------------------------

void ProcessaCMD_BOOTLOADER_CHANGEFW( BYTE * buffer ){

  BYTE bufOut[5];

  if ( !IsConnected( ) ){
    return;
  }  

  MakeHeader( bufOut, sizeof( bufOut ), buffer[EO_FIELD], CMD_BOOTLOADER_CHANGEFW );

  bufOut[CMD_FIELD+1 ]  = ChangeFirmware();    

  // unreachable code
  enviarPacotePC( bufOut, sizeof( bufOut ));
  return;
}

//----------------------------------------

void MakeHeader( BYTE * bufOut, BYTE bLen, BYTE bIDDest, BYTE bCmd ){
  bufOut[ED_FIELD    ]  = bIDDest;
  bufOut[EO_FIELD    ]  = GetID();
  bufOut[LEN_FIELD   ]  = bLen - CMD_FIELD;
  bufOut[CMD_FIELD   ]  = bCmd;    
  return;
}

//----------------------------------------
