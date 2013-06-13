
#ifndef __BOOT_STATUS_H__
#define __BOOT_STATUS_H__

#include "processor.h"

#define BOOT_LOADER_FRAME_LEN     64
#define BOOT_LOADER_LEN           ( PROGRAM_MEMORY_BYTES + (PROGRAM_MEMORY_BYTES / BOOT_LOADER_FRAME_LEN) * sizeof( DWORD ) )

// Boot loader status
#define BOOT_LOADER_CHANGE_FW     (0)

#endif //~ __BOOT_STATUS_H__
