#include "Timer0.h"
#include "defs.h"
#include "processor.h"

void InitTimer0( void )
{
  // incremento do timer0 a cada (1/(18432000/4)) * Preescaler
  // no meu caso, o preescaler está com fator de divisão 1:16
  // assim, a cada 3.47us haverá um incremento no timer
  
  T0CONbits.T08BIT  = 0;
  T0CONbits.T0CS    = 0;
  T0CONbits.PSA = 1;

  T0CONbits.T0PS2 = 0;
  T0CONbits.T0PS1 = 1;
  T0CONbits.T0PS2 = 1;

  T0CONbits.TMR0ON = 1;

  return;
}
