
#include "stdafx.h"
#include "EnumDevices.h"

UINT EnumDevices( CStdStrArray &devices, TCHAR * cPrefix )
{
  CStdString sPrefix( cPrefix );
  CStdString sCurrDev;
  int i=0;

  //Make sure we clear out any elements which may already be in the array
  devices.clear();

  //Determine what OS we are running on
  OSVERSIONINFO osvi;
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  BOOL bGetVer = GetVersionEx(&osvi);

  //On NT use the QueryDosDevice API
  if (bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
  {
    //Use QueryDosDevice to look for all devices of the form COMx. This is a better
    //solution as it means that no devices have to be opened at all.
    TCHAR szDevices[65535];
    DWORD dwChars = QueryDosDevice(NULL, szDevices, 65535);
    if (dwChars)
    {

      for (;;)
      {
        //Get the current device name
        TCHAR* pszCurrentDevice = &szDevices[i];
        sCurrDev = &szDevices[i];
        sCurrDev.ToUpper();


        //If it looks like "COMX" then
        //add it to the array which will be returned
        int nLen = sCurrDev.GetLength();
        if (nLen > sPrefix.GetLength() && _tcsnicmp(sCurrDev.c_str(), sPrefix.c_str() , sPrefix.GetLength() ) == 0)
        {
          //Work out the port number
          devices.push_back( CStdString(_T("\\\\.\\")) + CStdString( pszCurrentDevice ) );
        }

        // Go to next NULL character
        i+= sCurrDev.GetLength();
        //while(szDevices[i] != _T('\0'))
        //  i++;

        // Bump pointer to the next string
        i++;

        // The list is double-NULL terminated, so if the character is
        // now NULL, we're at the end
        if (szDevices[i] == _T('\0'))
          break;
      }
    }
    else
    {
      return -1;
    }
      
  }
  else
  {
    //On 95/98 open up each port to determine their existence

    //Up to 255 COM devices are supported so we iterate through all of them seeing
    //if we can open them or if we fail to open them, get an access denied or general error error.
    //Both of these cases indicate that there is a COM port at that number. 
    for (UINT i=1; i<256; i++)
    {
      //Form the Raw device name
      CStdString sDev;
      sDev.Format(_T("\\\\.\\%s%d"), sPrefix.c_str(), i);

      //Try to open the port
      BOOL bSuccess = FALSE;
      HANDLE hPort = ::CreateFile(sDev.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
      if (hPort == INVALID_HANDLE_VALUE)
      {
        DWORD dwError = GetLastError();

        //Check to see if the error was because some other app had the port open or a general failure
        if (dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
          bSuccess = TRUE;
      }
      else
      {
        //The port was opened successfully
        bSuccess = TRUE;

        //Don't forget to close the port, since we are going to do nothing with it anyway
        CloseHandle(hPort);
      }

      //Add the port number to the array which will be returned
      if (bSuccess)
        devices.push_back(sDev.c_str());
    }
  }
  return devices.size();
}
