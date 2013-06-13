/*************************************************************************************************************************
	WinSocketClass.h
*************************************************************************************************************************/

#ifndef WinSocketClassH
	#define WinSocketClassH

#include <windows.h>

class WinSocketClass {

	private:

		WinSocketClass *pInterface;
	
	public:

		WinSocketClass *GetInterface(void);

		virtual int Connect(char *s_server, unsigned short sh_port){ return 0; }
		virtual int CreateSocketUDP(unsigned short PORT){ return 0; }
		virtual int CloseSocketUDP( int SocketUDP ){ return 0; }
		virtual int SendTo(char *TxBuf, int NumBytes, char *IP, unsigned short PORT){ return 0; }
		virtual int RecvFrom(int SocketUDP, char *RecvBuf, int NumBytes, char *IP, int timeout = 0){ return 0; }
		virtual int SetSocketSendBuffer(int _Socket, int iSize){ return 0; }
		virtual int SetSocketRecvBuffer(int _Socket, int iSize){ return 0; }
		virtual int SetUDPSockTxBuffSize (int iSize, int hSocket){ return 0; }
		virtual int SetUDPSockRxBuffSize (int iSize, int hSocket){ return 0; }
		virtual int Recv(int _Socket, char *RecvBuf, int NumBytes, int TimeOut = -1){ return 0; }
		virtual int Send(int _Socket, char *TxBuf, int NumBytes, int TimeOut){ return 0; }
		virtual int CreateServer(unsigned short Port){ return 0; }
		virtual int Accept(void){ return 0; }
		virtual int Accept(int timeout){ return 0; }
		virtual int SetSocketToWindow(int _Socket, char *WindowName, WNDPROC wndproc, unsigned int UserMsg, long NetEvents, void *lparams = NULL){ return 0; }
		virtual void CloseSocket(int _Socket){ }
		virtual void Dispatch(void){ }
		virtual const char *GetLastError(){ return NULL; }
		virtual const char *GetIpClient(void){ return NULL; }
    virtual HWND GetWindowHandle(void){ return NULL; }

		WinSocketClass(){}
		~WinSocketClass(){}
};

#endif

