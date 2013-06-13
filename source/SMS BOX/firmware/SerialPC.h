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
 * 
 * - Modifications
 *  -- 09/2009 by rdias: Initial version
 *  -- 10/2009 by rdias: Timer overflow between host messages
 *  -- 15/12/2009 by rdias : implementation of version and sonda packages
 */


#ifndef __SERIALPC__
#define __SERIALPC__

#include "defs.h"
#include "processor.h"

#define ED_FIELD    0
#define EO_FIELD    1
#define LEN_FIELD   2
#define DATA_FIELD  3
#define CMD_FIELD   3
#define CMD_PARAM   (CMD_FIELD+1)

#define SERVER_ID   0x00

//#define USE_SONDA
//#define _USE_SERIALPC_TIMEOUT

/**
 *  \brief Performs the processing of the packages received from host PC
 *  \param bData byte received in the serial line
 */
void ProcessaProtocolo(BYTE bData);

/**
 *  \brief Initialize the serial connection with the host PC
 */
void SerialPCInit( void );

/**
 *  ProcessaPacotes
 *  \brief Perform the processing of packages received from host PC
 */

void ProcessaPacotes( void );

/**
 *  \brief Returns the controller ID
 *  \return ID do controlador
 */
BYTE GetID ( void );

/**
 *  \brief Get the actual state of the serial connection
 *  \return TRUE connected
 */
BYTE IsConnected( void );

/**
 * \brief Send modem command received from GSM Modem to PC
 * \param buffer data to send
 * \param len length os stream to send
 */
void EnviaCMD_MODEM( BYTE * buffer, int len );


#endif
