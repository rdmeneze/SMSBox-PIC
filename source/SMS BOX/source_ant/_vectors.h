#ifndef __VECTORS__
#define __VECTORS__

//#define _USE_BOOT_LOADER

#define GotoResetVec()           _asm \
                                  goto RM_RESET_VECTOR \
                                  _endasm


#define GotoUserProgram()         _asm \
                                  goto RM_USER_PROGRAM \
                                  _endasm


#if ( defined( _USE_BOOT_LOADER ) /*& !defined( __DEBUG )*/ )
  #define RM_RESET_VECTOR           0x004000 // define relocated vector addresses
#else
  #define RM_RESET_VECTOR           0x000000 // define relocated vector addresses
#endif 

#define RM_USER_PROGRAM             0x004000

#define RM_HIGH_INTERRUPT_VECTOR    0x000008
#define RM_LOW_INTERRUPT_VECTOR     0x000018

#define SECOND_HIGH_ISR_VECTOR      0x001008
#define SECOND_LOW_ISR_VECTOR       0x001018

#endif
