
#ifndef PacketH
	#define PacketH

#include <windows.h>
#include "StdString.h"

#define SOH										0x01
#define START_OF_DATA					'?'
#define MAX_PACKET_HANDLE			10
#define HEADER_SIZE						22

enum PacketResults {

	PACKET_NO_SOH = 0,
	PACKET_NEED_DATA,
	PACKET_OK,
	PACKET_ERROR
};

//------------------------------------------------------------------------------------------------------------------------
// A estruta de pacote deve ter alinhamento 1
#pragma pack(1)

// 1   2          4        4      10     1  
// -----------------------------------------------
// SOH PACKETSIZE SOURCEID DESTID HANDLE DATASTART
// -----------------------------------------------

typedef struct
{
  // inicio do pacote - codigo 0x01
	char		StartOfHeader;
  // tamanho do pacote a partir de SourceId (inclusive)
	WORD		PacketSize;
  // identificacao da origem - 
  // 2 bytes mais significativos para tipo
  // 2 bytes menos significativos para identificacao
	DWORD		SourceId;
  // identificacao do destino
  // 2 bytes mais significativos para tipo
  // 2 bytes menos significativos para identificacao
	DWORD		DestId;
  // identficador da chamada
	char		Handle[MAX_PACKET_HANDLE];
  // inicio dos dados - '?'
	char		DataStart;

}ST_HEADER;

typedef union 
{
	ST_HEADER StHeader;
	char sHeader[ HEADER_SIZE ];
}UNION_HEADER;

typedef struct {
  //header do pacote
	ST_HEADER Header;
  //dados  do pacote
	CStdString Data;
}ST_PACKET;

#pragma pack()

#endif
//------------------------------------------------------------------------------------------------------------------------
