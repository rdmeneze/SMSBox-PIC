#include "ports.h"


void InitGPIO( void )
{
  SIM_SEL_00_DIR = DIR_OUT;
  SIM_SEL_01_DIR = DIR_OUT;
  SIM_SEL_02_DIR = DIR_OUT;
  SIM_SEL_03_DIR = DIR_OUT;
  SIM_SEL_EN_DIR = DIR_OUT;

  SIM_SEL_EN = 1;           // Inicialmente nenhum sim card está habilitado
  return;
}
