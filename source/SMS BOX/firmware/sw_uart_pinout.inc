#ifndef _SW_UART_PINOUT_
#define _SW_UART_PINOUT_

#define USE_INT0  1

SWTXD           equ     LATC           ; Transmit pin port and pin
SWTXDpin        equ     1
TRIS_SWTXD      equ     TRISC           ; Transmit pin tris and pin
SWRXD           equ     PORTB           ; Receive pin port and pin
SWRXDpin        equ     0
TRIS_SWRXD      equ     TRISB           ; Receive pin tris and pin

#endif