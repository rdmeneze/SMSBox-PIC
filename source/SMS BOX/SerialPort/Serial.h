
// $Id: Serial.h,v 1.1 2009/12/14 19:57:28 Antonio Exp $

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <windows.h>

namespace network {

  //typedef void(SERIAL_PORT_CALLBACK)( BYTE*, DWORD );

  // Enum para controle do Handshake
  enum EnumSerialHandshake
  {
	  HAND_SHAKE_OFF			=	0,			// NO HANDSHAKING
	  HAND_SHAKE_HARDWARE	=	1,			// HARDWARE HANDSHAKING (RTS/CTS)
	  HAND_SHAKE_SOFTWARE	=	2,			// SOFTWARE HANDSHAKING (XON/XOFF)
  };

  class CSerial
  {
	  private:
      
      /**
       * \brief Handle para a porta serial
       */
      HANDLE hPort;

      static HANDLE hDispatchThread;
      static HANDLE hListenerThread;
      HANDLE hCompletionEvnt;

      //! Estrura para setar todos os parametros da porta serial
      DCB dcb;

		  //! Seta o valor default para timeout de leitura e escrita
		  void SetTimeouts();
      
      //! overlapped structure for use with the 
      OVERLAPPED ov;

      // 
      //SERIAL_PORT_CALLBACK  process;

      DWORD SerialPortListener( void );
      static DWORD WINAPI ThreadStartSerialPortListener( LPVOID lpParam );

      DWORD Dispatch( void );
      static DWORD WINAPI ThreadDispatch( LPVOID lpParam );

	  public:
      /**
       *  \brief Construtor
       */
      CSerial();
      /**
       *  \brief Destructor
       */
      virtual ~CSerial( );

      /**
       *  \brief Abre um device com base no nome do dispositivo COMM, exemplo: COM1
       */
		  int Open(const char *device);
      /**
       *  \brief Fecha a porta inicialmente aberta pelo objeto
       */
		  void Close();

      /**
       *  \brief  Seta os parametros basicos da porta serial
       *  \param  baud_rate baudrate do link de comunicação
       *  \return Estado da operação: <0: erro, caso contrário : Sucesso
       */
		  DWORD SetBaudRate(int baud_rate);

      /**
       *  \brief Configura as opções de stop bits
       *  \param stop_bits Numero de stop bits do lnk de comunicacao. Olhe em Winbase.h.
       *  \return Código de Erro. 
       */
		  DWORD SetStopBits(int stop_bits);

      /**
       *  \brief Configura as opções de paridade para o canal de comunicação
       *  \param parity Paridade do canal de comunicação. Olhe em Winbase.h.
       *  \return Código de Erro. 
       */
		  DWORD SetParity(int parity);
       
      /**
       *  \brief Configura o comprimento de dados usado na comunicação serial
       *  \param parity Paridade do canal de comunicação. Olhe em Winbase.h.
       *  \return Código de Erro. 
       */
		  DWORD SetByteSize(int byte_size);

      /**
       *  \brief Configura o tipo de handshake entre o host e o cliente
       *  \param SerialHandshake Tipo de protocolo de handshake utilizado. Olhe a estrutura EnumSerialHandshake.
       *  \return Código de Erro. 
       */
		  DWORD SetHandshaking(EnumSerialHandshake SerialHandshake);	

      ///**
      // *  \brief Le dados da porta COMM, retornando o tamanho do dado lido, se houver timeout ou nenhum dado retorna 0
      // */
		  //int Read(char *s, int len);

      
      /**
		   *  \brief Escreve dados na porta COMM, bloqueando ate que todos os dados sejam escritos, retorna o numero de dados
		   *         escritos ou 0 se ocorrer timeout
       */
		  int Write(char *s, int len);

      /**
		   *  \brief  Escreve dados na porta COMM, bloqueando ate que todos os dados sejam escritos, retorna o 
       *          numero de dados escritos ou 0 se ocorrer timeout, coloca um delay em milisegundos entre 
       *          cada caractere a ser transmitido    
       */
		  int Write(char *s, int len, int delay);

  };

};

#endif
