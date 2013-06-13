#ifndef __PROC_SIM340CZ__
#define __PROC_SIM340CZ__

#include "defs.h"

/**
 * @ brief 	Envia um comando ao modem GSM
 * @ param	cCmd buffer a ser enviado
 * @ bLen 	quantidade de bytes a serem transmitidos
 * @ return	estado de envio do comando 
 */
BYTE Sim340CZ_SendCmd( char * cCmd, BYTE bLen );

/**
 * @ brief	Realiza o processamento de uma mensagem recebida pelo modem
 */
BYTE Sim340CZ_ProcResponse( char * cCmd, BYTE bLen );


#endif  //~ __PROC_SIM340CZ__
