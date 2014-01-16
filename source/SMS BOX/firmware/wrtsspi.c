#include <p18cxxx.h>
#include "sw_spi.h"

/********************************************************************
*       Function Name:  SWSPIWrite                                  *
*       Parameters:     data: data to transmit                      *
*       Description:    This routine sets the CS pin high.          *
********************************************************************/
void SWSPIWrite( char output ){
	BYTE i; 

#if defined(MODE0)    // Mode 0
	SW_DOUT_PIN = 0;
  
	for (i = 0; i < 8; i++) { 
		if (output & 0x80) { 
      SW_DOUT_PIN = 1;
		} 
		else { 
			SW_DOUT_PIN = 0; 
		} 

		output <<= 1; 
    
    SW_SCK_PIN = 1;
    SW_SCK_PIN = 0;
	} 
	SW_DOUT_PIN = 0;	

#endif
  return;
}

