#include <P18CXXX.INC>
#include "sw_uart_pinout.inc"

        EXTERN  DelayRXBitUART
        EXTERN  DelayRXHalfBitUART
        EXTERN  DelayTXBitUART
        EXTERN  uartdata
        EXTERN  BitCount

UARTCODE        CODE
;********************************************************************
;*      Function Name:  OpenUART                                    *
;*      Return Value:   void                                        *
;*      Parameters:     void                                        *
;*      Description:    This routine configures the I/O pins for    *
;*                      software UART.                              *
;********************************************************************
        GLOBAL  OpenUART
OpenUART
	; rdias - configura a interrupção por borda de descida no pino RB0
	;
#if USE_INT0 == 1
	BANKSEL	INTCON
	movlw		b'00111111'
	andwf	  INTCON,F
	
	BANKSEL ADCON1
	movlw   0x0F
	movwf   ADCON1
	
	BANKSEL INTCON2
	bcf     INTCON2,INTEDG0 ; sensível a borda de descida no pino INT0  
	
	BANKSEL INTCON
	bsf     INTCON, INT0IE  ; habilita a interrupção por borda no pino RB0
	
	BANKSEL	INTCON
	movlw		b'11000000'
	iorwf	  INTCON,F
#endif   
	
	banksel SWTXD
	bcf             TRIS_SWTXD,SWTXDpin     ; Make TXD an output
	bsf             SWTXD,SWTXDpin          ; Make TXD high
	banksel SWRXD
	bsf             TRIS_SWRXD,SWRXDpin     ; Make RXD an input
	bsf             SWRXD,SWRXDpin          ; Make RXD high
	return

        
	END
