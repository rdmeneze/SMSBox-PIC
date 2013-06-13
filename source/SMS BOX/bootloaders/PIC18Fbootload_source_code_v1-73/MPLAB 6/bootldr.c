#include	<pic18.h>
#include	"main.h"

//note: psect bootloader must be linked to ROM location 0x7000, the top of memory
//in MPLab v6.6, select "Project..Build Options..Project", select the "PICC-18 Linker" tab, then select "Use Alternate Settings", then add:
//-L-Pbootloader=7000h -RESRAM008-500 -RESROM0000-7000

#pragma psect text=bootloader

void load_tbl_ptr(unsigned long);
unsigned char bootldr_getch(void);
void ldr_flash_write(unsigned char *,unsigned char,unsigned long);
void bootldr_init_serial(unsigned char);
void bootldr_putch(char);
void read_program(unsigned long,unsigned char,unsigned char *);
void ldr_FLASH_ERASE(unsigned long);
unsigned char read_EE(unsigned char);
void send_reg(void);
void application_jump(void);

/*
bootloader program
accessed via B command from serial control screen.
All interupts are turned off.  The logger is not expected to maintain RTC functions.
Unit will be completely reset on exit.


commands available

S - start programming, read first 8 bytes (4 words) to store erase memory
		program in new reset vector and set to allow programming.
		data recieved in following format.
	byte number		data
	1				length LSB		must be on 64 byte boundry and greater than 64
	2				length MSB
	3				chksum

Z - Program up to 16 bytes into program memory. data recieved in following format.
	Byte number		data
	1				length 1-16
	2				Location LSB
	3				Location MSB
	4				data 0
	---				---
	length+3		data length
	length+4		checksum

	if location == 0 then save first 8 bytes (4 words) into store.

F - finish programming,  write first 8 bytes (4 words) from store and reset processor.

R - Reset Processor

*/

#ifndef	XTAL_FREQ
  //#define	XTAL_FREQ	3580 // Crystal frequency in kHz
  //#define	XTAL_FREQ	3680 // Crystal frequency in kHz
  //#define	XTAL_FREQ	9830 // Crystal frequency in kHz
  //#define	XTAL_FREQ	10000	// Crystal frequency in kHz
  //#define	XTAL_FREQ	14318 // Crystal frequency in kHz
  //#define	XTAL_FREQ	16000 // Crystal frequency in kHz
  #define	XTAL_FREQ	20000 // Crystal frequency in kHz
  //#define	XTAL_FREQ	40000 // Crystal frequency in kHz
#else
  #error XTAL_FREQ undefined
#endif

#define	MHZ	*1000				// number of kHz in a MHz

#define	DelayUs(x)	{ unsigned char _dcnt; \
			  _dcnt = (x)/(12MHZ/(XTAL_FREQ))|1; \
			  while(--_dcnt != 0) \
				  continue; }

#define program_mem 0
#define id_mem 1
#define config_mem 2
#define eeprom_mem 3


//	asm("goto _send_reg");
//	asm("goto _boot_loader");

void
register_send(void)						// used for user program jump
{
	asm("goto _send_reg");
}


void
boot_loader(void)
{
	unsigned char reset_vector_store[4];					// sote to hold first 8 bytes.  these are programmed with a jump to bootloader until all programming finished.
	unsigned long data_address;								// lsb = loc 0, msb - loc 2
	unsigned char data_length;								// length of data recieved
	unsigned char program_data[32];							// 16 byte store for data to be programmed to micro
	unsigned char memory_type;							// state of program 0 = not in program mode
														//					1 = in start program mode, reset_vector_store has been saved and reset vector modified.
	unsigned char i,chksum,type,char_in;
	unsigned static char test[10];

	GIE = 0;												// disable interupts
	SWDTEN = 0;
	serial_TX_out_dir = OUT;
	serial_TX_out = 1;
	serial_RX_in_dir = IN;
 #if (MCWP == TRUE)
	serialchip_shutdown_out_dir = OUT;
	serialchip_shutdown_out = 0;			// shutdown off
	serial_enable_out_dir = OUT;
	serial_enable_out = 0;					// rs232 enabled
	flash_chip_select_out_dir = OUT;
	flash_chip_select_out = 1;
 #endif
	for (data_address = 0;data_address < 40000; data_address++)		//Delay
	{
		asm("NOP");
		asm("NOP");
	}

	bootldr_init_serial(4);			// set up serial ports 19200
	INT0IE = 0;			// enable wakeup from 1 sec pulse
	INT1IE = 0;			// enable wakeup from RS232
	INT2IE = 0;			// enable wakeup from slow pulse
	RBIE = 0;			// RB interupt on change off
	TMR0IE = 0;			//timer 0 overflow
	PEIE = 0;
	ADIE = 0;
 #if (MCWP == TRUE)
	serialchip_shutdown_out = 1;			// shutdown off
 #endif
	bootldr_putch('B');
	bootldr_putch('O');
	bootldr_putch('O');
	bootldr_putch('T');

 #if (MCWP == TRUE)
	while ((TRMT != 1) || (TXIF != 1))
	{
	}
	serialchip_shutdown_out = 0;			// shutdown transmitter
 #endif
 	while(1==1)
	{
		char_in = bootldr_getch();
		switch (char_in)							//bootldr_getch())
		{
			case 'X':
			{
				bootldr_putch('x');
				while ((TRMT != 1) || (TXIF != 1))
				{
				}
				break;
			}
			case 'A':									// for testing register send function
			{
				asm("call _register_send");
			}
			case 'V':
			{
				bootldr_putch('v');
				bootldr_putch(SOFTWARE_VERSION_NUMBER);
				while ((TRMT != 1) || (TXIF != 1))
				{
				}
				break;
			}
			case 'R':
			{
				bootldr_putch('r');
				while ((TRMT != 1) || (TXIF != 1))
				{
				}
				read_program((unsigned long)application_jump,4,&test[0]);
				if (test[1] == 0xEF)
				{
					STKPTR = 0;										// clear stack
					asm("goto _application_jump");					// Jump to user program
				}
				break;
			}
			case 'U':
			case 'E':
			{
				read_program((unsigned long)application_jump,4,&test[0]);
				if (test[1] == 0xEF)
				{
					STKPTR = 0;										// clear stack
					asm("goto _application_jump");					// Jump to user program
				}
				break;
			}
			case 'P':
			{
				bootldr_putch('p');							//
				break;
			}
			case 'B':
			{
				bootldr_putch('b');							//
//				bootldr_putch('B');							//
//				bootldr_putch('O');							//
//				bootldr_putch('O');							//
//				bootldr_putch('T');							//
				break;
			}
			case 'T':										// start program sequence
			case 'S':										// start program sequence
			{
				chksum = 0;
				data_address = bootldr_getch();
				chksum += data_address;
				i = bootldr_getch();
				chksum += i;
				data_address += i*256;
				i = bootldr_getch();
				if (chksum == (0xFF - i))
				{
					reset_vector_store[1] = 0xEF;
					data_address = ((long)boot_loader)>>1;
					reset_vector_store[0] = data_address;
					reset_vector_store[3] = 0xF0;
					reset_vector_store[2] = *(((char *)&data_address)+1);
					memory_type = program_mem;						//set to program memory
					CFGS = 0;										// set memory to program.
					ldr_flash_write(&reset_vector_store[0],4,0);	// reset boot vector to boot_loader
					bootldr_putch('f');
				}
				if (char_in == 'T')
				{
					while ((TRMT != 1) || (TXIF != 1))
					{
					}
					bootldr_init_serial(7);			// set up serial ports 115200
				}
				break;
			}
			case 'Z':										// finish program sequence
			{
				chksum = 0;
				data_length = bootldr_getch();
				chksum += data_length;
				data_address = bootldr_getch();
				chksum += data_address;
				i = bootldr_getch();
				chksum += i;
				data_address = (data_address*256)+i;
				type = bootldr_getch();
				chksum += type;
				for (i=0;i<data_length;i++)
				{
					program_data[i] = bootldr_getch();
					chksum += program_data[i];
				}
				if ((unsigned char)(chksum + bootldr_getch()) == 0)
				{
					if (type == 0)
					{
						if (memory_type == program_mem)
						{
							if (data_address < 0x7000)
							{
								if (data_address == 0)
								{
									for (i=0;i<4;i++)
									{
										reset_vector_store[i] = program_data[i];
									}
									data_length -= 4;
									data_address += 4;
									if (data_length > 0)
									{
										ldr_flash_write(&program_data[4],data_length,data_address);	// Program the locations
									}
								}
								else
								{
									if (data_length > 0)
									{
										ldr_flash_write(&program_data[0],data_length,data_address);	// Program the locations
									}
								}
							}
							bootldr_putch('f');
						}
						else if (memory_type == id_mem)
						{
							if (data_length > 0)
							{
								for (i=data_address;i<data_address+data_length;i++)
								{
//									CFGS = 1;									// set memory to program configuration
									load_tbl_ptr(0x200000+i);				/* load the destination address */
									TABLAT=program_data[i-data_address];	// data into hold buffer
									asm("\tTBLWT*");						// copy 1 byte,
									EEPGD=1;WREN=1;
									GIE=0;
									EECON2=0x55;
									EECON2=0xAA;
									WR=1;									// perform the write for this one byte
									asm("\tNOP");
								}
							}
							bootldr_putch('f');
						}
						else if (memory_type == config_mem)
						{
							if (data_length > 0)
							{
								for (i=data_address;i<data_address+data_length;i++)
								{
									if ((i == 2) || (i == 3) || (i == 5))
									{
										CFGS = 1;									// set memory to program configuration
										load_tbl_ptr(0x300000+i);				/* load the destination address */
										if (i == 3)
										{
											program_data[i-data_address] = program_data[i-data_address] & 0xFE;  // to stop someone setting the WDT on
										}
										TABLAT=program_data[i-data_address];	// data into hold buffer
										asm("\tTBLWT*");						// copy 1 byte,
										EEPGD=1;WREN=1;
										GIE=0;
										EECON2=0x55;
										EECON2=0xAA;
										WR=1;									// perform the write for this one byte
										asm("\tNOP");
									}
								}
							}
							bootldr_putch('f');
						}
						else if (memory_type == eeprom_mem)
						{
							if (data_length > 0)
							{
								for (i=0;i<data_length;i++)
								{
									eeprom_write(data_address+i,program_data[i]);
									while(WR)continue;						//wait for write to finish
								}
							}
							bootldr_putch('f');
						}
					}
					else if (type == 4)
					{
						if (program_data[1] == 0x00)
						{
							memory_type = program_mem;
							CFGS = 0;									// set memory to program.
						}
						if (program_data[1] == 0x20)
						{
							memory_type = id_mem;
						}
						if (program_data[1] == 0x30)
						{
							memory_type = config_mem;
							CFGS = 1;									// set memory to program configuration
						}
						if (program_data[1] == 0xF0)
						{
							memory_type = eeprom_mem;
						}
						bootldr_putch('f');
					}
					else
					{
						bootldr_putch('f');
						memory_type = 0;
					}
				}
				break;
			}
			case 'F':										// finish program sequence
			{
				ldr_flash_write(&reset_vector_store[0],4,(unsigned long)application_jump);		// reset boot vector to boot_loader
				bootldr_putch('f');
				while ((TRMT != 1) || (TXIF != 1))
				{
				}
				STKPTR = 0;										// clear stack
				asm("goto _application_jump");								// Jump to user program
			}
		}
	}
}

unsigned char
bootldr_getch(void)
{
	unsigned long timeout;
	timeout=200000;
	while( (RCIF != 1) && (timeout!=0) )				// RCIF is set if there is a character waiting on the serial port
	{
		timeout--;
	}
	if (timeout == 0)
		return 'E';
	else
		return RCREG;											// RCREG contains serial character waiting
}

void
bootldr_putch(char c)
{
 #if (MCWP == TRUE)
	if (serialchip_shutdown_out == 0)
	{
		serialchip_shutdown_out = 1;			// shutdown off
		DelayUs(250);
		DelayUs(250);
		DelayUs(250);
		DelayUs(250);
	}
 #endif
	while(!TXIF)	// set when register is empty
		continue;
	TXREG=c;
}

void
read_program(unsigned long location,unsigned char length, unsigned char store[])
{
	unsigned char i;
	TBLPTRL=((location)&0xFF);
	TBLPTRH=(((location)>>8)&0xFF);
	TBLPTRU=(((location)>>8)>>8);
	for (i=0;i<length;i++)
	{
		asm("\tTBLRD*+");
		store[i] = TABLAT;
	}
}

void
bootldr_init_serial(unsigned char standard_baud)
{
#if XTAL_FREQ==3580
  unsigned char baud[8]={185,92,46,22,11,5,3,1};			//3.58Mhz
#elif XTAL_FREQ==3680
  unsigned char baud[8]={191,95,47,23,11,5,3,1};			//3.68Mhz
#elif XTAL_FREQ==9830
  unsigned char baud[8]={0xFF,0xFF,0xFF,63,31,15,10,4};		//9.8304Mhz
#elif XTAL_FREQ==10000
  unsigned char baud[8]={0xFF,0xFF,0xFF,64,32,15,10,4};			//10Mhz
#elif XTAL_FREQ==14318
  unsigned char baud[8]={0xFF,0xFF,185,92,46,22,15,7};			//14.318180Mhz
#elif XTAL_FREQ==16000
  unsigned char baud[8]={0xFF,0xFF,0xFF,103,51,25,16,8};			//16Mhz
#elif XTAL_FREQ==20000
  unsigned char baud[8]={0xFF,0xFF,0xFF,129,64,32,21,10};		//20Mhz
#elif XTAL_FREQ==40000
  unsigned char baud[8]={0xFF,0xFF,0xFF,0xFF,129,64,42,21};		//40Mhz
#else
  #error
#endif

	/* relates crystal freq to baud rate - see above and PIC16C7X data sheet p103

	BRGH=1, Fosc=3.579545MHz
	----------------------
	Baud		SPBRG	baud[x] index
	1200		185		0
	2400		92	  1
	4800		46		2
	9600		22		3
	19200		11		4
	38400		5		  5
	57600		3		  6
	115200	1		  7

	BRGH=1, Fosc=3.6864MHz
	----------------------
	Baud		SPBRG	baud[x] index
	1200		191		0
	2400		95		1
	4800		47		2
	9600		23		3
	19200		11		4
	38400		5		5
	57600		3		6
	115200		1		7

  BRGH=1, Fosc=9.8304Mhz
	----------------------
	Baud		SPBRG	baud[x] index
	1200		??		0
	2400		??		1
	4800		??		2
	9600		63		3
	19200		31		4
	38400		15		5
	57600		10		6
	115200	4  		7

	BRGH=1, Fosc=10MHz
	----------------------
	Baud		SPBRG	baud[x] index
	1200		??		0
	2400		??		1
	4800		??		2
	9600		64		3
	19200		32		4
	38400		15		5
	57600		10		6
	115200	4  		7

	BRGH=1, Fosc=14.318180MHz
	----------------------
	Baud		SPBRG	baud[x] index
	1200		??		0
	2400		??		1
	4800		185		2
	9600		92		3
	19200		46		4
	38400		22		5
	57600		15		6
	115200	7  		7

	BRGH=0, Fosc=16MHz
	----------------------
	Baud		SPBRG	baud[x] index
	1200		??		0
	2400		??		1
	4800		??		2
	9600		103  	3
	19200		51		4
	38400		25		5
	57600		16		6
	115200	8		  7

	BRGH=0, Fosc=20MHz
	----------------------
	Baud		SPBRG	baud[x] index
	1200		??		0
	2400		??		1
	4800		??		2
	9600		129		3
	19200		64		4
	38400		32		5
	57600		21		6
	115200	10		7

	*/

	SPBRG=baud[standard_baud];	// data rate for sending
	BRGH=1;				// data rate for sending
	SYNC=0;				// asynchronous
	SPEN=1;				// enable serial port pins
	CREN=1;				// enable reception
	SREN=0;				// no effect
	TXIE=0;				// disable tx interrupts
	RCIE=0;				// disable rx interrupts
	TX9=0;				// 8-bit transmission
	RX9=0;				// 8-bit reception
	TXEN=1;				// enable the transmitter

}


void ldr_flash_write(unsigned char * read_addr,unsigned char length,unsigned long dest_addr)
{
	/* variable declaration */
	unsigned char counter = 0;
	unsigned char counter_high;
	unsigned char BUFFER[64];
	unsigned char datalength;
	unsigned char prebuffer_count;
	unsigned char prebuffer;
	unsigned char data;
	prebuffer=(dest_addr%64);
	prebuffer_count=prebuffer;
	length+=prebuffer_count;

	dest_addr-=prebuffer_count;	/* force to write to start of sector */

	while(length)
	{

		datalength=length;
		length-=64;

		if ( datalength > 64 )
			datalength = 64;
		else
			length=0;

/* copy_to_buffer(); */
		FSR1H=((((unsigned int)&BUFFER[0])>>8)&0xFF);	// BUFFER is where the data storage area
		FSR1L=(((unsigned int)&BUFFER[0])&0xFF);

		load_tbl_ptr(dest_addr);	// if dest is not at start of sector, start to fill buffer
						// from start of dest sector
		while (prebuffer_count)
		{
			asm("\tTBLRD*+");
			POSTINC1=(TABLAT);
			counter++;
			prebuffer_count--;
		}

	//	load_tbl_ptr(*read_addr);	// Used to point to data source if source was ROM

		while ( counter < datalength )	// read [copylength] bytes of data from the source address into the BUFFER
		{
				data=(*(read_addr++));
				POSTINC1=(data);
				counter++;
		}

		load_tbl_ptr(dest_addr+counter-1);	// fill the remainder of the BUFFER by saving existing data
							// within the destination range
		while ( counter < 64 )	// until 64 bytes have been read.
		{
			asm("\tTBLRD+*");
			POSTINC1=(TABLAT);
			counter++;
		}
		counter = counter;
		ldr_FLASH_ERASE(dest_addr);

/* now begin to copy the buffer to the destination area */
		load_tbl_ptr((dest_addr-1)&0x1FFFFF);	/* load the destination address */

		FSR1H=((((unsigned int)&BUFFER[0])>>8)&0xFF);	/* point the source address to the start of the BUFFER */
		FSR1L=(((unsigned int)&BUFFER[0])&0xFF);

		counter_high=8;		/* 64 bytes must be written, this will be done in 8 * 8 blocks */

		while(counter_high)
		{
			counter=8;
			while(counter)
			{
				TABLAT=(POSTINC1);	// data into hold buffer
				asm("\tTBLWT+*");		// copy 1 byte, 8 times
				counter--;
			}

			EEPGD=1;WREN=1;
			GIE=0;
			EECON2=0x55;
			EECON2=0xAA;
			WR=1;	// perform the write for these 8 bytes
			asm("\tNOP");
			counter_high--;
		}
		WREN=0;
		dest_addr+=64;
		prebuffer=0;
	}
}

void load_tbl_ptr(unsigned long addr)
{
	TBLPTRU=((((addr)>>8)>>8)&0xFF);
	TBLPTRH=(((addr)>>8)&0xFF);
	TBLPTRL=((addr)&0xFF);
}

void ldr_FLASH_ERASE(unsigned long addr)
{
	load_tbl_ptr(addr);
	CFGS=0;
	EEPGD=1;
	WREN=1;
	FREE=1;
	EECON2=0x55;
	EECON2=0xAA;
	WR=1;
	asm("\tNOP");
}

unsigned char
read_EE(unsigned char loc)
{
	unsigned char val;
	CFGS = 0;
	EEADR = loc;
	EEPGD = 0;
	RD = 1;
	val = EEDATA;
	return val;
}

unsigned char
read_config(unsigned long dest_addr)
{
	CFGS = 1;
	load_tbl_ptr(dest_addr);					// load the destination address
	asm("\tTBLRD*+");							// copy 1 byte into the table
	return TABLAT;								// data into hold buffer
}

void
send_reg(void)
{
	unsigned int i;
	unsigned char j;
	unsigned char test[2];
	unsigned char input;
	unsigned char spbrg_tmp;
	unsigned char status_tmp;
	unsigned char txsta_tmp;
	unsigned char rcsta_tmp;
	unsigned char txreg_tmp;
	unsigned char intcon_tmp;
	unsigned char pir1_tmp;
	unsigned char wreg_tmp;

	wreg_tmp = WREG;
	intcon_tmp = INTCON;
	GIE = 0;								//disable interupts
	SWDTEN = 0;
	pir1_tmp = PIR1;
	status_tmp = STATUS;
	spbrg_tmp = SPBRG;
	txsta_tmp = TXSTA;
	rcsta_tmp = RCSTA;
	txreg_tmp = TXREG;
	bootldr_init_serial(4);
	bootldr_putch('S');
	bootldr_putch('F');
	bootldr_putch('R');
	bootldr_putch(TOSU);
	bootldr_putch(TOSH);
	bootldr_putch(TOSL);
	bootldr_putch(STKPTR);
	bootldr_putch(PCLATU);
	bootldr_putch(PCLATH);
	bootldr_putch(PCL);
	bootldr_putch(TBLPTRU);
	bootldr_putch(TBLPTRH);
	bootldr_putch(TBLPTRL);
	bootldr_putch(TABLAT);
	bootldr_putch(PRODH);
	bootldr_putch(PRODL);
	bootldr_putch(intcon_tmp);
	bootldr_putch(INTCON2);
	bootldr_putch(INTCON3);
	bootldr_putch(FSR0H);
	bootldr_putch(FSR0L);
	bootldr_putch(wreg_tmp);
	bootldr_putch(FSR1H);
	bootldr_putch(FSR1L);
	bootldr_putch(BSR);
	bootldr_putch(FSR2H);
	bootldr_putch(FSR2L);
	bootldr_putch(status_tmp);
	bootldr_putch(TMR0H);
	bootldr_putch(TMR0L);
	bootldr_putch(T0CON);
	bootldr_putch(OSCCON);
	bootldr_putch(LVDCON);
	bootldr_putch(WDTCON);
	bootldr_putch(RCON);
	bootldr_putch(TMR1H);
	bootldr_putch(TMR1L);
	bootldr_putch(T1CON);
	bootldr_putch(TMR2);
	bootldr_putch(PR2);
	bootldr_putch(T2CON);
	bootldr_putch(SSPBUF);
	bootldr_putch(SSPADD);
	bootldr_putch(SSPSTAT);
	bootldr_putch(SSPCON1);
	bootldr_putch(SSPCON2);
	bootldr_putch(ADRESH);
	bootldr_putch(ADRESL);
	bootldr_putch(ADCON0);
	bootldr_putch(ADCON1);
	bootldr_putch(CCPR1H);
	bootldr_putch(CCPR1L);
	bootldr_putch(CCP1CON);
	bootldr_putch(CCPR2H);
	bootldr_putch(CCPR2L);
	bootldr_putch(CCP2CON);
	bootldr_putch(TMR3H);
	bootldr_putch(TMR3L);
	bootldr_putch(T3CON);
	bootldr_putch(spbrg_tmp);
	bootldr_putch(RCREG);
	bootldr_putch(txreg_tmp);
	bootldr_putch(txsta_tmp);
	bootldr_putch(rcsta_tmp);
	bootldr_putch(EEADR);
	bootldr_putch(EEDATA);
	bootldr_putch(EECON2);
	bootldr_putch(EECON1);
	bootldr_putch(IPR2);
	bootldr_putch(PIR2);
	bootldr_putch(PIE2);
	bootldr_putch(IPR1);
	bootldr_putch(pir1_tmp);
	bootldr_putch(PIE1);
 #if defined(_18F452)
	bootldr_putch(TRISE);
	bootldr_putch(TRISD);
 #endif
 #if defined(_18F252)
	bootldr_putch(0);
	bootldr_putch(0);
 #endif
	bootldr_putch(TRISC);
	bootldr_putch(TRISB);
	bootldr_putch(TRISA);
 #if defined(_18F452)
	bootldr_putch(LATE);
	bootldr_putch(LATD);
 #endif
 #if defined(_18F252)
	bootldr_putch(0);
	bootldr_putch(0);
 #endif
	bootldr_putch(LATC);
	bootldr_putch(LATB);
	bootldr_putch(LATA);
 #if defined(_18F452)
	bootldr_putch(PORTE);
	bootldr_putch(PORTD);
 #endif
 #if defined(_18F252)
	bootldr_putch(0);
	bootldr_putch(0);
 #endif
	bootldr_putch(PORTC);
	bootldr_putch(PORTB);
	bootldr_putch(PORTA);
	FSR0L = 0;
	FSR0H = 0;
	for (i=0;i<=0x5FF;i++)
	{
		bootldr_putch(POSTINC0);
	}
	for (j=0;j<=0x0FC;j++)
	{
		bootldr_putch(read_EE(j));
	}
	bootldr_putch(read_config(0x200000));
	bootldr_putch(read_config(0x200001));
	bootldr_putch(read_config(0x200002));
//	bootldr_putch(read_config(0x300002));
//	bootldr_putch(read_config(0x300003));
//	bootldr_putch(read_config(0x300005));
	while ((TRMT != 1) || (TXIF != 1))
	{
	}
	while(1==1)
	{
		input = bootldr_getch();
		if (input == 'X')
		{
			bootldr_putch('x');
		}
		if (input == 'P')
		{
			bootldr_putch('p');
		}
		if (input == 'B')
		{
			bootldr_putch('b');
			while ((TRMT != 1) || (TXIF != 1))
			{
			}
			asm("goto _boot_loader");
		}

		if (input == 'A')
		{
			asm("goto _register_send");
		}

		if ((input == 'R') || (input == 'U'))
		{
			read_program((unsigned long)application_jump,2,&test[0]);
			if (test[1] == 0xEF)
			{
				STKPTR = 0;										// clear stack
				asm("goto _application_jump");					// Jump to user program
			}
			else
			{
				STKPTR = 0;										// clear stack
				asm("goto _boot_loader");						// no user program so rerun bootloader.
			}
		}
	}
}

void
application_jump(void)					// used for user program jump
{
	asm(" NOP");
}

