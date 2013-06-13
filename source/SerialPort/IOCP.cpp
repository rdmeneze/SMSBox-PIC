#include "stdafx.h"
#include "IOCP.h"

//std::map<int, HANDLE > IOCP::MAPHANDLE;

IOCP::IOCP( void ) 
{
  HANDLE hIOCP = ::CreateIoCompletionPort( NULL, 0, NULL, 0 );
  if ( hIOCP == NULL )
  {
    throw( ::GetLastError() );
  }
}

int IOCP::GetID( void )
{
  return 0;
}

void* IOCP::Wait( int iTime )
{
  return NULL;
}

int IOCP::Send( void* data )
{
  return 0;
}

IOCP::~IOCP( void )
{
}
