/**
 *  Module to control the time run in the application
 *  Autor   :   Rafael Dias Menezes (rdmeneze@yahoo.com.br)
 *  Date    :   Ago/2009
 */

#ifndef __TIMER__
#define __TIMER__

#include "defs.h"
#include "processor.h"

#define TIMER_HANDLE  BYTE

#define TIMER_NULL (-1)

/** 
 *  Initialize the timer engine
 */
void InitTimer( void );

/**
 *  Get the actual tick timer counter value
 *  \return DWORD   tick count
 */
DWORD GetTickCount( void );

/**
 *  \brief Get a timer handle to a dwTimeValue timer value
 *  \param dwTime time (in time units) to signal
 *  \return TIMER_HANDLE timer handle
 */
TIMER_HANDLE GetTimer( DWORD dwTime );

/**
 *  \brief Restart the timer conter
 *  \param handle to the timer
 *  \param  dwNewTime  the new time to cont
 *  \return TRUE ou FALSE
 */
BYTE  RestartTimer( TIMER_HANDLE handle, DWORD dwNewTime );


/**
 *  \brief Release a timer
 *  \param handle Handle of timer to release
 */
void ReleaseTimer( TIMER_HANDLE * handle );

/**
 *  \brief  Verify if the timer overflows
 *  \param  handle  Handle to timer
 *  \return Overflow condition
 */
BYTE IsTimerTimeOut( TIMER_HANDLE handle );

/**
 *  \brief  Increase the counter 
 */
void IncTickCount( void );

#endif
