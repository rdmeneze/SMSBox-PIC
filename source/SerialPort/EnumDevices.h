#ifndef __ENUMDEVICES__
#define __ENUMDEVICES__

#include <windows.h>
#include <vector>
#include "StdString.h"

typedef std::vector< CStdString > CStdStrArray ;

/**
 * \brief Enumerate the devices in the machine
 * \param devices The array of devices present in the machine
 * \param cPrefix The prefix of type of device 
 */
UINT EnumDevices( CStdStrArray &devices, TCHAR * cPrefix );


#endif //~ __ENUMDEVICES__