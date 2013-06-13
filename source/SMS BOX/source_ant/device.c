#include "device.h"
#include "funcoes.h"
#include "timer.h"
#include "modemGSM.h"
#include "cpu.h"

//---------------------------------------------------------
#define CHECK_DEVICE_TIMER_OV 100L
//---------------------------------------------------------

void UpdateState( CDevicePtr devPtr );

//---------------------------------------------------------

BYTE bDevInit = FALSE;  //! initialization flag status
CDevice dev[NDEV];      //! array of 

//---------------------------------------------------------

const BYTE bDevID[NDEV] = {
  DEV_GSM_PWR_KEY,
  DEV_CPU_RST
};

//---------------------------------------------------------

void Dev_Init( void ){
  BYTE i;
  CDevicePtr devPtr;

  if ( bDevInit == FALSE ){
    bDevInit = TRUE;
  }
  else{
    return;
  }
  
  for ( i = 0, devPtr = &dev[0]; i < GET_VEC_NUM_MEMBERS(dev); i++, devPtr++ ){
    devPtr->ID          = bDevID[i];
    devPtr->bState      = OFF;
    devPtr->bNextState  = OFF;
  }
 
  return;
}

//---------------------------------------------------------

BYTE Dev_ChangeState( BYTE devID, DEV_STATE state ){
  CDevicePtr devPtr;
  BYTE i;
  DEV_STATE devState;

  for ( i = 0, devPtr = &dev[0]; i < GET_VEC_NUM_MEMBERS(dev); i++, devPtr++ ){
    if ( devID == devPtr->ID ){
//
      devState = devPtr->bState;
      
      if ((( devState == ON ) || ( devState == BUSY )) && ( state == ON ))
      {
        return TRUE;
      }

      if ((( devState == OFF ) || ( devState == BUSY )) && ( state == OFF ))
      {
        return TRUE;
      }

      if ( state == BUSY )
      {
        return TRUE;
      }
//
      if ( devPtr->ID & DEV_HS ){
        devPtr->bState      = state;    //! high speed device can modify the state immediately
      }
      else{
        devPtr->bState     = BUSY;
      }
      devPtr->bNextState  = state;    

      return TRUE;
    }
  }
  return FALSE;
}

//---------------------------------------------------------

BYTE Dev_GetStatus( BYTE devID, BYTE * bDevState ) {
  CDevicePtr devPtr;
  BYTE i;
  
  for ( i = 0, devPtr = &dev[0]; i < GET_VEC_NUM_MEMBERS(dev); i++, devPtr++ ){
    if ( devPtr->ID == devID ){
      *bDevState  = (BYTE)devPtr->bState;
      return devID;
    }    
  }
  return NULL;
}

//---------------------------------------------------------

void CheckDevice( void ){

  static TIMER_HANDLE bTimer = TIMER_NULL;
  CDevicePtr devPtr;
  BYTE i;

  if ( bDevInit == FALSE ) {
    Dev_Init();
  }

  if ( bTimer == TIMER_NULL ){
    bTimer = GetTimer( CHECK_DEVICE_TIMER_OV );
  }

  if ( IsTimerTimeOut( bTimer ) == TRUE ){
    RestartTimer( bTimer, CHECK_DEVICE_TIMER_OV );
    for ( i = 0, devPtr = &dev[0]; i < GET_VEC_NUM_MEMBERS(dev); i++, devPtr++ ){
      if ( devPtr->bNextState != devPtr->bState ){
        UpdateState( devPtr );
      }
    }
  }
  return;
}

//---------------------------------------------------------

void UpdateState( CDevicePtr devPtr ){
  BYTE bDevType;
  BYTE bRet = 0xFF;
  BYTE bDevState;
  
  bDevType = (devPtr->ID & DEV_TYPE_MASK);
  switch( bDevType ){
    case GSM_PWR_KEY:
    
    bDevState = (BYTE)ModemGSM_IsReady();

    switch(devPtr->bState){
      case BUSY:
        switch( devPtr->bNextState ) {
          case ON:
            //if ( bDevState == TRUE ){
            //  bRet = GSM_OK;
            //}
            //else{
              bRet = ModemGSM_OnNoBlk();
            //}
          break;

          case OFF:
            if ( bDevState == FALSE ){
              bRet = GSM_OK;
            }
            else{
              bRet = ModemGSM_OffNoBlk();
            }
          break;

          default:
            //bRet = ModemGSM_OffNoBlk(); 
            return;
          }

          if ( bRet == GSM_OK ){
            devPtr->bState = devPtr->bNextState;
            if ( devPtr->bState == OFF )
            {
              ModemGSM_ChangeCheckONOFFTimer( 30000 );
            }
          }

        break;      
      }

      return;
  
    case CPU_RST:
      // ainda não implementado
      CPU_Reset( );
    break;

    default:  
      return;
  }
}

//---------------------------------------------------------
