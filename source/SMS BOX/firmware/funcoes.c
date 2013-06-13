#include "funcoes.h"
#include <ctype.h>

BYTE ascii2int( BYTE asciiChar ){
  BYTE bChar;
  
  bChar = toupper( asciiChar );
  
  if ( (bChar >= '0') && (bChar <= '9') ){
    return bChar - '0';
  }
  else if ((bChar >= 'A') && (bChar <= 'F')){
    return (bChar - 'A') + 10;
  }
  return 0;
} 

//--------------------------------------

int abs_word( int wVal ){
  return ( wVal > 0 ) ? wVal : -wVal;
}

//--------------------------------------
