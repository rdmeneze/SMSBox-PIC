
#ifndef tcp_ip_h
	#define tcp_ip_h

//#include "packet.h"
#include <windows.h>
//#include "LuaRemote.h"
#include "Winsocketclass.h"
#include "tcp_ip_interface.h"
#include "TCP_IOCP.h"
#include "types.h"

#include <map>

using namespace std;

// Mensagem de janela para os eventos de socket tcp/ip
#define	WM_TCP								(WM_APP + 1000)

//[29_12_2008<]
// Tamanho do buffer de recepcao e transmissao TCP_IP
#define	TCP_BUFFER_SIZE				(1024 * 64)
// Tempo maximo para enviar dados via tcp/ip em segundos
#define	TCP_TIME_OUT_SEND			10
//[29_12_2008>]

// Tempo maximo para verificar se o socket possui dados para ler em segundos
#define	TCP_TIME_OUT_SELECT		15

//--------------------------------------------------------------------------

class tcp_ip : public tcp_ip_interface {

	private:

		// Objeto de secao critica para operacoes no socket
		CriticalSection CritSocket;
		// Id do Client remoto
		DWORD RemoteId;
		// Id da aplicacao do Client remoto
		WORD RemoteAppId;
		// Tipo do Client remoto
		WORD RemoteAppType;
		// Id desse Client
		DWORD Id;
		// Id da aplicacao
		WORD IdApp;
		// Tipo da aplicacao
		WORD IdTypeApp;
		// Uniao para copiar os dados do cabecalho do pacote
		UNION_HEADER UnionHeader;
		// Variavel para uso geral
		DWORD Size;
		// Nivel de log
		int iLogLevel;
		// Tamanho do buffer de recepcao;
		int iRecvBufSize;
		// Posicao do buffer de recepcao a partir da qual sera feita a analise dos pacotes
		int iRecvBufIndex;
		// Tamanho atual com dados validos do buffer de recepcao
		int iRecvBufActualSize;
		// Posicao a partir da qual os dados serao lidos do buffer tcp
		int iRecvBufPos;
		// Tamanho do pacote
		int iPacketSize;
		// Usada para ler o tamanho do pacote
		BYTE bLow;
		// Usada para ler o tamanho do pacote
		BYTE bHigh;
		// Estrutura do pacote
		ST_PACKET pacote;
		// Acao recebida pelo TcpIp que define a funcao a ser chamda
		//CStdString sAction;
		// Estrutura de dados para comunicacao entre as threads
		TCP_IOCP st_iocp;
		// Endereco do Router IP
		char Host[256];

		//[4167<]
		// Buffer de recepcao
		char *RecvBuf;
		// Tamanho do buffer temporario de recepcao
		int iTmpBufSize;
		// Tamanho atual do temporario buffer de recepcao
		int iTmpBufActualSize;
		// Buffer temporario para receber dados do socket
		char tmpBuf[TCP_BUFFER_SIZE+1];
		//[4167>]

		// Porta para conectar
		unsigned short Port;
		// Ponteiro para a classe WinSocketClass para a comunicacao TcpIp
		WinSocketClass *pSocket;
		// ponteiro para a classe log  
		LogFile *pLog;
		// Socket Client
		int _Socket;
		// Indica o estado da conexao tcp/ip
		bool bConnected;

		// Envia pacote de Hello no inicio da conexao
		int SendHello(void);
		// Le os dados do buffer de recepcao tcp/ip
		void Read(void);
		// Fecha o socket corrente e tenta reconectar
		void Close(int errorcode = 0);
		// Verifica se existe um pacote no buffer
		void CheckPacket(int iBegin, int iEnd);
		// Obtem um pacote do buffer TCP_IP
		int GetPacket(char *sData, int index, int iNumBytes, int &iBegin, int &iEnd);
		// Monta um pacote para ser enviado
		void MakePacket(DWORD SourceId, DWORD DestId, const char *pHandle, char *pData, int iDataLen, char *pBuffer);
		// Conecta ao server e gerencia os dados
		int Connect(void);
		// Executa as acoes
		void Action(CStdString sAction);
		// Funcao de log
		//[17_05_2010<]
		void Log(int level, const char *s);
		//[17_05_2010>]
		// Envia dados
		int Send(DWORD RemoteId, const char *sData, const char *sHandle = NULL);
		// Obtem um dado do pacote recebido		
		int GetData(char *cCommand);
		// Obtem um dado do pacote recebido		
		int GetData(char *cCommand, CStdString &sValue);

    // ACTION=HELLO
    static void ActionHelloEntryPoint( ST_PACKET* pacote , LPVOID lparam );
    void ActionHello( ST_PACKET* pacote );

		// Funcao CallBaock para pegar eventos tcp/ip
		static LRESULT CALLBACK CallBack(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			// Thread de gerenciamento do objeto
		friend void ThreadProxyClient(void *param);
		// Funcao CallBack real onde os eventos TCP chegarao
		LRESULT CALLBACK VirtualCallBack(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    //!
    //MapStringAction actionArray;
    MapStringToPtr actionArray;

	public:

		// Contrutor
		tcp_ip(const char *sHostServer, unsigned short PortServer);
		~tcp_ip(){}
		// Returna true se a conexao com o VosProxy esta OK, false caso contrario
		bool Connected(void);
		// Fica pegando eventos de kanela
		void Dispatch(void);
		// Inicializa e conecta com o server
		void InitClient(void);

    //
    int RegisterAction( CStdString sAction, ActionRoutineEntryPoint routine, void * instance );
};

#endif
