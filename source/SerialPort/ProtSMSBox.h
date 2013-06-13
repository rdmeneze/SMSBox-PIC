#include "stdafx.h"
#include "Serial.h"

#ifndef __PROT_SMSBOX__
#define __PROT_SMSBOX__

namespace smsbox{

  //--------------------------------------------------------------
  //   descrição e posição dos campos componentes do pacote enviado/recebido da SMS Box
  #define ED_FIELD    0   //! campo "endereço de destino"
  #define EO_FIELD    1   //! campo "endereço de origem"
  #define LEN_FIELD   2   //! campo "comprimento"
  #define DATA_FIELD  3   //! campo de dados
  #define CMD_FIELD   3   //! campo "comando"
  #define CMD_PARAM   (CMD_FIELD+1) //! campo "parâmetros do comando"
  //--------------------------------------------------------------
  #define BUFFER_DATA_LEN   255
  //--------------------------------------------------------------

  //! Estruturas de retorno dos comandos recebidos do SMS Box.
  //< estrutura de retorno para o comando HELLO
  struct ST_CMD_HELLO 
  {
    DWORD dwSerialNumber;   //! serial number da placa
  };

  //< estrutura de retorno para o comando de MODEM
  struct ST_CMD_MODEM
  {
    BYTE  bData[BUFFER_DATA_LEN];          //! buffer de dados
    BYTE  bDataLen;         //! comprimento do buffer de dados alocado
  };

  
  //< estrutura de retorno para o comando Active SIM Card
  struct ST_CMD_ASC 
  {
    BYTE  bStatus;          //! status de execução do comando
  };

  //< estrutura de retorno para o comando SONDA
  struct ST_CMD_SONDA
  {
  };

  //< estrutura de retorno para o comando STATUS
  struct ST_CMD_STATUS
  {
    WORD  wStatus;          //! status de retorno
  };

  //< estrutura de retorno para o comando DEV_SET_STATUS
  struct ST_CMD_DEV_SET_STATUS
  {
    BYTE  bDevID;           //! ID do dispositivo
    BYTE  bStatus;          //! status do dispositivo
  };

  //< estrutura de retorno para o comando DEV_GET_STATUS
  struct ST_CMD_DEV_GET_STATUS
  {
    BYTE  bDevID;           //! ID do dispositivo
    BYTE  bStatus;          //! status do dispositivo
  };

  //< estrutura de retorno para o comando GET_VERSION
  struct ST_CMD_GET_VERSION
  {
    DWORD dwFWVersion;      //! versão do firmware
    DWORD dwHWVersion;      //! versão do hardware
  };

  //< estrutura de retorno para o comando GET_VERSION
  struct ST_CMD_GET_LOG
  {
    BYTE  bLogType;         //! informa o tipo de log
    BYTE  bLogLen;          //! informa a quantidade de bytes
    WORD  wStamp;           //! contador de mensagem
    BYTE  bLogEvnt;         //! tipo de evento de log
    BYTE  bLogBuffer[BUFFER_DATA_LEN];  //! buffer de log de bLogLen bytes
  };


  //< estrutura de retorno para o comando SMSBOX_COMMAND
  struct SMSBOX_COMMAND
  {
    BYTE  bSize;            //! tamanho da estrutura
    BYTE  bType;            //! tipo de mensagem
    BYTE  bID;              //! ID do SMS Box que enviou o comando  
    union
    {
      struct ST_CMD_HELLO           Hello;
      struct ST_CMD_MODEM           ModemCMD;
      struct ST_CMD_ASC             ASC;
      struct ST_CMD_SONDA           Sonda;
      struct ST_CMD_STATUS          BoardStatus;
      struct ST_CMD_DEV_SET_STATUS  DevSetStatus;
      struct ST_CMD_DEV_GET_STATUS  DevGetStatus;
      struct ST_CMD_GET_VERSION     Version;
      struct ST_CMD_GET_LOG         Log;
    }Info;
  };

  //--------------------------------------------------------------

  #define SERVER_ID   0x00

  class CSMSBox {
  private:
    
    network::CSerial serial;

    BYTE bID;
    static BYTE bQuit;

    HANDLE hThreadDispatch;
    static DWORD WINAPI ThreadDispatch( LPVOID lpParam );
    DWORD Dispatch( void );

    HANDLE hThreadProcessaMensagens;
    static DWORD WINAPI ThreadProcessaMensagens( LPVOID lpParam );
    DWORD ProcessaMensagens( void );

    HANDLE hThreadProcessaPacotes;
    static DWORD WINAPI ThreadProcessaPacotes( LPVOID lpParam );
    void ProcessaPacotes( BYTE * pData, DWORD dwDataLen );

  public:

    CSMSBox( LPCSTR cPortName = NULL ) throw(...);

    BYTE Open( LPCSTR cPortName );

    BYTE IsOpen( void );

    /**
     *  \brief  Configura o ID do cliente SMS Box
     *  \param  ID do do cliente
     */
    void SetID( BYTE ID );

    /**
     *  \brief Captura o ID do cliente SMS Box
     *  \return ID do cliente
     */
    BYTE GetID( void );
  };

};


#endif //~ __PROT_SMSBOX__