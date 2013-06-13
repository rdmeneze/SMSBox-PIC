#ifndef __IOCP_H__
#define __IOCP_H__

#include <windows.h>
#include <map>

class IOCP
{
private:
  int iIOCP;

//  static std::map<int, HANDLE > MAPHANDLE;
public:
  IOCP( void );

  int GetID( void );

  void* Wait( int iTime );

  int Send( void* data );

  int Remove( );

  virtual ~IOCP( void );
};

#endif