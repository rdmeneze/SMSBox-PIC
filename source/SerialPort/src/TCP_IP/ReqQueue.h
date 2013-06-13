
#ifndef ReqQueueH
	#define ReqQueueH

#include <Windows.h>
#include <list>
#include "StdString.h"
#include "CriticalSection.h"
//#include "st_iocp.h"
#include "tcp_iocp.h"

using namespace std;

class ReqQueue {

	public:

		// Secao critica de controle das filas
		static CriticalSection CritReq;
		// Lista de requicoes tcp/ip
		static list<TCP_IOCP*>	list_iocp;
		// Lista de ids de threads de LUA
		static list<int>			list_threads;

		// Coloca na fila uma requisicao tcp/ip
		static bool Push(TCP_IOCP *info);
		// Coloca na fila uma thread de LUA disponivel
		static bool Push(int id);
};

#endif
