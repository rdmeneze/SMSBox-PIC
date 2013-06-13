/**
 * AT45DBxx
 *  Performs the control of communication between the controller and the serial flash memory
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
 * 
 * - Modificatios
 *  -- 09/2009 by rdias: Initial version
 */

#ifndef __AT45DBXX__
#define __AT45DBXX__

#include "defs.h"
#include "processor.h"

#include "ports.h"

#define AT_45_PAGE_SIZE 264L
//#define AT_45_PAGE_SIZE 256L

/**
 *  \brief  Inicializa a interface com a memória serial AT45DBXX
 */
void AT45DBXX_Init( void );

/**
 *  \brief  Realiza a leitura de um buffer de dados da memória externa
 *  \param  bufOut  ponteiro para um buffer de saída
 *  \param  addr    endereço a ser lido da memória
 *  \param  len     quantidade de bytes a serem lidos
 *  \return Sucesso (TRUE)  ou erro (FALSE)
 */
#if AT_45_PAGE_SIZE == 256L
  BYTE AT45DBXX_Read( BYTE * bufOut, DWORD addr, BYTE len );
#elif AT_45_PAGE_SIZE == 264L
  BYTE AT45DBXX_Read( BYTE * bufOut, DWORD addr, WORD len );
#endif

/**
 *  \brief  Realiza a escrita na memória externa
 *  \param  bufOut  ponteiro para um buffer de entrada
 *  \param  addr    endereço de destino na memória externa
 *  \param  len     quantidade de bytes a serem escritos
 */
#if AT_45_PAGE_SIZE == 256L
  BYTE AT45DBXX_Write( BYTE * bufIn, DWORD addr, BYTE len );
#elif AT_45_PAGE_SIZE == 264L
  BYTE AT45DBXX_Write( BYTE * bufIn, DWORD addr, WORD len );
#endif

#endif

