#define SOFTWARE_VERSION_NUMBER			11			// version number * 10

#define MCWP	FALSE			// for general use uncomment this and comment next line
//#define MCWP	TRUE			// for use in Weather stations uncomment this and comment previous line

/*
	the linker options must be setup correctly for the start address used.
	
	The linker must have the following two statements
	-L-Pbootloader=7000h and -RESROM0010-7000
	where the 7000 is replaced by the start_address.
	use 7000h if you are using the ICD and 7800h if not
*/
/*

25-07-2002	v1.1	Added EEprom to SFR fumction and writing EEprom from Hex file
24-05-2002	v1.0	Bootloader for the 18Fxx2 range of processors
*/

#define serial_enable_out			RE2			// 10 enable max3222 0 = enable
#define serial_enable_out_dir		TRISE2
#define serial_TX_out				RC6			// 25 serial TX line
#define serial_TX_out_dir			TRISC6
#define serial_RX_in				RC7			// 26 serial RX line
#define serial_RX_in_dir			TRISC7
#define	serialchip_shutdown_out		RD4			// 27 RS232MAX serial chip powersave
#define	serialchip_shutdown_out_dir	TRISD4	
#define	flash_chip_select_out		RD0			// 19 flash memory CS
#define	flash_chip_select_out_dir	TRISD0		
 

#define	ON					1
#define OFF					0

#define	OUT					0
#define	IN					1

#define FALSE		0
#define TRUE		!FALSE


