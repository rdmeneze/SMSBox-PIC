#ifndef __E2PROM__
#define __E2PROM__

/**
 *  e2prom.h
 *  e2prom access functions
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
 * - Modifications
 *  -- 23/12/2009 by rdias: Initial version
 */

#include "defs.h"
#include "e2prom_loc.h"

/**
 *  \brief read a buffer from e2prom memory
 *  \param dest destiny buffer
 *  \param addr address to read
 *  \param size size of the buffer to read
 *  \return status of operation TRUE = ok, else nok 
 */
BYTE e2prom_read( BYTE * dest, WORD addr, size_t size );

/**
 *  \brief write a buffer to e2prom memory
 *  \param src source buffer
 *  \param addr address to write
 *  \param size size of the buffer to write
 *  \return status of operation TRUE = ok, else nok 
 */
BYTE e2prom_write( BYTE * src, WORD addr, size_t size );

#endif
