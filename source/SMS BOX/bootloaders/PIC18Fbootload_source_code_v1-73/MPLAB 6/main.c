/*

PIC weather logger
note: when storing data in arrays, I have chosen lo byte first, high byte second as in the PIC16C7x series
	  ie: 243*17=4131 is 243 in array[0] and 17 in array[1]

*/

#include	<pic18.h>
#include	<conio.h>
#include	<math.h>
#include 	<stdio.h>
#include	<stdlib.h>
#include	"main.h"
#include	"delay.h"
#include	"bootldr.h"

//__CONFIG(1,XT & OSCSDIS); //for <8Mhz
__CONFIG(1,HS & OSCSDIS); //for <20Mhz
//__CONFIG(1,HSPLL & OSCSDIS); //for 40Mhz (10Mhz crystal with x4 PLL)

__CONFIG(2,BORDIS & PWRTEN & WDTDIS);
__CONFIG(4,DEBUGDIS & LVPDIS & STVRDIS);
__CONFIG(5,UNPROTECT);
__CONFIG(6,WRTEN);
__CONFIG(7,TRU);

__EEPROM_DATA (1,2,3,4,5,6,7,8);

void
main()
{
//	asm("goto _boot_loader");
	boot_loader();
}


