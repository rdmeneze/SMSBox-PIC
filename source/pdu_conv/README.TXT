*********************************************************************
*                                                                   *
* Functions for converting between an ISO-8859-1 ASCII string and a *
* PDU-coded array as described in ETSI GSM 03.38 and ETSI GSM 03.40 *
*                                                                   *
*********************************************************************

These functions as released to the public domain in 2003 by Mats Engstrom,
Nerdlabs Consulting. ( matseng at nerdlabs dot org )



The file pduconv.c (version 0.1) contains the following two callable functions:

   int ascii_to_pdu(char *ascii, unsigned char **pdu);
   int pdu_to_ascii(unsigned char *pdu, int pdulength, char **ascii);


ascii_to_pdu
============

ascii_to_pdu converts an ASCII-string (*ascii) into an array of PDU-bytes.
The array is malloc()'ed in the function and should be free()'ed by  the
caller. The return value of the function is the length of the PDU-array.

A short example of calling the ascii_to_pdu-function:

    char msg[]="Mats was here";
    unsigned char *pdu;
    int pdulen;
    pdulen=ascii_to_pdu(msg,&pdu);
    ....
    free(pdu);


pdu_to_ascii
============

pdu_to_ascii converts an array of PDU-bytes into an ASCII-string. The ASCII-
string is malloc()'ed in the function and should be free()'ed by the caller.
The return value of the function is the length of the string.

A short example of calling the pdu_to_ascii-function:

    unsigned char pdu[]={0xE8,0x32,0x9B,0xFD,0x46,0x97,0xD9,0xEC,0x37};
    char *ascii;
    pdu_to_ascii(pdu,9,&ascii);
    ....
    free(ascii);


Compiling the test-program
==========================

I've included a small test program named test.c. It converts a string to PDU
and back to ASCII again and prints the result.  It also prints results of converting 
all ASCII characters from ASCII to PDU and back to ASCII again.

To compile and run the test execute the following commands: 

    gcc -Wall -O2 test.c pduconv.c -o testpdu
    ./testpdu
