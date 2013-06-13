#ifndef __FLASHEEPROM__
#define __FLASHEEPROM__

#include "defs.h"


#define AT45DBXX

//! define the total capacity of serial memory
#define FLASH_CAPACITY  ((4L*1024L*1024L)/8L)    // 4 MBit


/**
 * \brief Inicializa o acesso com a serial EEPROM
 */
void FlashInit( void );

/**
 *  \brief  Realiza a leitura de um buffer de dados da mem�ria externa
 *  \param  bufOut  ponteiro para um buffer de sa�da
 *  \param  addr    endere�o a ser lido da mem�ria
 *  \param  len     quantidade de bytes a serem lidos
 *  \return Sucesso (TRUE)  ou erro (FALSE)
 */
BYTE Flash_Read( BYTE * bufOut, DWORD addr, BYTE len );

/**
 *  \brief  Realiza a escrita na mem�ria externa
 *  \param  bufOut  ponteiro para um buffer de entrada
 *  \param  addr    endere�o de destino na mem�ria externa
 *  \param  len     quantidade de bytes escritos
 */
BYTE Flash_Write( BYTE * bufIn, DWORD addr, BYTE len );

#endif
