/**
 * timer
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
 * - Modifications
 *  -- 08/2009 by rdias: Initial version
 */

#include "timer.h"
#include "funcoes.h"
#include <string.h>

#define NTIMER  32

// increment timer value
#define TICK_VALUE  1

//  TIMER2 POST CALER
#define T2POST_1_1    0
#define T2POST_1_2    1
#define T2POST_1_3    2
#define T2POST_1_4    3
#define T2POST_1_5    4
#define T2POST_1_6    5
#define T2POST_1_7    6
#define T2POST_1_8    7
#define T2POST_1_9    8
#define T2POST_1_10   9
#define T2POST_1_11   10
#define T2POST_1_12   11
#define T2POST_1_13   12
#define T2POST_1_14   13
#define T2POST_1_15   14
#define T2POST_1_16   15

// TIMER2 PRESCALER
#define T2PRE_1_1     0
#define T2PRE_1_4     1
#define T2PRE_1_16    3

//------------ Module local variables ------------

struct Timer{
  BYTE    bTimer;
  DWORD   dwTime;
};

struct Timer timer[NTIMER];
volatile DWORD   dwTickCount;
BYTE    tmInit = FALSE;

//------------------------------------------------

void InitTimer( void ){
  if ( tmInit == TRUE ){
    return;
  }

  // teste
 
  memset( (char*)&timer, TIMER_NULL, sizeof( timer ));
  dwTickCount = 0;
  
  // configures the TIMER 2 module to overflow in TICK_VALUE ms 
  #if TICK_VALUE == 1
    T2CON = (T2POST_1_16 << 3) | T2PRE_1_4;
    PR2 =   (TICK_VALUE*FOSC/4)/(1000L*(T2POST_1_16+1)*(2<<T2PRE_1_4));
  #endif
  
  // configures the interruption
  INTCON  &= ~(BIT7 | BIT6);    // desabilita todas as interupções
  PIE1    |=  BIT1;              // habilita interrupção do timer 2  
  IPR1    |=  BIT1;              // atribui a prioridade da interropção do T2 para alta prioridade.
  PIR1    &= ~BIT1;
  RCON    |=  BIT7;
  INTCON  |= (BIT7 | BIT6);  
  
  T2CON   |= BIT2;              // liga o timer 2
  
  tmInit = TRUE;
  
  return;  
}

//------------------------------------------------

DWORD GetTickCount( void ){
  return dwTickCount;
}

//------------------------------------------------

void IncTickCount( void ){
  dwTickCount += TICK_VALUE;
}

//------------------------------------------------

TIMER_HANDLE GetTimer( DWORD dwTime ){
  BYTE i;
  
  if ( tmInit == FALSE ){
    InitTimer();
  }
  
  for ( i = 1; i < GET_VEC_NUM_MEMBERS(timer);i++ ){
    if ( timer[i].bTimer == TIMER_NULL ){
      timer[i].bTimer     = i;
      timer[i].dwTime     = dwTime + dwTickCount;
      return i;
    }
  }
  
  timer[0].bTimer     = i;
  timer[0].dwTime     = dwTime + dwTickCount;
  return 0;
}

//------------------------------------------------

void ReleaseTimer( TIMER_HANDLE * handle ){

  if ( tmInit == FALSE ){
    InitTimer();
  }
  
  if ( (*handle > GET_VEC_NUM_MEMBERS(timer)) || (*handle == TIMER_NULL) ){
    return;
  }
  
  if ( timer[*handle].bTimer != *handle ){
    return;
  }
  
  memset( (char*)&timer[* handle], TIMER_NULL, sizeof( struct Timer ) );
  *handle   = TIMER_NULL;

  return; 
}

//------------------------------------------------

BYTE IsTimerTimeOut( TIMER_HANDLE handle ){
  
  if ( tmInit == FALSE ){
    InitTimer();
  }
  
  if ( (handle > GET_VEC_NUM_MEMBERS(timer)) || (handle == TIMER_NULL) ){
    return FALSE;
  }

  if ( timer[handle].bTimer != handle ){
    return FALSE;
  }
  
  if ( timer[handle].dwTime < dwTickCount  ) 
    return TRUE;
  
  return FALSE;
}

//------------------------------------------------

BYTE  RestartTimer( TIMER_HANDLE handle, DWORD dwNewTime ){

  if ( (handle > GET_VEC_NUM_MEMBERS(timer)) || (handle == TIMER_NULL) ){
    return FALSE;
  }

  if ( tmInit == FALSE ){
    InitTimer();
  }

  if ( timer[handle].bTimer != handle ){
    return FALSE;
  }

  timer[handle].dwTime     = dwNewTime + dwTickCount;
  
  return TRUE;
}

//------------------------------------------------
