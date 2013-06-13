#ifndef __LOG__
#define __LOG__

/**
 * log.h
 *  log engine library especification
 *  Author: Rafael Dias Menezes
 *  company: Taioba Corporation
 *  email: rdmeneze@yahoo.com.br
 *  Date: dez/2009
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
 *  -- 23/12/2009 by rdias: Initial version
 */

#include "defs.h"

//---- library defines ----
//! define the possible log types.
#define LOG_ALL       0
#define LOG_USR       1
#define LOG_SW        2
#define LOG_HW        3

//! define the possible events
#define EVT_SW        0
#define EVT_HW        1
#define EVT_USR       2

//! define the software code events
#define EVT_SW_MODEM      0
#define EVT_SW_HELLO      1
#define EVT_SW_ASC        2
#define EVT_SW_SONDA      3
#define EVT_SW_STATUS     4
#define EVT_SW_VERSION    5
#define EVT_SW_LOG_LEVEL  6
#define EVT_SW_DEV_ST     7
#define EVT_SW_POWERDOWN  8
#define EVT_SW_BYE        9

//! define hardware events
#define EVT_HW_MODEM    0
#define EVT_HW_FLASH    1
#define EVT_HW_E2PROM   2
#define EVT_HW_COM_MODEM  3
#define EVT_HW_RST      4

//! local usage defines
#define LOG_BUF_LEN   127
#define N_LOG_EVNT    512L

//-----------------------

struct LogBuffer {
  BYTE bCode;                       //! log type
  WORD wStamp;
  BYTE bLen;
  BYTE bBuffer[ LOG_BUF_LEN ];   //! buffer to data saved in buffer
};

//-------------------------

/**
 *  \brief Init the Log engine
 */
void LogInit( void );

/** 
 *  \brief Set the log level
 */
void LogSetLevel( BYTE bLevel );

/**
 *  \brief Log application messages
 *  \param bCode type of log
 *  \param bMsg  pointer to log buffer
 *  \param len  length of message
 */
void Log( BYTE bCode, BYTE * bMsg, BYTE len );

/**
 *  \brief Log the user messages
 *  \param cMsg User Message
 *  \param len  length of message
 */
//void LogUsrMsg( char * cMsg, size_t len );

/**
 * \brief Log the hardware messages
 * \param bCode     error code
 * \param bSubCode error code
 */
//void LogHW( BYTE bCode, BYTE bSubCode );

/**
 *  \brief  Log the software messages
 *  \param bCode software log code
 *  \param bSubCode error code
 */
//void LogSW( BYTE bCode, BYTE bSubCode );

/**
 *  \brief  get the log level
 *  \return log level
 */
BYTE GetLogLevel( void );

/**
 * \brief Get the log structure indexed LogPointerEnd
 * \param pLogPtr pointer to a byte buffer 
 */
BYTE GetLog( far void * LogPtr );

#endif // __LOG__
