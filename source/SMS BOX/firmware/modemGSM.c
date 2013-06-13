/**
 * modemGSM
 *  Performs the control of communication protocol between the host computer and the modem GSM.
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
 *  -- 02/02/2010 by rdias : log schema
 */

#include "modemGSM.h"
#include "delay.h"
#include "ports.h"
#include "sw_uart.h"
#include "cmd_serialPC.h"
#include "timer.h"
#include "SerialPC.h"
#include "status.h"
#include <string.h>
#include <stdio.h>
#include "processor.h"
#include "device.h"
#include "funcoes.h"
#include "simcardcontrol.h"

//------------------------------------
#ifndef MODEM_BAUDRATE
  #define MODEM_BAUDRATE  19200L
#endif

//#define BUFFER_GSM_LEN (255L)
#define BUFFER_GSM_LEN (512L)
//#define BUFFER_GSM_LEN (1024L)

#define DELAY_POWER_ON  2000
#define DELAY_POWER_OFF 10000
#define CHAR_DELAY      16

#define MODEMGSM_TIMEROVF  (WORD)((CHAR_DELAY*(11*1000L)/MODEM_BAUDRATE) + 0.5)   // tempo para envio de 16 caracteres

#if (MODEM_BAUDRATE == 300L)
  #define MODEM_BAUD      BR_300 
#elif (MODEM_BAUDRATE == 1200L)
  #define MODEM_BAUD      BR_1200
#elif (MODEM_BAUDRATE == 2400L)
  #define MODEM_BAUD      BR_2400 
#elif (MODEM_BAUDRATE == 4800L)
  #define MODEM_BAUD      BR_4800
#elif (MODEM_BAUDRATE == 9600L)
  #define MODEM_BAUD      BR_9600
#elif (MODEM_BAUDRATE == 19200L)
  #define MODEM_BAUD      BR_19200
#elif (MODEM_BAUDRATE == 38400L)
  #define MODEM_BAUD      BR_38400
#elif (MODEM_BAUDRATE == 57600L)
  #define MODEM_BAUD      BR_57600
#elif (MODEM_BAUDRATE == 115200L)
  #define MODEM_BAUD      BR_115200
#else
  #error "MODEM_BAUDRATE don't defined"
#endif

#define TIMEOUT_CHECK_ONOFF 500L
#define TIMEOUT_START_MODEM 5000L

//------------------------------------
//BYTE ModemGSM_Varzea2[5] = {0xFF};                  

#pragma udata GSM_BUFFER
volatile BYTE ModemGSM_Buffer[BUFFER_GSM_LEN];     //! buffer de recepção de dados do modem
#pragma udata

//BYTE ModemGSM_Varzea[32] = {0xFF};                  //! área de varzea. Estou tendo problemas de vazamento de memória.
BYTE ModemGSM_Ready;                                //! indica se o modem está pronto para operação. 
//volatile BYTE ModemGSM_DataCounter;                 //! variável interna para controle dos caracteres recebidos do modem. 
volatile int ModemGSM_DataCounter;                  //! variável interna para controle dos caracteres recebidos do modem. 
TIMER_HANDLE ModemGSM_TimerHandle;                  //! handle para timer que controla o tempo para considerar que o pacote 
                                                    //!   recebido do modem é um pacote pronto a ser enviado para o Host.
TIMER_HANDLE timerCheckONOFF = TIMER_NULL;


extern CDevice dev[NDEV];                           //! array de dispositivos. Declarado em device.c
                                                    //! está aqui para atualizar o estado do dispositivo DEV_GSM_PWR_KEY

//------------------------------------

#if _MODEL_GSM==SIMHD
  #define GSM_PWRKEY_ON() ( GSM_PWRKEY = 0 )
  #define GSM_PWRKEY_OFF() ( GSM_PWRKEY = 1 )
#else
  #error "_MODEL_GSM indefined"  
#endif

//------------------------------------

void  ModemGSM_InitGPIO( void );

//------------------------------------

void ModemGSM_Init( void ){
  
  char cBuffer[32]; 
  BYTE i;
  INT iCounter;

  // inicializa a conexão serial com o Modem
  InitSerial( 0, MODEM_BAUD, ST_1, PR_NONE, ModemGSM_ProcessaMensagens );
  //cdantas - alterei a função de UART para utilizar o HardWare

  //memset( (char*)ModemGSM_Varzea, 0, sizeof( ModemGSM_Varzea ));
  //for ( i = 0; i < sizeof( ModemGSM_Varzea ); i++ ){
  //  ModemGSM_Varzea[i] = (i % 2)? 0x55 : 0xAA;
  //}

  //for ( i = 0; i < sizeof( ModemGSM_Varzea2 ); i++ ){
  //  ModemGSM_Varzea2[i] = (i % 2)? 0x55 : 0xAA;
  //}

  for( ModemGSM_DataCounter = 0; ModemGSM_DataCounter < /*sizeof ( ModemGSM_Buffer )*/BUFFER_GSM_LEN; ModemGSM_DataCounter++ ){
    ModemGSM_Buffer[ModemGSM_DataCounter] = (ModemGSM_DataCounter % 2) ? 0xAA: 0x55;
  }

  // inicializa os pinos de conexão com os SIMs cards
  ModemGSM_InitGPIO();

  ModemGSM_ResetStateSIMCARD();

  ModemGSM_Change_State_SIM_PRESENCE( 0 );

  ModemGSM_Ready = FALSE;
  
  ModemGSM_DataCounter = 0;

  ModemGSM_TimerHandle = GetTimer( MODEMGSM_TIMEROVF );

 if ( !ModemGSM_IsOn() ){

#ifdef _BAUDRATE_AUTOBAUD      
    if ( ModemGSM_On() == TRUE ){
      // wait a delay before send a first command to modem. 
      delay( TIMEOUT_START_MODEM );
      
      // Send a .AT. string to modem to detect the baudrate
      strcpypgm2ram( (char*)cBuffer, (const MEM_MODEL rom char*)".AT." );
      ModemGSM_SendATCMD( (BYTE*)cBuffer, strlen( cBuffer ) );
      
      delay( TIMEOUT_START_MODEM ); 
      strcpypgm2ram( (char*)cBuffer, (const MEM_MODEL rom char*)"AT+IPR=?\r\n" );
      ModemGSM_SendATCMD( (BYTE*)cBuffer, strlen( cBuffer ) );
    }    
#else
    ModemGSM_On();
#endif
  }
  else{
    ModemGSM_Ready = TRUE;
  }

  if ( ModemGSM_Ready == TRUE ){
    //Dev_ChangeState( DEV_GSM_PWR_KEY, ON );
    
    SetStatus( ST_MODEM_RDY );

    for ( i = 0 ; i < GET_VEC_NUM_MEMBERS(dev); i++ ){
      if ( dev[i].ID == DEV_GSM_PWR_KEY ){
        dev[i].bState = ON;
        dev[i].bNextState = ON;
      }
    }
    
  }

  timerCheckONOFF = GetTimer( TIMEOUT_START_MODEM );

  return;
}

//------------------------------------

BYTE ModemGSM_On( void ){
  
  if ( GSM_STATUS == 1 )
    return TRUE;
  
  GSM_PWRKEY_OFF();
  delay( DELAY_POWER_ON );  // espera tempo de resposta 

  if( GSM_STATUS == 0 ){
    GSM_PWRKEY_ON();
    delay( 100 );
    GSM_PWRKEY_OFF();
    delay( DELAY_POWER_ON );  // espera tempo de resposta 
  }

  if( GSM_STATUS == 0 ){
    return FALSE;
  }

  GSM_PWRKEY_ON();
  
  return TRUE;
}

//------------------------------------

BYTE ModemGSM_Off( void ){
  BYTE bTimer;
  bTimer = GetTimer( DELAY_POWER_OFF );

  if ( GSM_STATUS == 1 ){
    GSM_PWRKEY_OFF();
    delay( 2000 );
    GSM_PWRKEY_ON();
  
    RestartTimer( bTimer, DELAY_POWER_OFF );

    do{
    } while( (IsTimerTimeOut( bTimer ) == FALSE) && (GSM_STATUS == 1));
    ModemGSM_ResetStateSIMCARD();

  }
  ReleaseTimer( &bTimer );
  return TRUE;
}

//------------------------------------

BYTE ModemGSM_IsOn( void ){
  return (GSM_STATUS == 1);
}

//------------------------------------

BYTE ModemGSM_Restart( void )
{
  if ( ModemGSM_Off() )
  {
      return ModemGSM_On( );
  }
  return FALSE;
}

//------------------------------------

/*
BYTE ModemGSM_ChangeCard( BYTE ID )
{
  return SetSimCard( ID );
}
*/

//------------------------------------

/*void ModemGSM_ResetStateSIMCARD( void )
{
  ResetSIMCARD( );
}
*/

//------------------------------------

void ModemGSM_InitGPIO( void ){
  
  GSM_PWRKEY_ON();
  GSM_PWRKEY_DIR  =  DIR_OUT;
  GSM_STATUS_DIR  =  DIR_IN;
  
#ifdef USE_SIM_PRESENCE
  GSM_AC_SIM_PRES_DIR = DIR_OUT;
#endif
  
  InitSimCards( );
}

//------------------------------------

BYTE ModemGSM_SendATCMD( BYTE * buffer, BYTE len ){
  
  if ( GSM_STATUS == 0  ) {
    return FALSE;
  }
  
  //WriteTXBuffer( buffer, len );
  
  for( ; len ; len-- ){
    SerialPutc( *buffer );   
    buffer++;
  }
  return TRUE;
}

//------------------------------------

void ModemGSM_ProcessaMensagens( BYTE bData ){
  RestartTimer( ModemGSM_TimerHandle, MODEMGSM_TIMEROVF );

  if ( ModemGSM_DataCounter >= /*sizeof( ModemGSM_Buffer )*/ BUFFER_GSM_LEN - 1 ){
    ModemGSM_DataCounter = 0;
  }  

  ModemGSM_Buffer[ModemGSM_DataCounter] = bData;
  ModemGSM_DataCounter++;
  
  return;
}

//------------------------------------

void ModemGSM_CheckMSG( void ){
  char * pChar = NULL;
  BYTE i;

  //static const char strPowerDown[] = "\r\nNORMAL POWER DOWN\r\n";
  //static const char strPowerLowDown[] = "\r\nPOWER LOW DOWN\r\n";
  //static const char strPowerDownLowTemp[] = "\r\n+CMTE:-2\r\n";
  //static const char strPowerDownHighTemp[] = "\r\n+CMTE: 2\r\n";
  
  if (ModemGSM_DataCounter) {
    if ( (ModemGSM_DataCounter >= /*sizeof( ModemGSM_Buffer )*/ BUFFER_GSM_LEN - 1) || (IsTimerTimeOut( ModemGSM_TimerHandle ) == TRUE) ){

#ifdef _BAUDRATE_AUTOBAUD

      if ( ModemGSM_Ready == FALSE ){
        // busca por RDY no buffer de recepção
        pChar = strstrrampgm( (const char*)ModemGSM_Buffer, (const MEM_MODEL rom char*)"+IPR" );
        if ( pChar != NULL ){
          ModemGSM_Ready = TRUE;
          SetStatus( ST_MODEM_RDY );

          for ( i = 0 ; i < GET_VEC_NUM_MEMBERS(dev); i++ ){
            if ( dev[i].ID == DEV_GSM_PWR_KEY ){
              dev[i].bState = ON;
              dev[i].bNextState = ON;
            }
          }
        }
      }
      else{
        //ModemGSM_Buffer[ModemGSM_DataCounter] = 0;
        // verify the modem power down cause
        //if ( (strncmp( (const char*)ModemGSM_Buffer, strPowerDown,         ModemGSM_DataCounter ) == 0) ||
        //     (strncmp( (const char*)ModemGSM_Buffer, strPowerLowDown,      ModemGSM_DataCounter ) == 0) || 
        //     (strncmp( (const char*)ModemGSM_Buffer, strPowerDownLowTemp,  ModemGSM_DataCounter ) == 0) || 
        //     (strncmp( (const char*)ModemGSM_Buffer, strPowerDownHighTemp, ModemGSM_DataCounter ) == 0)  )
        //{
        //  for ( i = 0 ; i < GET_VEC_NUM_MEMBERS(dev); i++ ){
        //    if ( dev[i].ID == DEV_GSM_PWR_KEY ){
        //      dev[i].bState = OFF;
        //      dev[i].bNextState = OFF;
        //    }
        //  }
        //  ModemGSM_Ready = FALSE;
        //  CleanStatus( ST_MODEM_RDY );      
        //}

        EnviaCMD_MODEM((BYTE*)ModemGSM_Buffer, ModemGSM_DataCounter );
      }
#else
      if ( ModemGSM_Ready == FALSE ){
        // busca por RDY no buffer de recepção
        pChar = strstrrampgm( (const char*)ModemGSM_Buffer, (const MEM_MODEL rom char*)"RDY" );
        if ( pChar != NULL ){
          ModemGSM_Ready = TRUE;

          for ( i = 0 ; i < GET_VEC_NUM_MEMBERS(dev); i++ ){
            if ( dev[i].ID == DEV_GSM_PWR_KEY ){
              dev[i].bState = ON;
              dev[i].bNextState = ON;
            }
          }
        }
      }
      else{
        EnviaCMD_MODEM( ModemGSM_Buffer, ModemGSM_DataCounter );
      }
#endif
      ModemGSM_DataCounter = 0;
    }
  }
  return;
}

//------------------------------------

BYTE ModemGSM_IsReady( void ){
  return (ModemGSM_Ready == TRUE);
}

//------------------------------------

BYTE ModemGSM_Change_State_SIM_PRESENCE( BYTE newValue ){
  
#ifdef USE_SIM_PRESENCE
  if ( newValue == 0x00 ){
    GSM_AC_SIM_PRES = 0;    
  }
  else{
    GSM_AC_SIM_PRES = 1;
  }
  return (newValue != 0x00);
#else
  return TRUE;
#endif

}

//------------------------------------

BYTE ModemGSM_OnNoBlk( void ){

#ifndef _BAUDRATE_AUTOBAUD
  return TRUE;
#else

  char cBuffer[16];
  static BYTE contTent = 0;
  static BYTE bState = 0;
  static TIMER_HANDLE bTimer = TIMER_NULL;

  if ( contTent > 4 ) {
    contTent = 0;
    return GSM_MODEM_NTENPT;    
  }

  switch( bState ){
    case 0:
      if ( bTimer == TIMER_NULL ){
        bTimer = GetTimer( DELAY_POWER_ON );
      }

      GSM_PWRKEY_OFF();     // coloca o PWR_KEY para nível zero. 
      bState = 1;
      return GSM_IDLE;

    case 1 :
     if ( IsTimerTimeOut( bTimer ) == TRUE ) {
        // ocorreu o timeout da operação com o modem
        // deve verificar o valor de GSM_STATUS
        GSM_PWRKEY_ON();
        contTent++;

        if ( GSM_STATUS == 0 ){
          // não foi possível ligar o modem.
          delay( 10 );
          GSM_PWRKEY_OFF();
          bState = 2;
          bTimer = GetTimer( DELAY_POWER_ON );
          return GSM_IDLE;
        }
        else{
          contTent = 0;
          bState = 3;
          RestartTimer( bTimer, TIMEOUT_START_MODEM );
          return GSM_IDLE;
        }
     }

    case 2:
      if ( IsTimerTimeOut( bTimer ) == TRUE ){ 
        bState = 1; 
      }
      return GSM_IDLE;


    case 3:
      
      if ( IsTimerTimeOut( bTimer ) == TRUE ){
        
        // Send a .AT. string to modem to detect the baudrate
        strcpypgm2ram( (char*)cBuffer, (const MEM_MODEL rom char*)".AT." );
        ModemGSM_SendATCMD( (BYTE*)cBuffer, strlen( cBuffer ) );   

        RestartTimer( bTimer, TIMEOUT_START_MODEM );
        bState = 4;
      }
      return GSM_IDLE;
  
    case 4:
      if ( IsTimerTimeOut( bTimer ) == TRUE ){
        
        // Send a .AT. string to modem to detect the baudrate
        strcpypgm2ram( (char*)cBuffer, (const MEM_MODEL rom char*)"AT+IPR=?\r\n" );
        ModemGSM_SendATCMD( (BYTE*)cBuffer, strlen( cBuffer ) );

        bState = 5;
        RestartTimer( bTimer, 10000 );        
      }
      return GSM_IDLE;

    case 5:
      
      if ( (IsTimerTimeOut( bTimer ) == TRUE) || ( ModemGSM_IsReady( ) == TRUE ) ){
        ReleaseTimer( &bTimer );
        bState = 0;

        if ( ModemGSM_IsReady( ) == TRUE ) {
          SetStatus( ST_MODEM_RDY );
          return GSM_OK;
        }        
        else{
          return GSM_MODEM_TIMEOUT;      
        }
      }
      return GSM_IDLE;

    default:
      return GSM_MODEM_ERROR;
  }
#endif
}

//------------------------------------

BYTE ModemGSM_OffNoBlk( void ){
  BYTE bTmp;
  static BYTE           bState = 0;
  static TIMER_HANDLE   bTimer = TIMER_NULL;
#ifndef _BAUDRATE_AUTOBAUD
  return TRUE;
#else

  //! há um erro na atualização da variável bState_OffNoBlk. Após o módulo retornar GSM_OK


  switch( bState ){
    case 0:
      //!
      //! desliga o PowerKey
      //!
      if ( bTimer != TIMER_NULL ){
        ReleaseTimer( &bTimer );
      }
      
      if ( bTimer == TIMER_NULL ){
        bTimer = GetTimer( 2000 /*DELAY_POWER_OFF*/ );
      }

      bState = 1;
      GSM_PWRKEY_OFF();
      
      return GSM_IDLE;

    case 1:
      // espera tempo de desligamento do powerkey
      if ( IsTimerTimeOut( bTimer ) == TRUE ){
        RestartTimer( bTimer, DELAY_POWER_OFF );
        GSM_PWRKEY_ON();
        bState = 100;
      }
      return GSM_IDLE;

      case 100:
        //!
        //! Espera o tempo para GSM_STATUS (VDD_EXT) ir para o nível lógico 0
        //!
        bTmp = GSM_STATUS;
        if ( (IsTimerTimeOut( bTimer ) == TRUE) || (GSM_STATUS == 0) ) {
          if ( GSM_STATUS == 0 ) {
            bState = 0;
            ReleaseTimer( &bTimer );
            //teste
            ModemGSM_Ready = FALSE;
            CleanStatus( ST_MODEM_RDY );
            //teste
            return GSM_OK;
          }
          //else
          //{
          //  // reinicia o processo de desligar o modem
          //  bState_OffNoBlk = 0; 
          //}
        }
        return GSM_IDLE;


      default:
        if ( bTimer != TIMER_NULL ){
          bState = 0;
          ReleaseTimer( &bTimer );
        }
        return GSM_MODEM_ERROR;
  }
  return GSM_IDLE;
#endif
}

//------------------------------------

void CheckGSM_ONOffState( void ){

  static BYTE bState_ONOffState = 0;
  BYTE bDevState = 0xFF;

//  if ( timer == TIMER_NULL ){
//    timer = GetTimer( TIMEOUT_START_MODEM );
//  }

  switch( bState_ONOffState ) {
    case 0:
      if ( IsTimerTimeOut( timerCheckONOFF ) == TRUE ){       
        if ( ModemGSM_IsReady() == FALSE ){
          bState_ONOffState = 1;
          return;
        }
        RestartTimer( timerCheckONOFF, TIMEOUT_CHECK_ONOFF );
      }
      return;

    case 1:
      if ( ModemGSM_IsReady() == FALSE ) {
        if( ModemGSM_IsOn() == TRUE ){
          switch( ModemGSM_OffNoBlk() ){
            case GSM_OK            :
              //Dev_ChangeState( DEV_GSM_PWR_KEY, OFF );
              bState_ONOffState = 2;
              return;

            case GSM_IDLE          :
              return;

            case GSM_MODEM_ERROR   :
            case GSM_MODEM_NTENPT  :
            case GSM_MODEM_TIMEOUT :
              bState_ONOffState = 0;
              RestartTimer( timerCheckONOFF, TIMEOUT_CHECK_ONOFF );
              return;
          }
        }
      }
      else{
        bState_ONOffState = 0;
        RestartTimer( timerCheckONOFF, TIMEOUT_CHECK_ONOFF );
        return;
      }

    case 2:
      if ( ModemGSM_IsReady() == FALSE ){
        switch( ModemGSM_OnNoBlk() ){
            case GSM_OK            :
              bState_ONOffState = 0;
              ReleaseTimer( &timerCheckONOFF );
              //Dev_ChangeState( DEV_GSM_PWR_KEY, ON );
              return;

            case GSM_IDLE          :
              return;

            case GSM_MODEM_ERROR   :
            case GSM_MODEM_NTENPT  :
            case GSM_MODEM_TIMEOUT :
              bState_ONOffState = 0;
              RestartTimer( timerCheckONOFF, TIMEOUT_CHECK_ONOFF );
              return;
        }    
      }
      else{
        bState_ONOffState = 0;
        RestartTimer( timerCheckONOFF, TIMEOUT_CHECK_ONOFF );
        return;
      }
      return; 
  }
  return;
}

//------------------------------------

void ModemGSM_ChangeCheckONOFFTimer( DWORD dwTime )
{
  RestartTimer( timerCheckONOFF, dwTime );
  return;
}

//------------------------------------
