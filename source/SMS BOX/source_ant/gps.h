#ifndef __GPS__
#define __GPS__

#include "defs.h"

typedef enum __GPSPROTO{
  GPGGA = 0, 
  GPGSA, 
  GPGSV, 
  GPRMC, 
  GPVTG, 
  GPGLL
} GPSProto;


struct GPS_GGA{
  BYTE  proto;
  DWORD utcTime;
  DWORD latitude;
  char  indNS; 
  DWORD longitude;
  char  indEW; 
  char  FixInd;
  char  satelitesUsed;
  char  HDOP;
  char  MSLAlt;
  char  MSLUnit;
  char  GeoidSep;
  char  GeoidUnit;
  char  DiffCorr;
  char  checksum;
};

struct GPS_GLL{
  BYTE  proto;
  DWORD latitude;
  char  indNS; 
  DWORD longitude;
  char  indEW; 
  DWORD UTCPos;
  char status;
  char checksum;
};

struct GPS_GSA{
  BYTE  proto;
  char  mode1;
  char  mode2;
  BYTE  satUsed[12];
  BYTE  pdop;
  BYTE  hdop;
  BYTE  vdop;
  char  checksum;
};


struct GPS_SAT{
  BYTE  satID;
  BYTE  elevation;
  BYTE  azimuth;
  BYTE    snr;
};

struct GPS_GSV{
  BYTE  proto;
  char    numberOfMsg;
  char    msgNumber;
  BYTE    satInView;
  struct GPS_SAT satellite[4];
  char    checksum;
};

struct GPS_RMC{
  BYTE  proto;
  //char    msgID[ 6 ];
  DWORD    utcTime;
  char    status;
  DWORD   latitude;
  char    indNS; 
  DWORD   longitude;
  char    indEW;   
  int     speedOverGround;
  int     courseOverGround;
  char    date[6];
  char    magVariation;
  char    checksum;
};

struct GPS_COURSE{
  WORD    course;
  char    ref;  
};

struct GPS_VELO{
  BYTE    speedy;
  char    unit;  
};

struct GPS_VTG{
  BYTE  proto;
  //char    msgID[ 6 ];
  struct  GPS_COURSE course1;
  struct  GPS_COURSE course2;
  struct  GPS_VELO  vel1;
  struct  GPS_VELO  vel2;
  char    checksum;
};

/**
 *  \brief Initialize the connection with the GPS module
 *  \sa InitSerial() and SERIALCOMM
 */
void InitGPS( void );

/**
 *  \brief Open the GPS connection
 */
void OpenGPS( void );

/**
 *  \brief Close the GPS connection
 */
void CloseGPS( void );

/**
 *  \brief  Reset the GPS hardware
 */
void ResetGPS( void );


/**
 *  \brief Do the processeing of NMEA packages
 */
BYTE GPSProcess( void );

#endif //~__GPS__
