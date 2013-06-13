 ;;
 ; CPU_disableAll_Int
 ;  disable all interrupts sources
 ;  Author: Rafael Dias Menezes
 ;  company: Taioba Corporation
 ;  email: rdmeneze@yahoo.com.br
 ;  Date: sep/2009
 ;
 ;  Copyright (C) 2009  Rafael Dias
 ;
 ;  This program is free software: you can redistribute it and/or modify
 ;  it under the terms of the GNU General Public License as published by
 ;  the Free Software Foundation, either version 3 of the License, or
 ;  (at your option) any later version.
 ;
 ;  This program is distributed in the hope that it will be useful,
 ;  but WITHOUT ANY WARRANTY; without even the implied warranty of
 ;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ;  GNU General Public License for more details.
 ;
 ;  You should have received a copy of the GNU General Public License
 ;  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ;
 ; 
 ; - Modificatios
 ;  -- 09/2009 by rdias: Initial version
 ;/


#include "P18CXXX.INC"

		GLOBAL  CPU_DisableAllInt

CPU_DISABLEALLInt_CODE CODE

CPU_DisableAllInt:
		BANKSEL	INTCON
		;movlw		~0xC0					
		movlw		0x3F
		andwf		INTCON,F			; clean the bits 7 and 6 of intcon. See datasheet
    return

    END