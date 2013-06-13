#ifndef __CRC32__
#define __CRC32__

#include "defs.h"

/**
 *  \brief Calcule the CRC32 of a buffer
 */
DWORD crc32c(DWORD crc, const BYTE *data, unsigned int length);

#endif
