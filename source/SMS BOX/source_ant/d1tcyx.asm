#include "p18cxxx.inc"

D1TCYXCODE CODE

    GLOBAL  Delay1TCYx
Delay1TCYx:
    movlw   0xff
    movf    PLUSW1,0
    dcfsnz  WREG,1
    return

D1x
    nop
    decfsz  WREG,1
    bra     $-2
    return


    END
    
