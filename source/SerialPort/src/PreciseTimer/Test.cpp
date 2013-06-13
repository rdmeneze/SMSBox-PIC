
#include "PreciseTimer.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string Int64ToString(long long const& ri64, int iRadix=10)
{
	bool bNeg = (ri64 < 0);
	long long i64 = ri64;
	string ostrRes;
	bool bSpecial = false;
	if(true == bNeg)
	{
		i64 = -i64;
		if(i64 < 0)
			//Special case number -9223372036854775808 or 0x8000000000000000
			bSpecial = true;
		ostrRes.append(1, '-');
	}
	int iR;
	do
	{
		iR = i64 % iRadix;
		if(true == bSpecial)
			iR = -iR;
		if(iR < 10)
			ostrRes.append(1, '0' + iR);
		else
			ostrRes.append(1, 'A' + iR - 10);
		i64 /= iRadix;
	}
	while(i64 != 0);
	//Reverse the string
	string::iterator it = ostrRes.begin();
	if(bNeg)
		it++;
	reverse(it, ostrRes.end());
	return ostrRes;
}

int main()
{
	CPreciseTimer oPreciseTimer;
	cout << "Starting!" << endl;
	oPreciseTimer.StartTimer();
	DWORD dwStart = ::GetTickCount();
	::Sleep(5000);
	cout << "Ending!" << endl;
	oPreciseTimer.StopTimer();
	DWORD dwDiff = (::GetTickCount() - dwStart)*1000;
	long long i64Diff = oPreciseTimer.GetTime();
	cout << "Diff1 (GetTickCount()) = " << dwDiff << endl;
	cout << "Diff2 (PreciseTimer) = " << Int64ToString(i64Diff) << endl;
	return 0;
}

