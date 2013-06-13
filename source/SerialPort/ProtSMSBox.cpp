#include "stdafx.h"
#include "ProtSMSBox.h"
#include "cmd_SMSBOX.h"

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
using namespace smsbox;

//------------------------------------------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------------------------------------------

volatile BYTE serialPC_ProcessaPkt;   //! flag indicativa de que pode processar o pacote
BYTE stSerialPC = 0;                  //! operação da máquina de estado da porta de recepção serial. 
BYTE serialPC_CRC = 0;                //! CRC acumulado no pacote recebido. 
BYTE serialPC_DLE = 0;                //! indica se chegou um caracter DLE
volatile BYTE serialPC_DataLen = 0;   //! tamanho da última mensagem recebida
volatile BYTE serialPC_DataCounter = 0;   //! controle de onde se deve escrever no buffer de recepção
volatile BYTE serialPC_Buffer[BUFFER_DATA_LEN] = {0};  //! buffer de recepção

BYTE smsbox::CSMSBox::bQuit = FALSE;

//------------------------------------------------------------------------------------------------------------------
  
CSMSBox::CSMSBox( LPCSTR cPortName )
{
  if ( cPortName != NULL )
  {
    try
    {
      serial.Open( cPortName );
    }
    catch(DWORD& iError)
    {
      throw iError;
    }
  }

  hThreadDispatch = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)CSMSBox::ThreadDispatch, this, 0, NULL );
  if ( hThreadDispatch == NULL )
  {
    throw ::GetLastError();
  }

  hThreadProcessaMensagens = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)CSMSBox::ThreadProcessaMensagens, this, 0, NULL );
  if ( hThreadProcessaMensagens == NULL )
  {
    throw ::GetLastError();
  }

  //hCompletionPort = serial.GetCompletionPort();
  return;
}

//------------------------------------------------------------------------------------------------------------------

BYTE CSMSBox::Open( LPCSTR cPortName )
{
  DWORD dwError;
  if ( serial.IsOpen() == FALSE )
  {
    if ( serial.Open( cPortName ) == 0 )
    {
      return TRUE;
    }

    dwError = ::GetLastError();
    return FALSE;
  }
  return TRUE;
}

//------------------------------------------------------------------------------------------------------------------

BYTE CSMSBox::IsOpen( void )
{
  return serial.IsOpen();
}

//------------------------------------------------------------------------------------------------------------------

void CSMSBox::ProcessaPacotes( BYTE * pData, DWORD dwDataLen )
{
  DWORD dwCounter;

  for( dwCounter = 0; dwCounter < dwDataLen; dwCounter++ )
  {
    if ( serialPC_DataCounter >= sizeof( serialPC_Buffer ) ) 
    {
      serialPC_DataCounter = 0;
      stSerialPC = ST_STX;
      return;
    }

    switch( stSerialPC  ) 
    {
      case ST_STX:
        serialPC_CRC = 0;
        serialPC_DataLen = 0;
        serialPC_DataCounter = 0;

        if ( pData[dwCounter] == STX )
        {
          stSerialPC = ST_ED;
        }
        break;

      case ST_ED:
      case ST_EO:
      case ST_LEN:
      case ST_DATA:
      case ST_LRC:
        
        if ( stSerialPC == ST_DATA ) 
        {

          if ( serialPC_DLE == 1 )
          {
            serialPC_Buffer[serialPC_DataCounter] = pData[dwCounter] ^ DLE_CHAR;
            serialPC_CRC ^= pData[dwCounter];
            serialPC_DataCounter++;

            serialPC_DLE = 0;
          }     
          else{
            if ( (pData[dwCounter] == DLE)||(pData[dwCounter] == ETX)||(pData[dwCounter] == STX) ){
              serialPC_DLE = 1;
            }
            else
            {
              serialPC_Buffer[serialPC_DataCounter] = pData[dwCounter];
              serialPC_CRC ^= pData[dwCounter];
              serialPC_DataCounter++;
            }
          }
        }
        else
        {
          serialPC_Buffer[serialPC_DataCounter] = pData[dwCounter];
          serialPC_CRC ^= pData[dwCounter];
          serialPC_DataCounter++;
        }


        switch( stSerialPC ){ 
          case ST_ED:
            if ( pData[dwCounter] != GetID() ){
              //pacote não é para este SMS Box
              serialPC_CRC = 0;
              serialPC_DataCounter = 0;
              stSerialPC = ST_STX;
              serialPC_ProcessaPkt = FALSE;      
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

        if ( pData[dwCounter] != ETX ){
          serialPC_ProcessaPkt = FALSE;
        }
        
        break;

      default:
        serialPC_CRC = 0;
        serialPC_DataCounter = 0;
        stSerialPC = ST_STX;
        serialPC_ProcessaPkt = FALSE;
    }
  }
}

//------------------------------------------------------------------------------------------------------------------

BYTE CSMSBox::GetID( void )
{
  return bID;
}

//------------------------------------------------------------------------------------------------------------------

void CSMSBox::SetID( BYTE ID )
{
  bID = ID;
  return;
}
//------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSMSBox::ThreadDispatch( LPVOID lpParam )
{
  CSMSBox * box;

  box = (CSMSBox*)lpParam;

  return box->Dispatch();
}

//------------------------------------------------------------------------------------------------------------------

DWORD CSMSBox::Dispatch( void )
{
  BOOL bRet;
  MSG msg; 

  while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
  { 
    TranslateMessage(&msg); 
    DispatchMessage(&msg); 
  }

  bQuit = TRUE;

  return 0;
}

//------------------------------------------------------------------------------------------------------------------

DWORD CSMSBox::ProcessaMensagens( void )
{
  BYTE * pData;
  BYTE bDataLen;

  do
  {
    if ( CSMSBox::bQuit == TRUE ) 
    {
      break;
    }

    if( serialPC_ProcessaPkt == FALSE ) 
    {
      continue;
    }

    bDataLen = serialPC_DataLen;
    pData = new BYTE[ bDataLen ];

    memcpy( (BYTE*)pData, (BYTE*)serialPC_Buffer, serialPC_DataLen );
    serialPC_ProcessaPkt = FALSE;

    switch( *(pData + CMD_FIELD)  )
    {
    case CMD_HELLO:
      break;

    case CMD_ASC:
      break;

    }
  }while( 1 );

  
  return 0;
}

//------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSMSBox::ThreadProcessaMensagens( LPVOID lpParam )
{
  CSMSBox * box;  
  box = (CSMSBox*)lpParam;

  return box->ProcessaMensagens( );
}

//------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSMSBox::ThreadProcessaPacotes( LPVOID lpParam )
{
  CSMSBox * box;
  network::SERIAL_DATA * serialData;
//  DWORD dwNumberOfBytes;

  box = (CSMSBox*)lpParam;

  while( bQuit == FALSE )
  {
    serialData = NULL;
    //if ( GetQueuedCompletionStatus( box->hCompletionPort, &dwNumberOfBytes, (PULONG_PTR)serialData, NULL, 0 ) == FALSE )
    //{
    //  continue;
    //}

    box->ProcessaPacotes( serialData->pData, serialData->dwLen );

    delete serialData->pData;
    delete serialData;
  }

  return 0;
}

//------------------------------------------------------------------------------------------------------------------