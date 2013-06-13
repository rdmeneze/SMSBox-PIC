#include <Application.h>
#include "tcp_ip.h"
#include "ReqQueue.h"
#include "Register.h"

//------------------------------------------------------------------------------------------------------------------------

// Thread de controle dos eventos TcpIp
DWORD Thread_tcp(void *param)
{
	try	{

		tcp_ip *ptcp = (tcp_ip *)param;

		ptcp->InitClient();

		ptcp->Dispatch();

		return 0;
	}
	catch(...){
		return 0;
	}
}

//------------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK tcp_ip::VirtualCallBack(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	try	{

		switch(uMsg) {

			case WM_TCP:
				
				switch( WSAGETSELECTEVENT(lParam) )	{
	
					case FD_READ:
						Read();
					break;

					case FD_CLOSE:
						Close(WSAGETSELECTERROR(lParam));
					break;
				}
			break;

			case WM_DESTROY:
				PostQuitMessage(0);
			break;

			default:
				return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
		}

		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

//------------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK tcp_ip::CallBack(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	try	{

		tcp_ip *pHWND;

		if( uMsg == WM_NCCREATE ){
			// Obtem o ponteiro para a janela do parametro lpCreateParams na chamada de CreateTcpWindow
			SetWindowLong(hWnd, GWL_USERDATA, (long) LPCREATESTRUCT(lParam)->lpCreateParams );
		}

		// Obtem o ponteiro do objeto real
		pHWND = (tcp_ip *)GetWindowLong(hWnd, GWL_USERDATA);

		if( pHWND )
			return pHWND->VirtualCallBack(hWnd, uMsg, wParam, lParam);
		else
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	catch(...){
		return FALSE;
	}
}

//------------------------------------------------------------------------------------------------------------------------

tcp_ip::tcp_ip(const char *sHostServer, unsigned short PortServer)
{
	try {

		//[4167<]
		iRecvBufSize				= 0;
		iRecvBufActualSize	= 0;
		RecvBuf							=	NULL;
		//[4167>]

		_Socket = 0;

		bConnected = false;

		strcpy(Host, sHostServer);

		Port = PortServer;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_tcp, (void *)this, 0, NULL);

    RegisterAction( "HELLO", ActionHelloEntryPoint, this );
	}
	catch(...){
	}
}

//------------------------------------------------------------------------------------------------------------------------

void tcp_ip::Dispatch(void)
{
	pSocket->Dispatch();
}

//------------------------------------------------------------------------------------------------------------------------

void tcp_ip::InitClient(void)
{
	CStdString sTemp;

	// Cria objeto de socket
	pSocket = new WinSocketClass();

	pSocket = pSocket->GetInterface();

  iLogLevel = Register::LogLevel;
	// Inicializa o objeto de log erros
	pLog = new LogFile("IP", Register::LogLevel, Register::BasePathLog, true, true);
	// Seta o nivel de Log
	pLog->SetLevel(Register::LogLevel);

	//[17_05_2010<]
	// Conecta ao VosProxy
	sTemp.Format("Connecting to:  %s : %d ...", Host, Port);
	Log(LOG_TCP_IP, sTemp.c_str());
	//[17_05_2010>]

	Connect();
}

//------------------------------------------------------------------------------------------------------------------------

int tcp_ip::Connect(void)
{
	try {

		for(;;)
		{
			Sleep(100);

			_Socket = pSocket->Connect(Host, Port);

			if( _Socket <= 0 ){
				_Socket = 0;
				continue;
			}

			pSocket->SetSocketRecvBuffer(_Socket, TCP_BUFFER_SIZE );
			pSocket->SetSocketSendBuffer(_Socket, TCP_BUFFER_SIZE );

			pSocket->SetSocketToWindow(_Socket, "tcp", CallBack, WM_TCP, FD_CLOSE|FD_READ|FD_WRITE, (void *)this);

			if( SendHello() )
			{
				pSocket->CloseSocket(_Socket);
				_Socket = 0;
				continue;
			}

			break;
		}

		return 0;
	}
	catch(...)
	{
		Log(LOG_ERROR, "EXCEPTION: tcp_ip::Connect()");
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

void tcp_ip::Close(int errorcode)
{
	CStdString sAux, sTemp;

	try
	{
		Log(LOG_TCP_IP, "Close socket");

		CriticalSection::Scope scope(&CritSocket);

		pSocket->CloseSocket(_Socket);

		_Socket = 0;
		bConnected = false;

		//[17_05_2010<]
		sTemp.Format("Connecting to:  %s : %d ...", Host, Port);
		Log(LOG_TCP_IP, sTemp.c_str());
		//[17_05_2010>]

		Connect();
	}
	catch(...)
	{
	}
}

//------------------------------------------------------------------------------------------------------------------------

void tcp_ip::Read(void)
{
	int iBytes, iRet, iBegin, iEnd;

	try
	{
		CriticalSection::Scope scope(&CritSocket);

		Sleep(1);

		// Verifica se precisa fechar o arquivo de log dos canais gerenciados pela thread

		if( Application::bCloseLogFiles )
			pLog->CloseFile();

		//[4167<]
		// Sempre limpa o TmpBuf
		iTmpBufActualSize = 0;

		// Tenta receber o maximo que o TmpBuf suporta
		iBytes = pSocket->Recv(_Socket, tmpBuf, TCP_BUFFER_SIZE);

		if( iBytes < 0 )
		{
			// Erro de leitura no socket, o mesmo deve ser fechado
			pSocket->CloseSocket(_Socket);
			_Socket = 0;
			return;
		}

		iTmpBufActualSize = iBytes;

		// Copia dados do TmpBuf para RecvBuf, (re)alocando memoria p/ RecvBuf
		if( iTmpBufActualSize > 0 )
		{
			// Realoca memoria para o buffer final (RecvBuf)
			// Se o RecvBuf estiver vazio (NULL - primeira vez), realloc funciona como malloc

			RecvBuf = (char *) realloc(RecvBuf, iRecvBufSize + iTmpBufActualSize);

			if( RecvBuf == NULL )
			{
				// Erro: memoria insuficiente
				iRecvBufSize				= 0;
				iRecvBufActualSize	= 0;
				Log(LOG_ERROR, "tcp_ip::Read() - NOT ENOUGH MEMORY");
				Close(_Socket);
				return;
			}
		}

		// Atualiza tamanho do buffer final
		iRecvBufSize = _msize( RecvBuf );
		// Concatena dados do buffer temp no buffer final
		memcpy((RecvBuf) + (iRecvBufActualSize), tmpBuf, iTmpBufActualSize);
		// Atualiza o tamanho atual no buffer final
		iRecvBufActualSize += iTmpBufActualSize;
		//[4167>]

		for(;;)
		{
			iRet = GetPacket(RecvBuf, 0, iRecvBufActualSize, iBegin, iEnd);

			switch(iRet){

				case PACKET_NO_SOH:
					Log(LOG_ERROR, "ERROR: tcp_ip::Read() - SOH not found");
					// Nao existe Start of header nos dados, entao descarta
					iRecvBufActualSize	=	0;
				return;

				case PACKET_NEED_DATA:
					Log(LOG_INFO, "INFO: tcp_ip::Read() - packet need more data");
					memcpy(&RecvBuf[0], &RecvBuf[iBegin], iEnd - iBegin);
					iRecvBufActualSize	= iEnd - iBegin;
				return;
				
				case PACKET_OK:
					if( iRecvBufActualSize == iEnd )
					{
						CheckPacket(iBegin, iEnd );

						free( RecvBuf );
						RecvBuf = NULL;
						iRecvBufSize = 0;
						iRecvBufActualSize = 0;
						return;
					}
					else
					{
						CheckPacket(iBegin, iEnd );
						memcpy(&RecvBuf[0], &RecvBuf[iEnd], iRecvBufActualSize - iEnd);
						iRecvBufActualSize -= iEnd;
					}
				break;

				case PACKET_ERROR:
					Log(LOG_ERROR, "ERROR: tcp_ip::Read() - Packet error");
					// Descatar o pacote errado
					iRecvBufActualSize = 0;
				break;
			}
		}

		return;
	}
	catch(...)
	{
		Log(LOG_ERROR, "EXCEPTION: tcp_ip::Read()");
	}
}

//------------------------------------------------------------------------------------------------------------------------

void tcp_ip::CheckPacket(int iBegin, int iEnd)
{
	UNION_HEADER union_header;
	DWORD SourceId, SourceType, DestinationId, DestinationType;
	CStdString sTemp;
  CStdString sAction;

	try
	{
		memcpy(union_header.sHeader, &RecvBuf[iBegin], HEADER_SIZE);

		SourceId				= LOWORD( union_header.StHeader.SourceId );
		SourceType			= HIWORD( union_header.StHeader.SourceId );

		DestinationId		= LOWORD( union_header.StHeader.DestId );
		DestinationType	= HIWORD( union_header.StHeader.DestId );

		pacote.Header = union_header.StHeader;

		pacote.Data.assign(&RecvBuf[ iBegin + HEADER_SIZE ], iEnd - (iBegin+HEADER_SIZE));

		// Loga o pacote recebido
		RemoteId			= pacote.Header.SourceId;
		RemoteAppId		= LOWORD(pacote.Header.SourceId);
		RemoteAppType = HIWORD(pacote.Header.SourceId);

		//[17_05_2010<]
		sTemp.Format("RECV TYPE %d ID %d ",RemoteAppType, RemoteAppId);
		sTemp += pacote.Data; 
		Log(LOG_TCP_IP, sTemp.c_str());
		//[17_05_2010>]

		if(GetData("ACTION", sAction) < 0)
		{
			return;
		}

		// Executa a acao
		Action(sAction);
	}
	catch(...)
	{
		Log(LOG_ERROR, "EXCEPTION: tcp_ip::CheckPacket()");
	}
}

//------------------------------------------------------------------------------------------------------------------------

//[4167<]
int tcp_ip::Send(DWORD	RemoteId, const char *sData, const char *sHandle)
{
	WORD RemoteAppId = 0;		// Id da aplicacao do Client remoto
	WORD RemoteAppType = 0;	// Tipo do Client remoto
	int iRet = 0;
	int DataSize = 0;
	int TxBufferSize = 0;
	char *pTxBuffer = NULL;
	char tmpHandle[20];
	CStdString sTemp;

	try
	{
		CriticalSection::Scope scope(&CritSocket);

		if( !bConnected )
			return -1;

		if( _Socket <= 0 )
			return -1;

		DataSize = strlen(sData);
		
		TxBufferSize = HEADER_SIZE + DataSize;

		pTxBuffer = (char *) malloc( TxBufferSize + 1 );

		if( pTxBuffer == NULL )
		{
			// Erro: memoria insuficiente
			Log(LOG_ERROR, "tcp_ip::Send() - NOT ENOUGH MEMORY");
			return -1;
		}

		if( sHandle == NULL )
			strcpy(tmpHandle, "0000000000");
		else
			if( strlen( sHandle) > MAX_PACKET_HANDLE )
				strcpy(tmpHandle, "0000000000");
			else
				strcpy(tmpHandle, sHandle);

		MakePacket(Id, RemoteId, tmpHandle, (char *)sData, DataSize, pTxBuffer);

		iRet = pSocket->Send( _Socket, pTxBuffer, TxBufferSize, TCP_TIME_OUT_SEND );

		if( iRet == 0 )
		{
			free( pTxBuffer );
			// Timeout ao esperar o socket ficar pronto para enviar
			Log(LOG_ERROR, "ERROR: TcpIp_Send() - Timeout on send data");
			return -1;
		}
		if( iRet == SOCKET_ERROR )
		{
			pSocket->CloseSocket( _Socket );
			_Socket = 0;
			free( pTxBuffer );
			// erro de conexao com o socket
			Log(LOG_ERROR, "ERROR: TcpIp_Send() - socket error");
			return -1;
		}
		// verifica se o nivel de log esta ativado, para evitar muitas operacoes nessa chamada
		if( pLog->CheckLevel(LOG_TCP_IP) )
		{
			RemoteAppId		= LOWORD(RemoteId);
			RemoteAppType = HIWORD(RemoteId);

			//[17_05_2010<]
			sTemp.Format("SEND TYPE %d ID %d ", RemoteAppType, RemoteAppId);
			sTemp += sData; 
			Log(LOG_TCP_IP, sTemp.c_str());
			//[17_05_2010>]
		}

		free( pTxBuffer );
		return 0;
	}
	catch(...)					 
	{
		if( pTxBuffer != NULL )
			free( pTxBuffer );

		Log(LOG_ERROR, "EXCEPTION: tcp_ip::Send()");
		return -1;
	}
}
//[4167>]

//------------------------------------------------------------------------------------------------------------------------

int tcp_ip::SendHello(void)
{
	int iRet;
	//[4167<]
	char TxBuf[1024];
	//[4167>]

	try
	{
		// Id da aplicacao
		IdApp			= Application::IdApp;
		// Tipo da aplicacao
		IdTypeApp	= Application::IdTypeApp;

		// Id desse Client
		Id = MAKELONG(IdApp, IdTypeApp);

		// Monta o pacote de HELLO
		MakePacket(Id, VOS_PROXY_ID, "0000000000", "HELLO", 5, TxBuf);

		Log(LOG_TCP_IP, "[SEND] TYPE:1 ID:1 - HELLO");

		// No server nao precisa de secao critica pois o socket ainda so pertence a ele 
		iRet = pSocket->Send( _Socket, TxBuf, 5 + HEADER_SIZE, TCP_TIME_OUT_SEND);

		if( iRet == 0 ){
			// Timeout ao esperar o socket ficar pronto para enviar
			Log(LOG_ERROR, "ERROR: tcp_ip::SendPacket() - Timeout on send data");
			return -1;
		}
		if( iRet == -1 ){
			// erro de conexao com o socket
			Log(LOG_ERROR, "ERROR: tcp_ip::SendPacket() - socket error");
			return -1;
		}

		return 0;
	}
	catch(...)					 
	{
		Log(LOG_ERROR, "EXCEPTION: tcp_ip::SendHello()");
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

void tcp_ip::MakePacket(DWORD SourceId, DWORD DestId, const char *pHandle, char *pData, int iDataLen, char *pBuffer)
{
  try {

		Size = ( HEADER_SIZE - 3) + iDataLen;

		UnionHeader.StHeader.StartOfHeader	=	SOH;
		UnionHeader.StHeader.PacketSize			=	(WORD)Size;
		UnionHeader.StHeader.SourceId				=	SourceId;
		UnionHeader.StHeader.DestId					=	DestId; 

		memset(UnionHeader.StHeader.Handle, 0, sizeof(UnionHeader.StHeader.Handle));
		strncpy(UnionHeader.StHeader.Handle,  pHandle, 10);
		
		UnionHeader.StHeader.DataStart			=	START_OF_DATA;

		memcpy(pBuffer, UnionHeader.sHeader, HEADER_SIZE);
		memcpy(pBuffer+HEADER_SIZE, pData, iDataLen);

		pBuffer[iDataLen+HEADER_SIZE] = 0;
  }
  catch(...)
  {
		Log(LOG_ERROR, "EXCEPTION tcp_ip::MakePacket()");
	}
}

//DWORD UInt32
//WORD UInt16 
// 1   2          4        4      10     1  
// -----------------------------------------------
// SOH PACKETSIZE SOURCEID DESTID HANDLE DATASTART
// -----------------------------------------------

//------------------------------------------------------------------------------------------------------------------------

int tcp_ip::GetPacket(char *sData, int index, int iNumBytes, int &iBegin, int &iEnd)
{
  try {

		int i, pos;

		for(i = index; i < iNumBytes; ++i){

			if( sData[i] != SOH ){
				continue;
			}

			// Achou o SOH, verifica se possui dados suficientes para analisar o Header
			if( (iNumBytes - i) < HEADER_SIZE ){
				// Os dados ainda nao possuem o cabecalho inteiro
				iBegin	= i;
				iEnd		= iNumBytes;
				return PACKET_NEED_DATA;
			}

			// Verifica se pode encontrar o START_OF_DATA no cabecalho
			pos = i + (HEADER_SIZE - 1);

			if( sData[ pos ] != START_OF_DATA ){
				// Nao consegui encontrar o START_OF_DATA, recomeca a analise na proxima
				// posicao depois do SOH encontrado
				continue;
			}

			// Obtem o tamanho do pacote
			bLow	= sData[i+1];
			bHigh = sData[i+2];

			iPacketSize = MAKEWORD(bLow, bHigh);

			// Verifica se tem todos os dados de acordo com o tamanho do pacote
			// comecando no byte posterior aos dois bytes que guardam o tamanho do pacote

			if( (iNumBytes - (i+3)) >= iPacketSize ){
				// Retorna o posicao inicial e final do buffer com um pacote valido
				iBegin	= i;
				iEnd		= i + 3 + iPacketSize;
				return PACKET_OK;
			}
			else{
				// O pacote eh valido, mas precisa de mais dados
				iBegin	= i;
				iEnd		= iNumBytes;
				return PACKET_NEED_DATA;
			}
		}

		// Nao existe nenhum pacote nos dados passados, eles devem ser descartados
		return PACKET_NO_SOH;
  }
  catch(...)
  {
		Log(LOG_ERROR, "EXCEPTION tcp_ip::GetPacket()");
		return PACKET_ERROR;
	}
}

//------------------------------------------------------------------------------------------------------------------------

//[17_05_2010<]
void tcp_ip::Log(int level, const char *s)
{
	try
	{
		if( Register::LogLevel != iLogLevel )
		{
			// Atualiza o nivel de log
			iLogLevel = Register::LogLevel;
			pLog->SetLevel(iLogLevel);
		}

		pLog->Log(level, s);
	}
	catch(...)
	{
	}
}
//[17_05_2010>]

//---------------------------------------------------------------------------------------------

int tcp_ip::GetData(char *cCommand)
{
  CStdString check, strToFind;
  int pos_ini, pos_fim;
	char cValue[256];

  try {

		strToFind = cCommand;
		strToFind += "=";

		pos_ini = pacote.Data.find(strToFind.c_str(), 0);
		
		if( pos_ini == -1 ){
			strcpy(cValue, "");
			return -1;
		}

		if( pos_ini > 1 ){

			check = pacote.Data.at( pos_ini - 1 );

			while( check != "&" ){

				pos_ini = pacote.Data.find(strToFind.c_str(), pos_ini + 1);
				
				if( pos_ini == -1 ){
					return 0;
				}

				check = pacote.Data.at( pos_ini - 1 );
			}
		}

		pos_ini += (strlen(strToFind.c_str()));
		pos_fim = pacote.Data.find("&", pos_ini);

		// Retorna o valor de acordo com o tipo
		strncpy(cValue, pacote.Data.substr(pos_ini, pos_fim-pos_ini).c_str(), sizeof(cValue)-1);

		return atoi(cValue);
	}
	catch(...)
	{
		Log(0, "EXCEPTION: tcp_ip::GetData(const char *datapacket, char *cCommand, char *cValue, int valuesize)");
		return 0;
	}
}

//---------------------------------------------------------------------------------------------

int tcp_ip::GetData(char *cCommand, CStdString &sValue)
{
  CStdString check, strToFind;
  int pos_ini, pos_fim;

  try {

		strToFind = cCommand;
		strToFind += "=";

		pos_ini = pacote.Data.find(strToFind.c_str(), 0);
		
		if( pos_ini == -1 ){
			sValue= "";
			return -1;
		}

		if( pos_ini > 1 ){

			check = pacote.Data.at( pos_ini - 1 );

			while( check != "&" ){

				pos_ini = pacote.Data.find(strToFind.c_str(), pos_ini + 1);
				
				if( pos_ini == -1 ){
					sValue= "";
					return -1;
				}

				check = pacote.Data.at( pos_ini - 1 );
			}
		}

		pos_ini += (strlen(strToFind.c_str()));
		pos_fim = pacote.Data.find("&", pos_ini);

		// Retorna o valor de acordo com o tipo
		sValue = pacote.Data.substr(pos_ini, pos_fim-pos_ini).c_str();

		return 0;
	}
	catch(...)
	{
		sValue= "";
		Log(0, "EXCEPTION: tcp_ip::GetData(const char *datapacket, char *cCommand, CStdString &sValue)");
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

bool tcp_ip::Connected(void)
{
	return bConnected;
}

//------------------------------------------------------------------------------------------------------------------------

void tcp_ip::Action(CStdString sAction)
{
	try {
    ST_ACTION * actionData;
    ActionRoutineEntryPoint actionRoutine;
    MapStringToPtr::iterator itAction;

    itAction = actionArray.find( sAction.c_str() );
    if ( itAction == actionArray.end() )
    {
      itAction = actionArray.find( std::string("ERROR") );
    }

    actionData = (ST_ACTION *)itAction->second;
    actionRoutine = actionData->routine;

    if ( actionData->instance != NULL ) 
    {
      (*actionRoutine)( &pacote, (LPVOID)actionData->instance );
    }

    return;
	}
	catch(...)
	{
		Application::Log(0, "EXCEPTION: tcp_ip::Action()");
	}
}

//------------------------------------------------------------------------------------------------------------------------

int tcp_ip::RegisterAction( CStdString sAction, ActionRoutineEntryPoint routine, void * instance )
{
  try
  {
    ST_ACTION * action = new ST_ACTION();
    action->instance = instance;
    action->routine = routine;

    actionArray.insert( MapStringToPtr::value_type(sAction, action) );
    return actionArray.size();
  }
  catch(...)
  {
    Application::Log(LOG_ERROR, "EXCEPTION: tcp_ip::RegisterAction()");
    return -1;
  }
}

//------------------------------------------------------------------------------------------------------------------------

void tcp_ip::ActionHelloEntryPoint( ST_PACKET* pacote , LPVOID lparam )
{
  try
  {
    ((tcp_ip*)lparam)->ActionHello( pacote );
  }
  catch(...)
  {
    Application::Log(LOG_ERROR, "EXCEPTION: tcp_ip::ActionHelloEntryPoint()");
  }
}

//------------------------------------------------------------------------------------------------------------------------

void tcp_ip::ActionHello( ST_PACKET* pacote )
{
  try
  {
    bConnected = true;
  }
  catch(...)
  {
    Application::Log(LOG_ERROR, "EXCEPTION: tcp_ip::ActionHello()");
  }
  return;
}

//------------------------------------------------------------------------------------------------------------------------
