// Written By: Shane Hill
//
// This test code checks for memory leaks in the CIniFile class.
// Just run the code and use a program like "top" under Unix or
// TaskManager under Windows, to monitor the memory usage. The
// memory usage should reach a peak and not rise during the iterations.
// If memory continues to rise, there must be a leak.
//
// doMemTest:  is a destructor type test.
// doMemTest2: is a CIniFile::Erase() tester.

#include <iostream>
#include <strstream>

#include <stdio.h>

using namespace std;

#include "iniFile.h"

// This is a destructor type test.
void doMemTest()
{
  static unsigned count = 0;
  CIniFile iniFile("./memleak_test.sav");
  unsigned i;
  char svalue[2048];

  for ( i = 0; i < 5000; ++i) {
    sprintf( svalue, "Value%d", i);
    iniFile.SetValueI( "Header1", svalue, i);
  }
  iniFile.WriteFile();
  //iniFile.Erase();
  cout << ++count << " " << endl;
}

// This is a test of the CIniFile::Erase() function with
// no destructor use.
void doMemTest2()
{
  unsigned count = 0;
  CIniFile iniFile("./memleak_test.sav");
  unsigned i;
  char svalue[2048];

  while ( true) {
    for ( i = 0; i < 5000; ++i) {
      sprintf( svalue, "Value%d", i);
      iniFile.SetValueI( "Header1", svalue, i);
    }
    iniFile.WriteFile();
    iniFile.Erase();
    cout << ++count << " " << endl;
  }
}

int main()
{
  //while( true)
  //  doMemTest();
  doMemTest2();
}
