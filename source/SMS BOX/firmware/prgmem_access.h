#ifndef __PRGMEM_ACC__
#define __PRGMEM_ACC__

#include "defs.h"

/**
 *  \brief  perform the read of a buffer from memory program
 *  \param  buf pointer to receive buffer
 *  \param  dwAddr  Address to read
 *  \param  bLen  number of bytes to read
 *  \return number of bytes readed
 */
BYTE  memprg_read( BYTE * buf, DWORD dwAddr, BYTE bLen );


/**
 *  \brief  perform the write of a buffer to memory program
 *  \param  buf pointer to write buffer
 *  \param  dwAddr  Address to write
 *  \param  bLen    number of bytes to write
 *  \return number of bytes wrote
 */
BYTE  memprg_write( BYTE * buf, DWORD dwAddr, BYTE bLen );

#endif

