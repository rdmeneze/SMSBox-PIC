
#ifndef tcp_ip_interface_h
	#define tcp_ip_interface_h

#include <windows.h>
#include "StdString.h"
#include "packet.h"
#include <map>

//--------------------------------------------------------------------------

typedef void (*ActionRoutineEntryPoint)(ST_PACKET * pacote, LPVOID lparam);

typedef struct 
{
public:
  ActionRoutineEntryPoint routine;
  void * instance;
} ST_ACTION;

//typedef std::map <CStdString, ST_ACTION*> MapStringAction;

//--------------------------------------------------------------------------

class tcp_ip_interface 
{
	public:
		virtual LRESULT CALLBACK VirtualCallBack(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
		virtual int Send(DWORD RemoteId, const char *sData, const char *sHandle = NULL) = 0;
		virtual bool Connected(void) = 0;
		//[26473<]
    virtual ~tcp_ip_interface() {};
		//[26473>]
    virtual int RegisterAction( CStdString sAction, ActionRoutineEntryPoint routine, void * instance) = 0;
};

#endif



