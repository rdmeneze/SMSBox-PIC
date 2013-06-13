/**
 *  modemGSM.h
 *  Modulo para controle do modem GSM
 *  
 */
#ifndef __MODEMGSM__
#define __MODEMGSM__

#define NCARD       16
#define CARD_OFFSET 0

#include "defs.h"
#include "serial.h"

#define _MODEL_GSM SIMHD

//---------- Modem control return values ----------
#define GSM_OK            0
#define GSM_IDLE          1
#define GSM_MODEM_ERROR   2
#define GSM_MODEM_NTENPT  3
#define GSM_MODEM_TIMEOUT 4
//-------------------------------------------------

//---------- Modem operation status ----------
#define GSM_ST_IDLE         0
#define GSM_ST_READY        1
#define GSM_ST_ERROR        2
#define GSM_ST_BUSY         3
//--------------------------------------------

//#define _BAUDRATE_AUTOBAUD

//#define USE_SIM_PRESENCE

/**
 * \brief  Initialize modem communication
 */
void ModemGSM_Init( void );

/**
 * \brief Do the verification  Realiza a verificação do estado de ativação do modem GSM
 */
BYTE ModemGSM_IsOn( void );

/**
 * \brief Retorna se o modem está pronto para operação
 */
BYTE ModemGSM_IsReady( void );

/**
 * \brief Liga o modem. Função não bloqueante. 
 * \return 
 */
BYTE ModemGSM_OnNoBlk( void ); 

/**
 * \brief Desliga o modem. Função não bloqueante. 
 */
BYTE ModemGSM_OffNoBlk( void ); 

/**
 * \brief Liga o Modem GSM
 */
BYTE ModemGSM_On( void );

/**
 * \brief Desliga o Modem GSM
 */
BYTE ModemGSM_Off( void );

/**
 *  \brrief Reinicia o modem GSM
 */
BYTE ModemGSM_Restart( void );

/**
 *  \brief Realiza a troca do cartão SIM
 */
BYTE ModemGSM_ChangeCard( BYTE ID );

/**
 *  \brief Envia um comando AT ao modem GSM
 */
BYTE ModemGSM_SendATCMD( BYTE * buffer, BYTE len );

/**
 * \brief trata da recepção dos dados do modem 
 * \param bDado dado recebido da porta serial 
 */
void ModemGSM_ProcessaMensagens( BYTE bData );

/**
 *  \brief Verifica se houve timeout na recepção de dados do modem e envia-os para o PC
 */
void ModemGSM_CheckMSG( void );

/**
 * \brief  Reinicia todos os transistores de comutação dos SIMs para o estado cortado 
 */
void ModemGSM_ResetStateSIMCARD( void );

/**
 * \brief Altera o estado do pino SIM_PRESENCE
 * \param estado a ser alterado. 
 * \return estado do pino
 */
BYTE ModemGSM_Change_State_SIM_PRESENCE( BYTE newValue );

/**
 * \brief retorna o ID do SIM Card corrente
 * \return SIM Card ID
 */
BYTE ModemGSM_GetActiveSIMCard( void );

/**
 *  \brief Realiza a verificação do estado de operação do modem GSM
 */
void CheckGSM_ONOffState( void );

/**
 * \brief Altera o valor do timer de verifiação se o modem está ativo pronto
 */
void ModemGSM_ChangeCheckONOFFTimer( DWORD dwTime );

#endif // ~__MODEMGSM__
