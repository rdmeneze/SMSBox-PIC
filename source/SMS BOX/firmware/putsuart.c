#include <p18cxxx.h>
#include "sw_uart.h"

/**********************************************************************
*    Function Name:  putsUART                                         *
*    Return Value:   void                                             *
*    Parameters:     data: pointer to string of data                  *
*    Description:    This routine transmits a string of characters    *
*                    to the UART data byte including the null.        *
**********************************************************************/
void putsUART( char *data)
{
  do
  {    // Transmit a byte
    putcUART(*data);
  } while( *data++ );
}
