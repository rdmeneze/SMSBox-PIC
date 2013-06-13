// crcGen.cpp : Defines the entry point for the console application.
//

#include "stdio.h"


int main(int argc, char* argv[])
{
  char cBuffer[64];
  char crc = 0; 
  char i;

  cBuffer[0] = 1;
  cBuffer[1] = 0;

  cBuffer[2] = sprintf( &cBuffer[4], "AT+CFUN=?\r\n" ) + 1;
  cBuffer[3] = 2;

  for ( i = 0; i < cBuffer[2] + 3; i++ ){
    crc ^= cBuffer[i];
  }
  
  cBuffer[cBuffer[2]+3] = crc;


	return 0;
}

