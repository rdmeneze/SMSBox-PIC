#ifndef __VECTORS__
#define __VECTORS__

//#define _USE_BOOT_LOADER

#if ( defined( _USE_BOOT_LOADER ) & !defined( __DEBUG ) )
  //------------------------------------------------------------------------------------
  #define RM_RESET_VECTOR           0x002000 // define relocated vector addresses
  #define RM_HIGH_INTERRUPT_VECTOR  0x002008
  #define RM_LOW_INTERRUPT_VECTOR   0x002018
  //------------------------------------------------------------------------------------
#else
  //------------------------------------------------------------------------------------
  #define RM_RESET_VECTOR           0x000000 // define relocated vector addresses
  #define RM_HIGH_INTERRUPT_VECTOR  0x000008
  #define RM_LOW_INTERRUPT_VECTOR   0x000018
  //------------------------------------------------------------------------------------
#endif // ~_USE_BOOT_LOADER

#define SECOND_HIGH_ISR_VECTOR  0x001008
#define SECOND_LOW_ISR_VECTOR   0x001018

#endif
