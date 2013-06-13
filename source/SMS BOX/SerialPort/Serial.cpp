
// $Id: Serial.cpp,v 1.1 2009/12/14 19:57:28 Antonio Exp $

#if __MSDEV
    #include "stdafx.h"
#endif
#include "Serial.h"

using namespace network;

#ifndef SecureZeroMemory
  #define SecureZeroMemory( x, y ) memset( x, 0, y)
#endif

//-----------------------------------------------------------------------------------------------------------------------------------------------------

HANDLE CSerial::hDispatchThread = NULL;
HANDLE CSerial::hListenerThread = NULL;

//-----------------------------------------------------------------------------------------------------------------------------------------------------

CSerial::CSerial()
{
  hPort   = NULL;
  return;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

CSerial::~CSerial( ) 
{
  if ( hPort != NULL )
  {
    CloseHandle( hPort );
    hPort = NULL;
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

int CSerial::Open(const char *device)
{
	hPort = CreateFile( (LPCTSTR)device, 
                      GENERIC_READ | GENERIC_WRITE, 
                      0, 
                      NULL, 
                      OPEN_EXISTING, 
                      0/*FILE_FLAG_OVERLAPPED*/,
                      NULL );

	if( hPort == INVALID_HANDLE_VALUE )
	{
		return ::GetLastError();
	}

	// Seta os valores default para a porta
	SetBaudRate( 9600 );
	SetStopBits( 1 );
	SetByteSize( 8 );
	SetParity(NOPARITY);
	SetHandshaking(HAND_SHAKE_OFF);
	SetTimeouts();

  if ( hDispatchThread == NULL )
  {
    hDispatchThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)CSerial::ThreadDispatch, this, 0, NULL );
    if ( hDispatchThread == NULL )
    {
      return ::GetLastError();
    }
  }

  if ( hListenerThread == NULL )
  {
    hListenerThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)CSerial::ThreadStartSerialPortListener, this, 0, NULL );
    if ( hListenerThread == NULL )
    {
      return ::GetLastError();
    }
  }

  return ERROR_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

void CSerial::Close()
{
	if( hPort != NULL )
	{
		CloseHandle( hPort );
		hPort = NULL;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

DWORD CSerial::SetHandshaking(EnumSerialHandshake SerialHandshake)
{
	// Obtem os parametros default da porta serial aberta
	SecureZeroMemory(&dcb, sizeof(DCB));
	
	dcb.DCBlength = sizeof(DCB);

	if( !GetCommState(hPort, &dcb) )
	{
    return ::GetLastError();
	}

	switch( SerialHandshake )
	{
		case HAND_SHAKE_OFF:
			dcb.fOutxCtsFlow	= false;									// Disable CTS monitoring
			dcb.fOutxDsrFlow	= false;									// Disable DSR monitoring
			dcb.fDtrControl		=	DTR_CONTROL_DISABLE;		// Disable DTR monitoring
			dcb.fOutX					=	false;									// Disable XON/XOFF for transmission
			dcb.fInX					=	false;									// Disable XON/XOFF for receiving
			dcb.fRtsControl		=	RTS_CONTROL_DISABLE;		// Disable RTS (Ready To Send)
		break;

		case HAND_SHAKE_HARDWARE:
			dcb.fOutxCtsFlow	= true;										// Enable CTS monitoring
			dcb.fOutxDsrFlow	= true;										// Enable DSR monitoring
			dcb.fDtrControl		= DTR_CONTROL_HANDSHAKE;	// Enable DTR handshaking
			dcb.fOutX					=	false;									// Disable XON/XOFF for transmission
			dcb.fInX					=	false;									// Disable XON/XOFF for receiving
			dcb.fRtsControl		=	RTS_CONTROL_HANDSHAKE;	// Enable RTS handshaking
		break;

		case HAND_SHAKE_SOFTWARE:
			dcb.fOutxCtsFlow	=	false;									// Disable CTS (Clear To Send)
			dcb.fOutxDsrFlow	=	false;									// Disable DSR (Data Set Ready)
			dcb.fDtrControl		=	DTR_CONTROL_DISABLE;		// Disable DTR (Data Terminal Ready)
			dcb.fOutX					=	true;										// Enable XON/XOFF for transmission
			dcb.fInX					=	true;										// Enable XON/XOFF for receiving
			dcb.fRtsControl		=	RTS_CONTROL_DISABLE;		// Disable RTS (Ready To Send)
		break;
	}

	if( !SetCommState(hPort, &dcb) )
	{
    return ::GetLastError();
	}
	
  return ERROR_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

DWORD CSerial::SetBaudRate(int baud_rate)
{
	// Obtem os parametros default da porta serial aberta
	SecureZeroMemory(&dcb, sizeof(DCB));

	dcb.DCBlength = sizeof(DCB);

	if( !GetCommState(hPort, &dcb) )
		return GetLastError();

	switch( baud_rate )
	{
		case CBR_110:
		case CBR_300:
		case CBR_600:
		case CBR_1200:
		case CBR_2400:
		case CBR_4800:
		case CBR_9600:
		case CBR_14400:
		case CBR_19200:
		case CBR_38400:
		case CBR_56000:
		case CBR_57600:
		case CBR_115200:
		case CBR_128000:
		case CBR_256000:
			dcb.BaudRate = DWORD(baud_rate);
		break;

		default:
			return ERROR_BAD_COMMAND;
	}

  if( !SetCommState(hPort, &dcb) )
  {
    return GetLastError();
  }

	return ERROR_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

DWORD CSerial::SetStopBits(int stop_bits)
{
	// Obtem os parametros default da porta serial aberta
	SecureZeroMemory(&dcb, sizeof(DCB));

	dcb.DCBlength = sizeof(DCB);

	if( !GetCommState(hPort, &dcb) )
		return ::GetLastError();

	switch( stop_bits )
	{
		case ONESTOPBIT:		// 1 stopbit (default)
		case ONE5STOPBITS:	// 1.5 stopbit
		case TWOSTOPBITS:		// 2 stopbits
			dcb.StopBits = BYTE(stop_bits);
		break;

		default:
			return ERROR_BAD_COMMAND;
	}

	if( !SetCommState(hPort, &dcb) )
    return ::GetLastError();

	return ERROR_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

DWORD CSerial::SetParity(int parity)
{
	// Obtem os parametros default da porta serial aberta
	SecureZeroMemory(&dcb, sizeof(DCB));

	dcb.DCBlength = sizeof(DCB);

	if( !GetCommState(hPort, &dcb) )
    return ::GetLastError();

	switch( parity )
	{
		case NOPARITY:		// No parity (default)
		case ODDPARITY:		// Odd parity
		case EVENPARITY:	// Even parity
		case MARKPARITY:	// Mark parity
		case SPACEPARITY:	// Space parity
			dcb.Parity = BYTE(parity);
		break;

		default:
      return ERROR_BAD_COMMAND;
	}

	if( !SetCommState(hPort, &dcb) )
    return ::GetLastError();

  return ERROR_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

DWORD CSerial::SetByteSize(int byte_size)
{
	// Obtem os parametros default da porta serial aberta
	SecureZeroMemory(&dcb, sizeof(DCB));

	dcb.DCBlength = sizeof(DCB);

	if( !GetCommState(hPort, &dcb) )
    return ::GetLastError();

	switch( byte_size )
	{
		case 5:	// 5 bits per byte
		case 6:	// 6 bits per byte
		case 7:	// 7 bits per byte
		case 8:	// 8 bits per byte (default)
			dcb.ByteSize = BYTE(byte_size);
		break;

		default:
      return ERROR_BAD_COMMAND;
	}

	if( !SetCommState(hPort, &dcb) )
		return -1;

  return ERROR_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

void CSerial::SetTimeouts()
{
	COMMTIMEOUTS cto;

	cto.ReadIntervalTimeout					=	MAXWORD;
	cto.ReadTotalTimeoutMultiplier	=	0;
	cto.ReadTotalTimeoutConstant		=	1;
	cto.WriteTotalTimeoutMultiplier	=	0;
	cto.WriteTotalTimeoutConstant		=	0;

	SetCommTimeouts(hPort, &cto);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

//int CSerial::Read(char *s, int len)
//{
//	DWORD read = 0;
//
//	if( !ReadFile(hPort, (char *)s, len, &read, 0) )
//	{
//		return 0;
//	}
//	
//	return read;
//}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

int CSerial::Write(char *s, int len)
{
	DWORD wrote = 0;

	if( !WriteFile(hPort, (char *)s, len, &wrote, 0) )
	{
		return 0;
	}
	
	return wrote;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

int CSerial::Write(char *s, int len, int delay)
{
	DWORD wrote = 0;
	char temp[2];
	int i;

	for(i = 0; i < len; i++)
	{
		Sleep(delay);

		temp[0] = s[i];
		temp[1] = 0;

		if( !WriteFile(hPort, (char *)temp, 1, &wrote, 0) )
		{
			return 0;
		}
	}
	
	return len;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

DWORD CSerial::SerialPortListener( void )
{
  DWORD rxEvnt;
  DWORD dwRet;
  DWORD dwBytesRead;
  BYTE * pBuffer;
  const int bufferLen = (1024 * 4);

  ov.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
  ov.Internal = 0;
  ov.InternalHigh = 0;
  ov.Offset = 0;
  ov.OffsetHigh = 0;
  
  if ( ov.hEvent == NULL )
  {
    return ::GetLastError();
  }

  // configura o evento a ser recebido
  if ( SetCommMask( hPort, (DWORD)EV_RXCHAR ) )
  {
    return ::GetLastError();
  }

  for(;;)
  {
    if ( WaitCommEvent( hPort, &rxEvnt, &ov ) == 0 )
    {
      dwRet = GetLastError();
      if( dwRet == ERROR_IO_PENDING)
      {
        continue;
      }
    }

    if ( rxEvnt & EV_RXCHAR )
    {
      pBuffer = new BYTE [ bufferLen + 1 ];
      if ( pBuffer == NULL )
      {
        continue;
      }
      
      dwRet = ReadFile( hPort, (LPVOID)pBuffer, bufferLen, &dwBytesRead, &ov );

      if ( !dwRet )
      {
        dwRet = ::GetLastError();
        delete pBuffer;
        continue;
      }

      // realiza o processamento dos dados recebidos
      //if ( process )
      //{
      //  if ( dwBytesRead )
      //  {
      //    (this->*process)( pBuffer, dwBytesRead );
      // }
      //}

      delete pBuffer;
    }
  }

  return ERROR_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSerial::ThreadStartSerialPortListener( LPVOID lpParam )
{
  CSerial * serial;
  
  serial = (CSerial*)lpParam;

  serial->SerialPortListener( );

  return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

DWORD CSerial::Dispatch( void )
{
  BOOL bRet;
  MSG msg; 

  while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
  { 
    TranslateMessage(&msg); 
    DispatchMessage(&msg); 
  }

  return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSerial::ThreadDispatch( LPVOID lpParam )
{
  CSerial * serial;

  try{
    serial = (CSerial*)lpParam;

    return serial->Dispatch( );
  }
  catch(...)
  {
    return -1;
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

