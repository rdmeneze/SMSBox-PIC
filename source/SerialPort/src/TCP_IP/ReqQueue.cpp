
#include "ReqQueue.h"
#include "st_iocp.h"

CriticalSection	ReqQueue::CritReq;
list<TCP_IOCP*>  ReqQueue::list_iocp;
list<int>				ReqQueue::list_threads;

//------------------------------------------------------------------------------------------------------------------------

bool ReqQueue::Push(TCP_IOCP *info)
{
	CStdString sAux;
	int id;

	try
	{
		//[25809<]
		CriticalSection::Scope scope( CritReq );
		//[25809>]

		// Verifica se existe uma thread LUA disponivel
		if( !list_threads.empty() )
		{
			id = list_threads.front();
			list_threads.pop_front();
			
			// Envia evento para a thread LUA correspondente
			if ( IOCP::Send( id, info ) == false )
			{
				return false;
			}
		}
		else
		{
			// Coloca a requisica na fila
			list_iocp.push_back( info );
		}
    
		return true;
	}
	catch(...)
	{
		return true;
	}
}

//------------------------------------------------------------------------------------------------------------------------

bool ReqQueue::Push(int id)
{
	CStdString sAux;
	TCP_IOCP* st_iocp;

	try
	{
		//[25809<]
		CriticalSection::Scope scope( CritReq );
		//[25809>]

		// Verifica se existe uma requisica pendente
		if( !list_iocp.empty() )
		{
			st_iocp = list_iocp.front();
			//list_iocp.pop_front();

			// Envia evento para a thread LUA correspondente
			if ( IOCP::Send( id, st_iocp ) == false )
			{
        list_iocp.pop_front();
        delete st_iocp;
				return false;
			}
      list_iocp.pop_front();
      delete st_iocp;
		}
		else
		{
			// Coloca a thread na fila de threads disponiveis
			list_threads.push_back( id );
		}

		sAux.Format("  Threads Availables [ %d ]          Requests Pending [ %d ]", list_threads.size(), list_iocp.size());
		
		return true;
	}
	catch(...)
	{
		return true;
	}
}

//------------------------------------------------------------------------------------------------------------------------

