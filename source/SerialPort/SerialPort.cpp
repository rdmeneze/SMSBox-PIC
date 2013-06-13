// SerialPort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "protsmsbox.h"
#include <map>
#include "StdString.h"

int _tmain(int argc, _TCHAR* argv[])
{
  smsbox::CSMSBox box( "COM2" );
 
  //box.Open("COM4");

  if( box.IsOpen() == FALSE )
  {
    return -1;
  }

  
  return 0;
}

