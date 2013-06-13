/*************************************************************************************************************************
	WinSocket
*************************************************************************************************************************/

#include <Winsock2.h>
#include <windows.h>
#include "WinSocketClass.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "StdString.h"

// Tamanho do buffer do socket (Client/Server)
#define	SOCKET_BUFFER			8192

#ifndef HWND_MESSAGE
	#define HWND_MESSAGE		((HWND)-3)
#endif


class WinSocket : public WinSocketClass {

	private:

		HOSTENT			*lp_HostEntry;			// Estrutura de entradas para conexao com Host
		int					ServerSocket;				// Socket para conexao Server
		SOCKADDR_IN ClientSockAddr;			// Estrutura de enderecamento WinSock para client
		SOCKADDR_IN ServerSockAddr;			// Estrutura de enderecamento WinSock para server
		CStdString	sLastError;					// Buffer para armazenar a CStdString com o ultimo erro ocorrido
		char				HostClient[256];		// Endereco IP do cliente que conectou no server, caso 
																		// o objeto se comporte como server, ou o IP caso
																		// se comporte como client

		HWND					tcpWnd;
    unsigned int  TCPUserMessage;
    long          TCPNetEvents;

		int CreateTcpWindow(char *WindowName, WNDPROC wndproc, void *lpParam = NULL);

	public:


		int Connect(char *s_server, unsigned short sh_port);
		int CreateSocketUDP(unsigned short PORT);
		
		int CloseSocketUDP( int SocketUDP );
		int SendTo(char *TxBuf, int NumBytes, char *IP, unsigned short PORT);
		int RecvFrom(int SocketUDP, char *RecvBuf, int NumBytes, char *IP, int timeout = 0);
		int SetSocketSendBuffer(int _Socket, int iSize);
		int SetSocketRecvBuffer(int _Socket, int iSize);
		int SetUDPSockTxBuffSize (int iSize, int hSocket);
		int SetUDPSockRxBuffSize (int iSize, int hSocket);
		int Recv(int _Socket, char *RecvBuf, int NumBytes, int TimeOut = -1);
		int Send(int _Socket, char *TxBuf, int NumBytes, int TimeOut);
		int CreateServer(unsigned short Port);
		int Accept(void);
		int Accept(int timeout);

		void CloseSocket(int _Socket);
		void Dispatch(void);

		const char *GetLastError();
		const char *GetIpClient(void);

		int SetSocketToWindow(int _Socket, char *WindowName, WNDPROC wndproc, unsigned int UserMsg, long NetEvents, void *lparams = NULL);
    HWND GetWindowHandle(void);

		WinSocket();
		~WinSocket();
};

//------------------------------------------------------------------------------------------------------------------------

WinSocketClass *WinSocketClass::GetInterface(void)
{
	pInterface = (WinSocket *)new WinSocket();
	return (WinSocket *)pInterface;
}

//------------------------------------------------------------------------------------------------------------------------

WinSocket::WinSocket()
{
	try
	{
    tcpWnd = NULL;
		ServerSocket	= 0;
	}
	catch(...){
		sLastError = "Exception in WinSocket::WinSocket()";
		return;
	}
}

//------------------------------------------------------------------------------------------------------------------------

WinSocket::~WinSocket()
{
}

//------------------------------------------------------------------------------------------------------------------------

const char *WinSocket::GetLastError(void)
{
	return sLastError.c_str();
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::Connect(char *s_server, unsigned short sh_port)
{
	int i_flag = 1;
	int i_ret;
	unsigned long inaddr;
	int _Socket;

	try
	{
		// A resolucao de endereco IP deve sempre tentar primeiro o endereco depois o nome,
		// pois a resolocao de nome demora mais para retornar caso ocorra algum erro

		// tenta resolver o IP por endereco
		inaddr = inet_addr(s_server);

		if(inaddr != INADDR_NONE){
			ClientSockAddr.sin_family = AF_INET;				// Address family
			ClientSockAddr.sin_port		= htons(sh_port);	// Port number
			memcpy((char *)&ClientSockAddr.sin_addr, (char *)&inaddr, sizeof(inaddr));
		}
		else{	// tenta resolver o IP por nome de servidor

			lp_HostEntry = gethostbyname(s_server);

			if(lp_HostEntry == NULL){
				sLastError = "Server not found";
				return 0;
			}
			// preenche a estrutura de endereco
			ClientSockAddr.sin_family = AF_INET;
			ClientSockAddr.sin_port		= htons(sh_port);	// Port number
			ClientSockAddr.sin_addr		= *((LPIN_ADDR)*lp_HostEntry->h_addr_list); // Server's address
		}

		// cria o socket
		_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if( _Socket == INVALID_SOCKET )
		{
			sLastError = "Error in socket() in function WinSocket::Connect()";
			return 0;
		}

		i_ret = connect( _Socket, (LPSOCKADDR)&ClientSockAddr, sizeof(struct sockaddr) );

		if(i_ret == SOCKET_ERROR)
		{
			sLastError = "Error in connect() in function WinSocket::Connect()";
			CloseSocket( _Socket );
			return 0;
		}

		return _Socket;
	}
	catch(...)
	{
		sLastError = "Exception in WinSocket::connect()";
		CloseSocket( _Socket );
		return 0;
	}
}

/********************************************************************************************
	NOME:	Send

	DESCRICAO:	Envia dados via WinSock pelo socket criado

	PARAMETROS: char *TxBuf		- Buffer de recepcao para os dados
							int NumBytes	- Numero de bytes a enviar
							int TimeOut		- Tempo em segundos para esperar o socket ficar pronto para enviar

	RETORNO:		0		Se houve timeout ao esperar o socket ficar pronto para enviar
							-1	A conexao com o socket foi quebrada e o	socket e fechado automaticamente
							X		Caso nao tenha havido erro nem timeout, retorna o numero de bytes
									transmitidos
********************************************************************************************/
int WinSocket::Send(int _Socket, char *TxBuf, int NumBytes, int TimeOut)
{
	struct timeval timeval;
	fd_set wmask;
	int i,j;
	int k = 0;
	DWORD wsaFlags = 0;

	try
	{
		timeval.tv_sec	= TimeOut;
		timeval.tv_usec = 0;

		FD_ZERO(&wmask);

		FD_SET((unsigned int)_Socket, &wmask);

		// fica esperando pelo tempo especificado em timeval ate o socket ficar pronto para enviar
		if(select(FD_SETSIZE, NULL, &wmask, NULL, &timeval) < 0){
			return -1; // erro de conexao com o socket
		}
		
		if(!FD_ISSET( _Socket, &wmask )){
			return 0; // timeout ao esperar o socket ficar pronto para enviar
		}

		i = NumBytes;
		
		while( i ){
			
			j = send(_Socket, TxBuf+k, i, 0);
			if( (j == 0) || (j == SOCKET_ERROR ) ){
				return -1; // erro de conexao com o socket
			}

			i-=j;
			k+=j;
		}

		return NumBytes;		
	}
	catch(...)
	{
		sLastError = "Exception WinSocket::Send()";
		return -1; // erro de conexao com o socket
	}
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::Recv(int _Socket, char *RecvBuf, int NumBytes, int TimeOut)
{
	struct timeval timeval;
	fd_set rmask;
	WSABUF wsaBuf;
	DWORD wsaFlags = MSG_PARTIAL;
	int iRet;
	unsigned long BytesLidos;

	try
	{

		if( TimeOut == -1 ){

			iRet = recv( _Socket, RecvBuf, NumBytes, 0 );    

			if( iRet == 0 )
				return SOCKET_ERROR;

			if( iRet == SOCKET_ERROR )
				return SOCKET_ERROR;

			return iRet; // retorna o numero de bytes lidos
		}

		timeval.tv_sec	= TimeOut;
		timeval.tv_usec = 0;
		
		FD_ZERO(&rmask);

		FD_SET((unsigned int)_Socket, &rmask);

		// verifica se o socket tem dados a receber pelo tempo especificado em timeval
		if(select(FD_SETSIZE, &rmask, NULL, NULL, &timeval) < 0){
			CloseSocket(_Socket);
			return -1; // erro de conexao com o socket
		}
		
		if(!FD_ISSET(_Socket, &rmask)){
			return 0; // timeout na recepcao
		}
		
		wsaBuf.buf = RecvBuf;
		wsaBuf.len = NumBytes;

		iRet = WSARecv(_Socket, &wsaBuf, 1, &BytesLidos, &wsaFlags, NULL, NULL );    

		if ( iRet == SOCKET_ERROR )
		{
			CloseSocket(_Socket);
			return -1;
		}

		if(  BytesLidos == 0 ) {
			CloseSocket(_Socket);
			return -1; // erro de conexao com o socket
		} 

    iRet = WSAGetLastError();

    WSAAsyncSelect(_Socket, tcpWnd, TCPUserMessage, TCPNetEvents); 

		return BytesLidos; // retorna o numero de bytes lidos
	}
	catch(...)
	{
		sLastError = "Exception WinSocket::Recv()";
		return -1; // erro de conexao com o socket
	}
}

//------------------------------------------------------------------------------------------------------------------------

void WinSocket::CloseSocket(int _Socket)
{
	try
	{
		// desabilita recepcao e transmissao no socket, terminando de transmitir os dados pendentes
		shutdown(_Socket, SD_BOTH);
		// fecha o handle so socket
		closesocket(_Socket);
	}
	catch(...)
	{
		sLastError = "Exception WinSocket::CloseSocket()";
	}
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::CreateServer(unsigned short Port)
{
	try
	{
		memset(&ServerSockAddr, 0,sizeof(ServerSockAddr));

		ServerSockAddr.sin_port					=	htons(Port);
		ServerSockAddr.sin_family				=	AF_INET;
		ServerSockAddr.sin_addr.s_addr	=	htonl(INADDR_ANY);

		if( ServerSocket > 0 ){
			shutdown(ServerSocket, SD_BOTH);
			closesocket(ServerSocket);
			ServerSocket = 0;
		}

		ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if( ServerSocket == INVALID_SOCKET ){
			sLastError = "Error in socket() function WinSocket::CreateServer()";
			return -1;
		}
		if( bind(ServerSocket, (LPSOCKADDR)&ServerSockAddr, sizeof(ServerSockAddr)) == SOCKET_ERROR ){
			sLastError = "Error in bind() function WinSocket::CreateServer()";
			return -1;
		}
		if( listen(ServerSocket, SOMAXCONN) == SOCKET_ERROR ){
			sLastError = "Error in listen() function WinSocket::CreateServer()";
			return -1;
		}

		return 0;
	}
	catch(...)
	{
		sLastError = "Exception WinSocket::CreateServer()";
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::Accept(void)
{
	int addrLen = sizeof(SOCKADDR_IN);
	int OptionValue;
	int Socket;

	try {

		Socket = accept(ServerSocket, (LPSOCKADDR) &ClientSockAddr, &addrLen);

		if( Socket == INVALID_SOCKET ){
			sLastError = "Error in accept() function WinSocket::Accept()";
			return -1;
		}

		sprintf(HostClient, "%d.%d.%d.%d", 
											ClientSockAddr.sin_addr.S_un.S_un_b.s_b1,
											ClientSockAddr.sin_addr.S_un.S_un_b.s_b2,
											ClientSockAddr.sin_addr.S_un.S_un_b.s_b3,
											ClientSockAddr.sin_addr.S_un.S_un_b.s_b4);

		OptionValue = SOCKET_BUFFER;
		
		setsockopt(Socket, SOL_SOCKET, SO_RCVBUF, (char *)&OptionValue, sizeof(OptionValue));

		OptionValue = SOCKET_BUFFER;
		
		setsockopt(Socket, SOL_SOCKET, SO_SNDBUF, (char *)&OptionValue, sizeof(OptionValue));

		return Socket;
	}
	catch(...)
	{
		sLastError = "Exception WinSocket::Accept()";
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::Accept( int timeout )
{
	int addrLen = sizeof(SOCKADDR_IN);
	int OptionValue;
	struct timeval timeval;
	fd_set rmask;
	int Socket;

	try {

		timeval.tv_sec	= timeout;
		timeval.tv_usec = 0;

		FD_ZERO(&rmask);

		FD_SET((unsigned int)ServerSocket, &rmask);

		// fica esperando pelo tempo especificado em timeval ate o socket ficar pronto para aceitar
		if(select(FD_SETSIZE, &rmask, NULL, NULL, &timeval) < 0){
			return -1; // erro de conexao com o socket
		}
		if(!FD_ISSET(ServerSocket, &rmask)){
			return 0; // timeout ao esperar o socket ficar pronto para aceitar
		}

		Socket = accept(ServerSocket, (LPSOCKADDR) &ClientSockAddr, &addrLen);

		if( Socket == INVALID_SOCKET ){
			sLastError = "Error in accept() function WinSocket::Accept()";
			return -1;
		}

		sprintf(HostClient, "%d.%d.%d.%d", 
											ClientSockAddr.sin_addr.S_un.S_un_b.s_b1,
											ClientSockAddr.sin_addr.S_un.S_un_b.s_b2,
											ClientSockAddr.sin_addr.S_un.S_un_b.s_b3,
											ClientSockAddr.sin_addr.S_un.S_un_b.s_b4);

		OptionValue = SOCKET_BUFFER;
		setsockopt(Socket, SOL_SOCKET, SO_RCVBUF, (char *)&OptionValue, sizeof(OptionValue));

		OptionValue = SOCKET_BUFFER;
		setsockopt(Socket, SOL_SOCKET, SO_SNDBUF, (char *)&OptionValue, sizeof(OptionValue));

		return Socket;
	}
	catch(...)
	{
		sLastError = "Exception WinSocket::Accept()";
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::CreateSocketUDP(unsigned short PORT)
{
	SOCKADDR_IN SockAddr; // Estrutura de enderecamento WinSock
	int SocketUDP;			// Socket	
	int ReceiveBufferSize;

	try {
		
		SocketUDP = socket(AF_INET, SOCK_DGRAM, 0);
		
		if( SocketUDP == INVALID_SOCKET ){
			sLastError = "Error in socket() function CreateSocketUDP()";
			return -1;
		}

		memset(&SockAddr, 0,sizeof(SockAddr));

		SockAddr.sin_port					=	htons(PORT);
		SockAddr.sin_family				=	AF_INET;
		SockAddr.sin_addr.s_addr	=	htonl(INADDR_ANY);

		if( bind(SocketUDP, (LPSOCKADDR)&SockAddr, sizeof(SockAddr)) == SOCKET_ERROR ){
			shutdown(SocketUDP, SD_BOTH);
			closesocket(SocketUDP);
			sLastError = "Error in bind() function BindSocketUDP()";
			return -1;
		}

		ReceiveBufferSize = SOCKET_BUFFER;
		
		setsockopt(SocketUDP, SOL_SOCKET, SO_RCVBUF, (char *)&ReceiveBufferSize, sizeof(ReceiveBufferSize));

		ServerSocket = SocketUDP;

		return SocketUDP;
	}
	catch(...){
		sLastError = "Exception CreateSocketUDP()";
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::CloseSocketUDP( int SocketUDP )
{
	try {

		// desabilita recepcao e transmissao no socket, terminando de transmitir os dados pendentes
		shutdown( SocketUDP, SD_BOTH );
		// fecha o handle so socket
		closesocket( SocketUDP );
		return 0;
	}
	catch(...){
		sLastError = "Exception CloseSocketUDP()";
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::SendTo(char *TxBuf, int NumBytes, char *IP, unsigned short PORT)
{
	SOCKADDR_IN SockAddr;		// Estrutura de enderecamento WinSock
	int SocketUDP = -1;	// Socket	
  struct hostent *hostp;
	int i = 0;
	int j = 0;
	int k = 0;

	try {

		SocketUDP = socket(AF_INET, SOCK_DGRAM, 0);

		if( SocketUDP == INVALID_SOCKET ){
			sLastError = "Error in socket() function WinSocket::CreateSocketUDP()";
			return -1;
		}

		memset(&SockAddr, 0,sizeof(SockAddr));

		SockAddr.sin_family				=	AF_INET;
		SockAddr.sin_port					=	htons(PORT);
		SockAddr.sin_addr.s_addr	=	htonl(INADDR_ANY);

		hostp = gethostbyname(IP);

		if(hostp == NULL){
			shutdown(SocketUDP, SD_BOTH);
			closesocket(SocketUDP);
			sLastError = "Error in gethostbyname() function WinSocket::SendTo()";
			return -1;
		}

		memcpy((char *)&(SockAddr.sin_addr.s_addr), hostp->h_addr, hostp->h_length);

		i = NumBytes;

		while( i ){

			j = sendto(	SocketUDP, TxBuf+k, i, 0, (struct sockaddr *)&SockAddr, sizeof(SockAddr));
			
			if( j == SOCKET_ERROR )
				return -1;

			i-=j;
			k+=j;
		}

		shutdown(SocketUDP, SD_BOTH);
		closesocket(SocketUDP);
		// retorna o numero de bytes enviados
		return NumBytes;
	}
	catch(...){
		shutdown(SocketUDP, SD_BOTH);
		closesocket(SocketUDP);
		sLastError = "Exception WinSocket::SendTo()";
		return -1; // erro de conexao com o socket
	}
}
/************************************************************************************************/
/* Metodo: RecvFrom (int SocketUDP, char *RecvBuf, int NumBytes, char *IP, int timeout)			*/
/*                                                                                              */
/* Descr.:  Recebe dados usando Winsock atraves do socket especificado													*/
/*																																															*/
/* Param:   [in] Socket UDP																																			*/
/*					[in] Data buffer																																		*/
/*					[in] Tamanho de buffer																															*/
/*					[in] IP address																																			*/
/*					[in] Timeout em segundos																														*/
/*                                                                                              */
/* Retorno: -1: se a conexão socket foi interrompida ou fechada automaticamente                 */
/*					N#: Numero de bytes lidos																														*/
/************************************************************************************************/
int WinSocket::RecvFrom(int SocketUDP, char *RecvBuf, int NumBytes, char *IP, int timeout)
{
	SOCKADDR_IN SockAddr; // Estrutura de enderecamento WinSock
	int BytesLidos = 0;
	int SockAddrLen;
	int rc;
  int ErrCode;
	timeval					timeParam;
	fd_set					rmask;


	try
	{

		memset(&SockAddr, 0,sizeof(SockAddr));

		SockAddrLen = sizeof(SockAddr);

		//Inicializa controle de recepcao de dados por timeout
		timeParam.tv_sec = timeout;
		timeParam.tv_usec = 0;

		FD_ZERO(&rmask);
		FD_SET((unsigned int)SocketUDP, &rmask);

		rc = select(FD_SETSIZE, &rmask, NULL, NULL, &timeParam);

		//Se rc == 1, tem dado

		if (rc == 1)
		{
			BytesLidos = recvfrom(SocketUDP, RecvBuf, NumBytes, 0, (struct sockaddr *)&SockAddr, &SockAddrLen);
		}

		if((BytesLidos == SOCKET_ERROR ) || (BytesLidos == 0) || (rc != 1))
		{
        ErrCode = WSAGetLastError (); //Para consultar na tabela (DEBUG)
				return -1; // erro de conexao com o socket
		}

		sprintf(IP, "%d.%d.%d.%d",
								SockAddr.sin_addr.S_un.S_un_b.s_b1,
								SockAddr.sin_addr.S_un.S_un_b.s_b2,
								SockAddr.sin_addr.S_un.S_un_b.s_b3,
								SockAddr.sin_addr.S_un.S_un_b.s_b4);
		
		return BytesLidos; // retorna o numero de bytes lidos
	}
	catch(...)
	{
		sLastError = "Exception WinSocket::RecvFrom()";
		return -1; // erro de conexao com o socket
	}
}

//------------------------------------------------------------------------------------------------------------------------

const char *WinSocket::GetIpClient(void)
{
	try	{
		
		return HostClient;
	}
	catch(...)
	{
		sLastError = "Exception WinSocket::GetIpClient()";
		return NULL;
	}
}


//------------------------------------------------------------------------------------------------------------------------
// Habilita um socket para trabalhar com janela

// char *WindowName				-> Nome da janela
// WNDPROC wndproc, 				-> Função (CALLBACK) que irá tratar os eventos de janela
// unsigned int UserMsg		-> Mensagem que a janela ira receber qdo algum evento ocorrer 
// long NetEvents					-> Tipos de eventos que a janela ira receber

int WinSocket::SetSocketToWindow(int _Socket, char *WindowName, WNDPROC wndproc, unsigned int UserMsg, long NetEvents, void *lparams)
{
	try
	{
		int ret = 0;

    TCPNetEvents    = NetEvents;
    TCPUserMessage  = UserMsg;
		
		if( CreateTcpWindow(WindowName, wndproc, lparams) == -1)
			return -1;

		if( ServerSocket )
			ret = WSAAsyncSelect(ServerSocket, tcpWnd,	UserMsg, NetEvents);
		else
			ret = WSAAsyncSelect(_Socket, tcpWnd,	UserMsg, NetEvents);

		if( ret < 0 )
		{
			int error = WSAGetLastError();

			switch(error){

				case WSANOTINITIALISED: // A successful WSAStartup call must occur before using this function. 
					sLastError = "Error: WSAAsyncSelect()";
				break;
				case WSAENETDOWN:				// The network subsystem has failed. 
					sLastError = "Error: WSAAsyncSelect()";
				break;
				case WSAEINVAL:					// Indicates that one of the specified parameters was invalid such as the window handle not referring to an existing window, or the specified socket is in an invalid state. 
					sLastError = "Error: WSAAsyncSelect()";
				break;
				case WSAEINPROGRESS:		// A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function. 
					sLastError = "Error: WSAAsyncSelect()";
				break;
				case WSAENOTSOCK:				// The descriptor is not a socket. 
					sLastError = "Error: WSAAsyncSelect()";
				break;
			}
			
			sLastError = "Error: WSAAsyncSelect()";
			return -1;
		}

		return 0; 
	}
	catch(...)
	{
		sLastError = "Exception WinSocket::SetSocketToWindow()";
		return NULL;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::CreateTcpWindow(char *WindowName, WNDPROC wndproc, void *lpParam)
{
	WNDCLASSEX wcex;
	HWND WindowParent;
	OSVERSIONINFO os_version_info;
	
	try	{

		wcex.cbSize         = sizeof(WNDCLASSEX); 
		wcex.style					= 0;
		wcex.lpfnWndProc		= (WNDPROC)wndproc;
		wcex.cbClsExtra			= 0;
		wcex.cbWndExtra			= 0;
		wcex.hInstance			= NULL;
		wcex.hIcon					= NULL;
		wcex.hCursor				= NULL;
		wcex.hbrBackground	= NULL;
		wcex.lpszMenuName		= NULL;
		wcex.lpszClassName	= WindowName;
		wcex.hIconSm				= NULL;

		// Nao testar o retorno desta funcao, pois podemos registrar uma mesma classe mais de uma vez
		RegisterClassEx(&wcex);
		
		os_version_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  
		if( GetVersionEx( &os_version_info ) )
		{
			if(os_version_info.dwMajorVersion >= 5)
				WindowParent = HWND_MESSAGE;
			else
				WindowParent = HWND_DESKTOP;
		}
		else{
			WindowParent = HWND_DESKTOP;
		}

		tcpWnd = CreateWindowEx( 0, 
								 WindowName, 
								 "", 
								 0, 
								 CW_USEDEFAULT, 
								 CW_USEDEFAULT, 
								 CW_USEDEFAULT, 
								 CW_USEDEFAULT, 
								 WindowParent,
								 NULL, 
								 NULL, 
								 (void *)lpParam );

		if( tcpWnd == NULL)
			return -1;

		return 0;

	}

	catch(...)
	{
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

void WinSocket::Dispatch(void)
{
	MSG Msg;

	while( GetMessage( &Msg, NULL, 0, 0) )
	{
		TranslateMessage( &Msg );
		DispatchMessage( &Msg );
	}
}

//------------------------------------------------------------------------------------------------------------------------

HWND WinSocket::GetWindowHandle(void)
{
  return tcpWnd;
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::SetSocketRecvBuffer(int _Socket, int iSize)
{
	try {

		int i_tamanho_buffer = iSize;
		int i_sizeof = 4;
		int iRet;

		iRet	=	setsockopt(_Socket, SOL_SOCKET, SO_RCVBUF, (char *)&i_tamanho_buffer, sizeof(i_tamanho_buffer));

		if(iRet)
			return -1;
		
		i_tamanho_buffer = 0;

		iRet	=	getsockopt(_Socket, SOL_SOCKET, SO_RCVBUF,  (char *)&i_tamanho_buffer, &i_sizeof);

		if(iRet)
			return -1;

		if(i_tamanho_buffer != iSize)
			return -1;

		return 0;
	}
	catch(...){
		sLastError = "Exception WinSocket::SetSocketRecvBuffer()";
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int WinSocket::SetSocketSendBuffer(int _Socket, int iSize)
{
	try {

		int i_tamanho_buffer = iSize;
		int i_sizeof = 4;
		int iRet;
		
		iRet	=	setsockopt(_Socket, SOL_SOCKET, SO_SNDBUF, (char *)&i_tamanho_buffer, sizeof(i_tamanho_buffer));

		if(iRet)
			return -1;
		
		i_tamanho_buffer = 0;

		iRet	=	getsockopt(_Socket, SOL_SOCKET, SO_SNDBUF,  (char *)&i_tamanho_buffer, &i_sizeof);

		if(iRet)
			return -1;

		if(i_tamanho_buffer != iSize)
			return -1;

		return 0;

	}
	catch(...){
		sLastError = "Exception WinSocket::SetSocketRecvBuffer()";
		return -1;
	}
}


/************************************************************************************************/
/* Metodo: SetUDPSockRxBuffSize (int iSize, int hSocket)																			*/
/*                                                                                              */
/* Descr.:  Seta o tamanho do buffer de dados UDP de recepçao utilizado pelo objeto winsock			*/
/* Param:   Tamanho (in), Handle da conexao (in)																								*/
/* Retorno: Indiferente																																					*/
/************************************************************************************************/
int WinSocket::SetUDPSockRxBuffSize (int iSize, int hSocket)
{
	try 
	{

		int i_tamanho_buffer = iSize;
		int i_sizeof = 4;
		int iRet;
		
		iRet	=	setsockopt(hSocket, SOL_SOCKET, SO_RCVBUF, (char *)&i_tamanho_buffer, sizeof(i_tamanho_buffer));

		if(iRet)
		{
			return -1;
		}
		
		i_tamanho_buffer = 0;

		iRet	=	getsockopt(hSocket, SOL_SOCKET, SO_RCVBUF,  (char *)&i_tamanho_buffer, &i_sizeof);

		if(iRet)
		{
			return -1;
		}

		if(i_tamanho_buffer != iSize)
		{
			return -1;
		}

		return 0;

	}
	catch(...)
	{
		sLastError = "Exception WinSocket::SetUDPSockRxRecvBuffer()";
		return -1;
	}
}



/************************************************************************************************/
/* Metodo: SetUDPSockTxBuffSize (int iSize, int hSocket)																			*/
/*                                                                                              */
/* Descr.:  Seta o tamanho do buffer de dados de envio UDP utilizado pelo objeto winsock				*/
/* Param:   Tamanho (in), Handle da conexao (in)																								*/
/* Retorno: Indiferente																																					*/
/************************************************************************************************/
int WinSocket::SetUDPSockTxBuffSize (int iSize, int hSocket)
{
	try 
	{

		int i_tamanho_buffer = iSize;
		int i_sizeof = 4;
		int iRet;
		
		iRet	=	setsockopt(hSocket, SOL_SOCKET, SO_SNDBUF, (char *)&i_tamanho_buffer, sizeof(i_tamanho_buffer));

		if(iRet)
		{
			return -1;
		}
		
		i_tamanho_buffer = 0;

		iRet	=	getsockopt(hSocket, SOL_SOCKET, SO_SNDBUF,  (char *)&i_tamanho_buffer, &i_sizeof);

		if(iRet)
		{
			return -1;
		}

		if(i_tamanho_buffer != iSize)
		{
			return -1;
		}

		return 0;

	}
	catch(...)
	{
		sLastError = "Exception WinSocket::SetUDPSockTxBuffSize()";
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------
