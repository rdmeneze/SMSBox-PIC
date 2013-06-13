#ifndef _PDU_H_
#define _PDU_H_

int ascii_to_pdu(char *ascii, unsigned char *pdu);
int pdu_to_ascii(unsigned char *pdu, int pdulength, char **ascii);

#endif
