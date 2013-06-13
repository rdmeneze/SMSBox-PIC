#include <iostream>
#include "serial.h"

using namespace std;

int main(int argc, char *argv[])
{
  network::CSerial serial;

  serial.Open("COM4");

  return 0;
}
