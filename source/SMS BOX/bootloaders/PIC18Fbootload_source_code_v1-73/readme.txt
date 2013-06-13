Hi,

Here is the source code for the 18Fx52 bootloader.

The Windows source code performs an extremely simple task: it simply sends the
unaltered .hex file out of the COM port, with minimal flow control.

Here is an extract from bootldr.c showing the commands:

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

If you wish to look at the data flowing out of the COM port in real time, use Portmon:

http://www.microsoft.com/technet/sysinternals/utilities/PortMon.mspx

If creating the project manually, the psect bootloader must be linked to ROM
location 0x7000, the top of memory. In MPLab v6.6, select "Project..Build
Options..Project", select the "PICC-18 Linker" tab, then select "Use Alternate
Settings", then add:

-L-Pbootloader=7000h -RESRAM008-500 -RESROM0000-7000

Other than that, this .zip file contains enough information to get your own bootloader up
and running.