 ;;
 ; d4tcyx
 ;  do a delay of 4cc
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


#include "p18cxxx.inc"

    GLOBAL  Delay4TCYx


D1TCYXCODE CODE

Delay4TCYx:
    movlw   0xff				; 1
    movf    PLUSW1,W		; 1 
D4x											; restam WREG - 4 ciclos
		nop									; 1
    decfsz  WREG,F     	; 1
    bra     $-4        	; 2
    return


    END
    
