#ifndef	__PROCESSOR__
#define	__PROCESSOR__

/* some include files to work with PIC18 family */
#include <p18cxxx.h>
#include <p18f4680.h>
#include "defs.h"
#include "version.h"

#define PRGMEM_WRITE_BLOCK_SIZE 64L

#define SWBAUD     19200L

#define MODEM_BAUDRATE  9600L

#define XTAL    18432000
#define PLL     1

#if     PLL==1
#elif   PLL==4
#else
  #error "Wrong value to PLL macro"
#endif

#ifdef __18F4680_H
  #define PROGRAM_MEMORY_WORDS  (32*1024L*1024L)
  #define PROGRAM_MEMORY_BYTES  (PROGRAM_MEMORY_WORDS * 2)
  #define EEDATA_SIZE           (1024L)
#endif

#define FOSC    XTAL*PLL         // oscilator frequency


#endif
