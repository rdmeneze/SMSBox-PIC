
// $Id: WinService.h,v 1.3 2010/09/23 21:41:38 rafael.menezes Exp $

#ifndef __WINSERVICE_H__
	#define __WINSERVICE_H__

#include <windows.h>
#include "defs.h"

/**
 *  \brief Read the operation state of windows service
 *  \return windows service operation state
 */
int ServiceState(void);

bool IsService(void);
const char *GetServicePath(void);
void ReportServiceStatus( DWORD dwCurrentState, DWORD dwCheckPoint = 0, DWORD dwWaitHint = 0 );
void ServicePath(void);
void WaitForServiceStop(void);
VOID WINAPI ServiceHandler( DWORD fdwControl );
VOID WINAPI ServiceMain( DWORD dwArgc, LPTSTR *lpszArgv );
int InstallService(LPCTSTR lpszBinaryPathName, char * ServiceName, LPCTSTR lpDependencies);
int UnInstallService( char * ServiceName );
int HandleCommandLine(int argc, char *argv[]);
BOOL StartServiceCtrlDispatcher();

#endif
