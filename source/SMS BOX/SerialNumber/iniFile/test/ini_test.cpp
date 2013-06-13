
#include <iostream>

using namespace std;

#include "iniFile.h"

int main()
{
  CIniFile iniFile( "./ini_test.ini");
  iniFile.ReadFile();

  cout << "Hello" << endl;
  cout << "NKeys = " << iniFile.NumKeys() << endl;
  cout << "Num Values for \"386enh\" = " <<
    iniFile.NumValues( "386enh") << endl;
  cout << "Num Values for \"crapXXX\" = " <<
    iniFile.NumValues( "crapXXX") << endl;
  cout << "crapXXX:fred = " << iniFile.GetValueF( "crapXXX", "fred", 3.14159) << endl;
  cout << "ScreenTime:previousProjectorProcessID = ";
  cout << iniFile.GetValueI( "ScreenTime", "previousProjectorProcessID") << endl;
  iniFile.DeleteValue( "drivers", "timer");
  cout << "Num drivers = " << iniFile.NumValues( "drivers") << endl;
  cout << "drivers:timer = " << iniFile.GetValue( "drivers", "timer") << endl;
  cout << "drivers:wave = " << iniFile.GetValue( "drivers", "wave") << endl;

  iniFile.Path( "./ini_test.sav");
  iniFile.WriteFile();

  // Lookup what we have now.
  for ( unsigned keyID = 0; keyID < iniFile.NumKeys(); ++keyID) {
    cout << "Key = " << iniFile.KeyName( keyID) << endl;
    for ( unsigned valueID = 0; valueID < iniFile.NumValues( keyID); ++valueID)
      cout << "   ValueName = " << iniFile.ValueName( keyID, valueID) <<
	"  Value = " << iniFile.GetValue( keyID, valueID) << endl;
  }
  return 0;
}
