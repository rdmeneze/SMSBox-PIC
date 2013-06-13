#include "gps.h"
#include "serial.h"
#include "processor.h"
#include "ports.h"
#include "delay.h"
#include "funcoes.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//! define the max size of the gps data buffer
#define GPS_DATA_LEN  90
#define GPS_CMD_LEN   5

#define NMEA_INI_FRAME  '$'
#define NMEA_END_FRAME  '*'

//! receiver states
#define GPS_RX_ST     0
#define GPS_RX_PT_1   1
#define GPS_RX_PT_2   2
#define GPS_RX_PT_3   3
#define GPS_RX_PT_4   4
#define GPS_RX_PT_5   5
#define GPS_RX_DATA   6
#define GPS_RX_CS1    7
#define GPS_RX_CS2    10
#define GPS_RX_CR     8
#define GPS_RX_LF     9


#pragma udata  GPS_DATA
struct GPS_GGA gpsGGA; 
struct GPS_GSA gpsGSA;
struct GPS_GSV gpsGSV;
struct GPS_RMC gpsRMC;
struct GPS_VTG gpsVTG;
struct GPS_GLL gpsGLL;
BYTE *GPS_CONV[6];
BYTE *GPS_INDEX[6];
#pragma udata

const BYTE GPS_GGA_INDEX[] = {
  sizeof( DWORD ),   //DWORD utcTime;              	  
  sizeof( DWORD ),   //DWORD latitude;               
  sizeof( char  ),   //char  indNS;                  
  sizeof( DWORD ),   //DWORD longitude;              
  sizeof( char  ),   //char  indEW;                  
  sizeof( char  ),   //char  FixInd;                 
  sizeof( char  ),   //char  satelitesUsed;          
  sizeof( char  ),   //char  HDOP;                   
  sizeof( char  ),   //char  MSLAlt;                 
  sizeof( char  ),   //char  MSLUnit;                
  sizeof( char  ),   //char  GeoidSep;               
  sizeof( char  ),   //char  GeoidUnit;              
  sizeof( char  ),   //char  DiffCorr;               
  sizeof( char  )    //char  checksum;               
};

const BYTE GPS_GGA_CONV[] = {
  'N',   //DWORD utcTime;              	 
  'N',   //DWORD latitude;               
  'T',   //char  indNS;                  
  'N',   //DWORD longitude;              
  'T',   //char  indEW;                  
  'T',   //char  FixInd;                 
  'N',   //char  satelitesUsed;          
  'N',   //char  HDOP;                   
  'N',   //char  MSLAlt;                 
  'T',   //char  MSLUnit;                
  'N',   //char  GeoidSep;               
  'T',   //char  GeoidUnit;              
  'N',   //char  DiffCorr;               
  'N'    //char  checksum;               
};

const BYTE GPS_GLL_INDEX[]={
  sizeof( DWORD ),			// DWORD latitude; 	  
  sizeof( char  ),      // char  indNS;        
  sizeof( DWORD ),      // DWORD longitude;    
  sizeof( char  ),      // char  indEW;        
  sizeof( DWORD ),      // DWORD UTCPos;       
  sizeof( char 	),      // char status;        
  sizeof( char 	)       // char checksum;      
};                                          

const BYTE GPS_GLL_CONV[]={                         
  'N',      // DWORD latitude; 	      
  'T',      // char  indNS;        
  'N',      // DWORD longitude;    
  'T',      // char  indEW;        
  'N',      // DWORD UTCPos;       
  'T',      // char status;        
  'N'       // char checksum;      
};                                             

const BYTE GPS_GSA_INDEX[]={
  sizeof( char  ),      //  char  mode1;      
  sizeof( char  ),      //  char  mode2;      
  sizeof( BYTE  ),      //  BYTE  satUsed[0]; 
  sizeof( BYTE  ),      //  BYTE  satUsed[1]; 
  sizeof( BYTE  ),      //  BYTE  satUsed[2]; 
  sizeof( BYTE  ),      //  BYTE  satUsed[3]; 
  sizeof( BYTE  ),      //  BYTE  satUsed[4]; 
  sizeof( BYTE  ),      //  BYTE  satUsed[5];                     
  sizeof( BYTE  ),      //  BYTE  satUsed[6]; 
  sizeof( BYTE  ),      //  BYTE  satUsed[7]; 
  sizeof( BYTE  ),      //  BYTE  satUsed[8]; 
  sizeof( BYTE  ),      //  BYTE  satUsed[9]; 
  sizeof( BYTE  ),      //  BYTE  satUsed[10];
  sizeof( BYTE  ),      //  BYTE  satUsed[11];
  sizeof( BYTE  ),      //  BYTE  pdop;       
  sizeof( BYTE  ),      //  BYTE  hdop;       
  sizeof( BYTE  ),      //  BYTE  vdop;       
  sizeof( char  )       //  char  checksum;   
};

const BYTE GPS_GSA_CONV[]={                          
  'T',      //  char  mode1;        
  'T',      //  char  mode2;        
  'N',      //  BYTE  satUsed[0];   
  'N',      //  BYTE  satUsed[1];   
  'N',      //  BYTE  satUsed[2];   
  'N',      //  BYTE  satUsed[3];   
  'N',      //  BYTE  satUsed[4];   
  'N',      //  BYTE  satUsed[5];   
  'N',      //  BYTE  satUsed[6];   
  'N',      //  BYTE  satUsed[7];   
  'N',      //  BYTE  satUsed[8];   
  'N',      //  BYTE  satUsed[9];   
  'N',      //  BYTE  satUsed[10];  
  'N',      //  BYTE  satUsed[11];  
  'N',      //  BYTE  pdop;         
  'N',      //  BYTE  hdop;         
  'N',      //  BYTE  vdop;         
  'N'       //  char  checksum;     
};                                              

                                              
const BYTE GPS_RMC_INDEX[]={
  sizeof( DWORD ),      //  DWORD    utcTime;        
  sizeof( char  ),      //  char    status;          
  sizeof( DWORD ),      //  DWORD   latitude;        
  sizeof( char  ),      //  char    indNS;           
  sizeof( DWORD ),      //  DWORD   longitude;       
  sizeof( char  ),      //  char    indEW;           
  sizeof( int   ),      //  int     speedOverGround; 
  sizeof( int   ),      //  int     courseOverGround;
  6*sizeof( char  ),    //  char    date[6];         
  sizeof( char  ),      //  char    magVariation;    
  sizeof( char  )       //  char    checksum;        
};                                                 

const BYTE GPS_RMC_CONV[]={                               
  'N',      //  DWORD    utcTime;        
  'T',      //  char    status;          
  'N',      //  DWORD   latitude;        
  'T',      //  char    indNS;           
  'N',      //  DWORD   longitude;       
  'T',      //  char    indEW;           
  'N',      //  int     speedOverGround; 
  'N',      //  int     courseOverGround;
  'T',      //  char    date[6];         
  'T',      //  char    magVariation;    
  'N'       //  char    checksum;        
};                                                   



BYTE GPS_VTG_INDEX[]={
  sizeof( WORD  ),			//  WORD    course1;  
  sizeof( char  ),      //  char    ref1;     
  sizeof( WORD  ),      //  WORD    course2;  
  sizeof( char  ),      //  char    ref2;     
  sizeof( BYTE  ),      //  BYTE    speedy1;  
  sizeof( char  ),      //  char    unit1;    
  sizeof( BYTE  ),      //  BYTE    speedy2;  
  sizeof( char  ),      //  char    unit2;    
  sizeof( char  )       //  char    checksum; 
};                                            

const BYTE GPS_VTG_CONV[]={                        
  'N',			//  WORD    course1;     
  'T',      //  char    ref1;     
  'N',      //  WORD    course2;  
  'T',      //  char    ref2;     
  'N',      //  BYTE    speedy1;  
  'T',      //  char    unit1;    
  'N',      //  BYTE    speedy2;  
  'T',      //  char    unit2;    
  'N'       //  char    checksum;          
};                                                     


#define GPS_GGA_LEN GET_VEC_NUM_MEMBERS(GPS_GGA_INDEX)
#define GPS_GSA_LEN GET_VEC_NUM_MEMBERS(GPS_GSA_INDEX)

#define GPS_RMC_LEN GET_VEC_NUM_MEMBERS(GPS_RMC_INDEX)
#define GPS_VTG_LEN GET_VEC_NUM_MEMBERS(GPS_VTG_INDEX)
#define GPS_GLL_LEN GET_VEC_NUM_MEMBERS(GPS_GLL_INDEX)


BYTE GPS_STRUCT_LEN[] = {
  GPS_GGA_LEN,
  GPS_GSA_LEN,
  0,
  GPS_RMC_LEN,
  GPS_VTG_LEN,
  GPS_GLL_LEN,
};


  /*
  BYTE GPS_STRUCT_INDEX[]={
  GPS_GGA_INDEX,
  GPS_GSA_INDEX,
  0,
  GPS_RMC_INDEX,
  GPS_VTG_INDEX,
  GPS_GLL_INDEX,
};
*/



//! data buffer to GPS serial data
BYTE gpsDataBuffer[GPS_DATA_LEN];
char gpsTmpBuffer[GPS_DATA_LEN];
BYTE gpsDataCounter = 0;
BYTE gpsRXState     = GPS_RX_ST;
BYTE gpsMsgProc     = FALSE;
BYTE gpsCheckSum    = 0;
BYTE bCalcChecSum   = TRUE;
BYTE bRCVChecSum    = 0;



BYTE gpsFirst     = TRUE;     //! initialize GPS module
BYTE gpsDataReady = FALSE;		//! last data received is OK
BYTE gpsLastProt  = GPGGA; //! last proto received

//------------------------------------------------------------------

void GetStreamGPS( void );
void ParseBuffer( char * cGPSBuffer, void * lpGPSProto );

//------------------------------------------------------------------

void InitGPS ( void ){
  
  GPS_CONV[GPGGA] = GPS_GGA_CONV;
  GPS_CONV[GPGSA] = GPS_GSA_CONV;
  GPS_CONV[GPGSV] = NULL;
  GPS_CONV[GPRMC] = GPS_RMC_CONV;
  GPS_CONV[GPVTG] = GPS_VTG_CONV;
  GPS_CONV[GPGLL] = GPS_GLL_CONV;
  
  GPS_INDEX[GPGGA] = GPS_GGA_INDEX;
  GPS_INDEX[GPGSA] = GPS_GSA_INDEX;
  GPS_INDEX[GPGSV] = NULL;
  GPS_INDEX[GPRMC] = GPS_RMC_INDEX;
  GPS_INDEX[GPVTG] = GPS_VTG_INDEX;
  GPS_INDEX[GPGLL] = GPS_GLL_INDEX;
   
  gpsGGA.proto  = GPGGA;
  gpsGSA.proto  = GPGSA;
  gpsGSV.proto  = GPGSV;
  gpsRMC.proto  = GPRMC;
  gpsVTG.proto  = GPVTG;
  gpsGLL.proto  = GPGLL;
 
  gpsDataCounter  = 0;
  gpsDataReady    = FALSE;
  memset( (char*)gpsDataBuffer, 0, sizeof( gpsDataBuffer ));  
  GPS_RST_DIR = 0;
  GPS_RST     = 1;
  
  if ( gpsFirst == TRUE ){
    InitSerial( 0, BR_9600, ST_1, PR_NONE, GetStreamGPS );
  }
  return;
}
        
//------------------------------------------------------------------

void OpenGPS( void ){
	InitGPS( );
	return;  
}

//------------------------------------------------------------------

void CloseGPS( void ){
	gpsFirst = 1;
  return;
}

//------------------------------------------------------------------

void ResetGPS( void ){
  GPS_RST ^= 1;
  delay( 10 );
  GPS_RST ^= 1;
  return;
}

//------------------------------------------------------------------

void GetStreamGPS( void ){
  BYTE gpsData;
  BYTE bError = FALSE;
  
  gpsData = toupper( SerialGetchar() );

  switch( gpsRXState ){
    case GPS_RX_ST:
      if ( gpsData != NMEA_INI_FRAME ){
        bError = TRUE;
      }
      bCalcChecSum = FALSE;
      gpsRXState = GPS_RX_PT_1;
      break;
      
    case GPS_RX_PT_1:
      if ( gpsData != 'G' ){
        bError = TRUE;
      }
      bCalcChecSum = TRUE;
      gpsRXState = GPS_RX_PT_2;      
      break;
      
    case GPS_RX_PT_2:
      if ( gpsData != 'P' ){
        bError = TRUE;
      }
      gpsRXState = GPS_RX_PT_3;      
      break;
      
    case GPS_RX_PT_3:
      switch( gpsData ){
        case 'G':
        case 'R':
        case 'V':
          break;
        default:
          bError = TRUE;
      }
      
      gpsRXState = GPS_RX_PT_4;      
      break;
      
    case GPS_RX_PT_4:
    
      switch( gpsData ){
        case 'G':
        case 'S':
        case 'M':
        case 'T':
        case 'L':
          break;
        default:
          bError = TRUE;
      }
      
      gpsRXState = GPS_RX_PT_5;      
      break;
      
    case GPS_RX_PT_5:

      switch( gpsData ){
        case 'A':
        case 'V':
        case 'C':
        case 'G':
        case 'L':        
          break;
          
        default:
          bError = TRUE;
      }
    
      gpsRXState = GPS_RX_DATA; 
      break;
      
    case GPS_RX_DATA:
      if ( gpsData == NMEA_END_FRAME ){
        bCalcChecSum = FALSE;
        gpsRXState = GPS_RX_CS1;
      }
      else{
        gpsRXState = GPS_RX_DATA; 
      }
      break;
      
    case GPS_RX_CS1:
      bRCVChecSum = ascii2int( gpsData  ) << 4;
      gpsRXState = GPS_RX_CS2;
      break;
      
      
    case GPS_RX_CS2:
      bRCVChecSum += ascii2int( gpsData  );
      gpsRXState = GPS_RX_CR;
      break;


    case GPS_RX_CR:
      if ( gpsData != '\r' ){
        bError = TRUE;
      }
      else{
        gpsRXState = GPS_RX_LF;
        return;
      }
      break;
      

    case GPS_RX_LF:
      if ( gpsData != '\n' ){
        bError = TRUE;
      }
      else{
        gpsRXState      = GPS_RX_ST;
        //gpsDataCounter  = 0;        
        gpsMsgProc      = TRUE;
        return;
      }
      break;
      
    default:
      bError = TRUE;
  }

  if ( (bCalcChecSum == TRUE) && (bError == FALSE) ) {
    gpsCheckSum ^= gpsData ;
  }
  
  if ( gpsRXState == GPS_RX_CR ) {
    if ( gpsCheckSum != bRCVChecSum ){
      bError  = TRUE;
    }
    bRCVChecSum = 0;
    gpsCheckSum = 0;
  }  
  
  if ( bError  == TRUE ){
    gpsRXState      = GPS_RX_ST;
    gpsCheckSum     = 0;
    bRCVChecSum     = 0;
    gpsDataCounter  = 0;  
    gpsMsgProc      = FALSE;
  }
  else{  
    gpsDataBuffer[gpsDataCounter]  = gpsData;
    gpsDataCounter++;    
  }
  return;
}

//------------------------------------------------------------------

BYTE GPSProcessPackage( BYTE* proto, char** cBuffer ){
  BYTE bTmp;
  
  if( gpsMsgProc == FALSE ){
    return FALSE;
  }

  // determina qual é o protocolo corrente
  bTmp = GPGGA;
  
  if ( strncmppgm2ram( (char *)&gpsDataBuffer[1], "GPGGA" , GPS_CMD_LEN ) == 0 ){
    bTmp = GPGGA;
  }
  else if ( strncmppgm2ram( (char *)&gpsDataBuffer[1],"GPGSA" , GPS_CMD_LEN  ) == 0 ){
    bTmp = GPGSA;
  }
  else if ( strncmppgm2ram( (char *)&gpsDataBuffer[1],"GPGSV" , GPS_CMD_LEN  ) == 0 ){
    bTmp = GPGSV;
  }
  else if ( strncmppgm2ram( (char *)&gpsDataBuffer[1],"GPRMC" , GPS_CMD_LEN  ) == 0 ){
    bTmp = GPRMC;
  }
  else if ( strncmppgm2ram( (char *)&gpsDataBuffer[1],"GPVTG" , GPS_CMD_LEN  ) == 0 ){
    bTmp = GPVTG;
  }
  else if ( strncmppgm2ram( (char *)&gpsDataBuffer[1],"GPGLL" , GPS_CMD_LEN  ) == 0 ){
    bTmp = GPGLL;
  }
  else{
    gpsMsgProc = FALSE;
    gpsDataCounter = 0;
    return FALSE;
  }
  
  *proto =  bTmp;
  
  memcpy( (char*)gpsTmpBuffer, (const char*)&gpsDataBuffer[GPS_CMD_LEN+2], gpsDataCounter - GPS_CMD_LEN - 5 );
  gpsTmpBuffer[gpsDataCounter - GPS_CMD_LEN - 5] = ',';
  gpsTmpBuffer[gpsDataCounter - GPS_CMD_LEN - 4] = 0;
  
  *cBuffer = gpsTmpBuffer;
  gpsDataCounter = 0;
  
  return TRUE;
}

//------------------------------------------------------------------

BYTE GPSProcess( void ){
  BYTE gpsProtocol;
  BYTE btmp;
  char * gpsBuffer;  
  void * gpsProto = NULL;
  
  if ( GPSProcessPackage( &gpsProtocol, &gpsBuffer ) == FALSE ) {
    return -1;
  }
  
  switch( gpsProtocol ){
    case GPGGA: 
      gpsProto = (char*)&gpsGGA;
      break;
    case GPGSA: 
      gpsProto = (char*)&gpsGSA;
      break;
    case GPRMC: 
      gpsProto = (char*)&gpsRMC;
      break;
    case GPVTG: 
      gpsProto = (char*)&gpsVTG;   
      break;
    case GPGLL:
      gpsProto = (char*)&gpsGLL;    
      break;
    case GPGSV:     
      gpsProto = (char*)&gpsGSV;    
      break;
  }
  
  if ( gpsProto ){
    ParseBuffer( gpsBuffer, gpsProto );
  }
  
  return gpsProtocol;
}

//------------------------------------------------------------------

void ParseBuffer( char * cGPSBuffer, void * lpGPSProto ){
  BYTE proto;
  char cBuffer[16];
  char * pChar;
  char * pIni;
  char * pEnd;
  BYTE  i;
  BYTE  total;
  BYTE  iFieldLen;
 
  if ( lpGPSProto == NULL ){
    return;
  }

  // pega qual é a estrutura passada como parametro  
  //memcpy( (char*)&proto, (const char*)lpGPSProto, sizeof(char) );
  proto = *(char*)lpGPSProto;
  
  pIni = cGPSBuffer;
  pEnd = pIni;
  
  switch( proto ){
    case GPGGA:
    case GPGSA: 
    case GPRMC: 
    case GPVTG: 
    case GPGLL:
    
      total = 1;
      for ( i = 0; (i < GPS_STRUCT_LEN[proto]) && (pEnd != NULL); i++ ){
        iFieldLen = GPS_INDEX[proto][i];
        pEnd = strchr( pIni, ',' );
        if ( pEnd != NULL ){
          if ( GPS_CONV[proto][i] == 'T' ){
            memcpy( lpGPSProto + total, (const char*)pIni, (BYTE)(pEnd - pIni) );
          }
          else{
            if ( pIni != pEnd ){
              memset( cBuffer, 0, sizeof( cBuffer ));
              memcpy( cBuffer, (const char*)pIni, (BYTE)(pEnd - pIni) );
              
              switch( iFieldLen ){
                case sizeof( WORD ):
                  *(WORD*)(lpGPSProto + total) = atoi( cBuffer );
                  break;
                case sizeof( DWORD ):
                  *(WORD*)(lpGPSProto + total) = atol( cBuffer );
                  break;
                case sizeof( BYTE ):
                default:
                  *(char*)(lpGPSProto + total) = atoi( cBuffer );
                  break;
              }
            }
          }
        }
        pIni = pEnd+1;   
        total += iFieldLen;    
      }      
      break;
    
    case GPGSV:
      // tratamento diferenciado nesta situação
      break;
    
  }
  
  return;
}

//------------------------------------------------------------------
