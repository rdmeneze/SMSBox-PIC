/*********************************************************************************************
 *  Arquivo principal. Projeto de teste para desenvolvimento de módulos de 
 *  controle de dispositivos em uma plataforma ACEPIC com processador PIC18 
 *  Compilador utilizado: PIC C18
 *  Autor : Rafael Dias Menezes
 *  Data  : Ago/2009
 *
 *  Deve ser dada atenção às palavras de configuração para operação 
 *  do sistema. Vide help do MPLAB.
 *
 *********************************************************************************************/

//----------------- configuration words   -----------------
#pragma config OSC      = HS
//#pragma config OSC      = INTIO7
#pragma config PWRT     = OFF
#pragma config BOREN    = OFF
#pragma config BORV     = 0
#pragma config MCLRE    = ON
#pragma config PBADEN   = OFF
#pragma config LVP      = OFF  

#ifdef __DEBUG
  #pragma config WDT      = OFF
#else
  #pragma config WDT      = ON
#endif

//----------------------------------------------------------------------

void __init() {
  return;
}

//----------------------------------------------------------------------

void main( void ){
  L1:
    goto L1;
  
  return;
}

//----------------------------------------------------------------------
