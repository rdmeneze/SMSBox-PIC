///////////////////////////////////////////////////////////////////////////
////                             LCDD.C                                ////
////                 Driver for common LCD modules                     ////
////                                                                   ////
////  LCD_Init()   Must be called before any other function.           ////
////                                                                   ////
////  LCD_putc(c)  Will display c on the next position of the LCD.     ////
////                     The following have special meaning:           ////
////                      \f  Clear display                            ////
////                      \n  Go to start of second line               ////
////                      \b  Move back one position                   ////
////                                                                   ////
////  LCD_GotoXY(x,y) Set write position on LCD (upper left is 1,1)    ////
////                                                                   ////
////  LCD_getc(x,y)   Returns character at position x,y on LCD         ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2007 Custom Computer Services           ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////

// As defined in the following structure the pin connection is as follows:
//     D0  enable
//     D1  rs
//     D2  rw
//     D4  D4
//     D5  D5
//     D6  D6
//     D7  D7
//
//   LCD pins D0-D3 are not used and PIC D3 is not used.

// Un-comment the following define to use port B
#include "lcd.h"
#include "delay.h"
#include "funcoes.h"


#define INTERFACE8


//LCD Definitions
#define MAX_ROWS		  2
#define MAX_COLUMNS		16
#define MAX_CHARS		  ROW*COLUMNS



#ifndef lcd_type
#define lcd_type 2           // 0=5x7, 1=5x10, 2=2 lines
#endif

#define lcd_line_two 0x40    // LCD RAM address for the second line

#define EN_PULSE                Nop();\
                                E_PIN = 1;\
                          	  	Nop();\
                          	  	Nop();\
                          	  	Nop();\
                          	  	Nop();\
                                E_PIN = 0;\


//---------------------------------------------------

// These bytes need to be sent to the LCD
// to start it up.
#ifdef INTERFACE8
BYTE LCD_Init_STRING[] = {0x28, 0x08, 0x01, 0x01};
#else
BYTE LCD_Init_STRING[] = {0x20 | (lcd_type << 2), 0xc, 1, 6};
#endif


int _user_putc (char c){
  return LCD_putc( c );
}


//---------------------------------------------------
BYTE lcd_x;
BYTE lcd_y;
//---------------------------------------------------

#ifndef INTERFACE8    
void LCD_Send_Nibble( BYTE n ) {
  LCD_PORT = n;
  EN_PULSE;
}
#endif

//---------------------------------------------------

void LCD_Send_Byte( BYTE isCmd, BYTE n ) {

    RS_PIN = 0;
    Nop();
    RS_PIN = isCmd;
    
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    E_PIN = 0;
#ifdef INTERFACE8    
    LCD_PORT = n;
    EN_PULSE;
#else
    LCD_Send_Nibble(n >> 4);
    LCD_Send_Nibble(n & 0x0F);
#endif
    delay( 1 );
}

//---------------------------------------------------

void LCD_Init() {
  BYTE i;
  
  // control port E
  ADCON1 = 0x0F;   // disable the analog inputs
  
#ifdef INTERFACE8
  TRIS_LCD_PORT = 0x00;
#else
  TRIS_LCD_PORT = 0xF0;
#endif

  LCD_PORT  = 0;

  TRIS_RS = 0;
  RS_PIN  = 0;
  TRIS_E  = 0; 
  E_PIN   = 0; 
    
  delay(30);
  for(i = 0 ; i < 3 ; i++) {
#ifdef INTERFACE8
    LCD_SendCmd( 0x30 );
#else
    LCD_Send_Nibble(0x03);
#endif
    delay(5);
  }
  
#ifdef  INTERFACE8
 LCD_SendCmd(0x38); //Escreve comando para interface de 8 vias de dados
 delay(2);
 LCD_SendCmd(0x01); //Escreve comando para limpar todo o display
 
 delay(1);
 
 LCD_SendCmd(0x0C); //Escreve comando para ligar o display sem cursor
 delay(2);
 LCD_SendCmd(0x06); //Escreve comando para incrementar automaticamente á direita
 delay(2);

#else
  LCD_Send_Nibble(2);
  delay(5);
  
  for( i = 0 ; i < GET_VEC_NUM_MEMBERS(LCD_Init_STRING) ; i++ ){
    LCD_SendCmd( LCD_Init_STRING[i]); 
    delay( 5 );
  }
#endif
  lcd_x = 0;
  lcd_y = 0;

  // redirects the standard default handle to printf
  stdout = _H_USER;

  return;
}

//---------------------------------------------------

void LCD_GotoXY( BYTE x, BYTE y) {
   BYTE address;

   if (x > MAX_COLUMNS - 1 ){
	   x = MAX_COLUMNS - 1 ;
	 }

	 if ( y > MAX_ROWS - 1  ){
		 y = MAX_ROWS - 1 ;
	 }

   if( y == MAX_ROWS - 1)
     address=lcd_line_two;
   else
     address=0;

   address+=x;

   lcd_x = x;
   lcd_y = y;

   LCD_SendCmd( 0x80 + address);
   delay( 3 );
}

//---------------------------------------------------

int LCD_putc( char c) {
	switch (c) {
		case '\f'   :
		  LCD_SendCmd( 1 ); // clear cursor
			lcd_x = 0;
			lcd_y = 0;
			break;

		case '\r'   :
		case '\v'   :
		case '\n'   :
			lcd_x = 0;
			lcd_y = 1;
			LCD_GotoXY(lcd_x,lcd_y);
			break;

		case '\b'   :
		  LCD_SendCmd( 0x10 );
			break;

		default     :
      lcd_x++;
      if ( lcd_x == MAX_COLUMNS ){
        lcd_x = 0;
        if ( lcd_y == MAX_ROWS-1 ){
          lcd_y = 0;
        }
        else{
          lcd_y++;
        }
        LCD_GotoXY( lcd_x , lcd_y ); 
      }
      LCD_SendData( c );			
      
      break;
  }
  return TRUE;
}

//---------------------------------------------------

