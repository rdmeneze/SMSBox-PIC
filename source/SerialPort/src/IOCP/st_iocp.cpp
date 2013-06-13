
#include "st_iocp.h"
#include "UniqueCount.h"

MapWordToPtr IOCP::iocp;

//------------------------------------------------------------------------------------------------------------------------

int IOCP::Create(void)
{
  int iHandle;
  HANDLE hnd;

  hnd = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
  if ( hnd == NULL )
  {
    return -1;
  }

  iHandle = UniqueCount :: GetUniqueCount();
  iocp.insert( MapWordToPtr::value_type( iHandle, hnd ) );

  return iHandle;
}

//------------------------------------------------------------------------------------------------------------------------

void  IOCP::Remove( int id )
{
  MapWordToPtr::iterator itIOCP;
  HANDLE hIOCP;

  itIOCP = iocp.find( id );
  if ( itIOCP == iocp.end() )
  {
    return;
  }  

  hIOCP = (HANDLE)itIOCP->second;
  iocp.erase( itIOCP );

  CloseHandle( hIOCP );
}

//------------------------------------------------------------------------------------------------------------------------

void* IOCP::Wait(int id, int time)
{
	BOOL bSuccess = FALSE;
	LPOVERLAPPED lpOverlapped;
  DWORD dwIoSize;
	void *info = NULL;
  MapWordToPtr::iterator itIOCP;

  itIOCP = iocp.find( id );
  if ( itIOCP == iocp.end() )
  {
    return NULL;
  }

  if( GetQueuedCompletionStatus(itIOCP->second, &dwIoSize, (LPDWORD)&info, &lpOverlapped, time) == 0 )
		return NULL;

	return info;
}

//------------------------------------------------------------------------------------------------------------------------

bool IOCP::Send(int id, void * source)
{
  MapWordToPtr::iterator itIOCP;

  itIOCP = iocp.find( id );
  if ( itIOCP == iocp.end() )
  {
    return false;
  }

  if( PostQueuedCompletionStatus(itIOCP->second, sizeof( source ), (DWORD)source, NULL) == 0 )
	{
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------------------------------------------------
