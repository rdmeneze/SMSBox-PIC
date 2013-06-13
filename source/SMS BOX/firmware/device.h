/***
 * device
 * Módulo para controle de dispositivos conectados ao SMS Box. 
 * Dentre os dispositivos podemos englobar Modem GSM, GPIOs, etc.
 */

#ifndef __DEVICE__
#define __DEVICE__

#include "defs.h"

#define DEV_IN  0x80
#define DEV_OUT 0x00

#define DEV_HS  0x40    //! high speed device
#define DEV_LS  0x00    //! low speed device

#define DEV_TYPE_MASK 0x0F

//-----------------------------------------------------

#define GSM_PWR_KEY 0x01
#define CPU_RST     0x02

//-----------------------------------------------------

#define DEV_LIST_ST 27
#define DEV_GSM_PWR_KEY ( DEV_OUT | DEV_LS | GSM_PWR_KEY  )   // control the ON Off state of GSM Modem
#define DEV_CPU_RST     ( DEV_OUT | DEV_LS | CPU_RST      )   // reset the 
#define DEV_LIST_END  30

//-----------------------------------------------------

#define NDEV  ((DEV_LIST_END - DEV_LIST_ST) - 1 )

typedef enum {OFF = 0, 
              ON  = 1, 
              BUSY= 2} DEV_STATE;

typedef struct {
  BYTE ID;                //! device ID
  DEV_STATE bState;       //! Actual state of device (ON, OFF, BUSY) 
  DEV_STATE bNextState;   //! Future state of device (ON, OFF, BUSY). Used in slow devices
} CDevice;

typedef CDevice * CDevicePtr;

/**
 * \brief Initialize the device management engine
 */
void Dev_Init( void );

/**
 *  \brief Change the state of device
 *  \param  state New State
 */
BYTE Dev_ChangeState( BYTE devID, DEV_STATE state );

/**
 *  \brief Get the device status
 *  \param  devID ID of device
 *  \param  bDevState pointer to variable that receive the status
 *  \return device ID or NULL
 */
BYTE Dev_GetStatus( BYTE devID, BYTE * bDevState );

/**
 *  \brief Check the device list
 */
void CheckDevice( void );


#endif		// __DEVICE__
