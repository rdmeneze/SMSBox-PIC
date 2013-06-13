#ifndef __FUNCOES__
#define __FUNCOES__

#include "defs.h"

#define GET_VEC_NUM_MEMBERS(x)  (sizeof(x)/sizeof(x[0]))

#define HINIBBLE( x )( ( x ) / (16L) )
#define LONIBBLE( x )( (BYTE)(( x ) & (0x0F)) )

#define HIBYTE( x ) ( ( x ) / (256L) )
#define LOBYTE( x ) ( (BYTE)( x ) )

#define HIWORD( x ) ( ( x ) / (65536L) )
#define LOWORD( x ) ( (WORD)( x ) )

#define MAKEWORD( x, y ) ((WORD)((WORD)(y * 256L) + x ))
#define MAKELONG( x, y ) ((DWORD)((DWORD)(y * 65536L) + x ))

#define BIT_IS_SET( X, BIT )      ( (X  &  (1 << BIT)) != 0 )
#define BIT_IS_NOT_SET( X, BIT )  ( (X  &  (1 << BIT)) == 0 )
#define BIT_SET( X, BIT )         ( (X |=  (1 << BIT)) )
#define BIT_CLEAR( X, BIT )       ( (X &= ~(1 << BIT)) )

BYTE ascii2int( BYTE asciiChar );

int abs_word( int wVal );

#endif  // __FUNCOES__
