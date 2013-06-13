#include "sw_spi.h"

BYTE ReadSWSPI( void ){

	BYTE i;
  BYTE dat = 0; 

	for (i = 0; i < 8; i++) { 
		dat <<= 1; 
		SW_SCK_PIN = 1; 

    if (SW_DIN_PIN == 1) {	 
			dat |= 1;	 
		}   

		SW_SCK_PIN = 0; 
	} 
	SW_DIN_PIN = 0; 
	return dat; 
}

