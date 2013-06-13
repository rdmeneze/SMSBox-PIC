/*
 *	Delay functions
 *	See delay.h for details
 *
 *	Make sure this code is compiled with full optimization!!!
 */

#include	"delay.h"

void
DelayMs(unsigned char cnt)
{

	unsigned char	i;
	do {
		i = 4;
		do {
			DelayUs(250);
		} while(--i);
	} while(--cnt);

}

