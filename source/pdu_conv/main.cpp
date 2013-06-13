#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "pduconv.h"


/*
 * The main() function is just for testing and example purposes. 
 */

int main(int argc, char *argv[]) {
    char    *ascii1;
    char    *ascii2;
    unsigned char pdu[1024];
    unsigned char hellopdu[]={0xE8,0x32,0x9B,0xFD,0x46,0x97,0xD9,0xEC,0x37};
    int     pdulen;
    int     i,j;

    FILE * fOut;

    fOut = fopen( "teste.txt" , "w" );

    if ( fOut == NULL ){
      return(1);
    }
    /* Create a test message */
    if (argc>1) {
         ascii1=_strdup(argv[1]);
    } else {
        ascii1=_strdup("åäöÅÄÖ{[\\Mañana\\]}ABC");
    }
    
    memset( pdu, 0, sizeof( pdu ));
    /* Convert the message to a PDU array */
    pdulen=ascii_to_pdu(ascii1,pdu);

    /* Convert the PDU back to a readable message again */
    pdu_to_ascii(pdu,pdulen,&ascii2);

    /* Print the original message, the PDU array, and the new message */
    printf("Original ASCII =%s\n",ascii1);
    fprintf(fOut, "Original ASCII =%s\n",ascii1);
    printf("PDU=");
    fprintf(fOut, "PDU=");

    for (i=0; i<pdulen;i++) {
      printf("%02X ",pdu[i]);
      fprintf(fOut, "%02X",pdu[i]);
    }
    printf("\n");
    printf("Converted ASCII=%s\n\n",ascii2);
    fprintf(fOut, "\n");
    fprintf(fOut, "Converted ASCII=%s\n\n",ascii2);
    fclose( fOut );


    /* Free the allocated strings */
    //free(pdu);
    free(ascii1);
    free(ascii2);

    /* Convert a precalculated PDU array to ASCII.  The array is taken from  */
    /* http://www.dreamfabric.com/sms */
    
    pdu_to_ascii(hellopdu,9,&ascii1);
    printf("hellohello=%s\n\n",ascii1);
    free(ascii1);

    /* Test all printable ASCII characters */
    ascii1=(char*)malloc(40);
    ascii1[32]=0;
    for (j=2; j<8; j++) {
      for (i=0; i<32; i++) {
        ascii1[i]=j*32+i;
      }
      pdulen=ascii_to_pdu(ascii1,pdu);
      pdu_to_ascii(pdu,pdulen,&ascii2);
      printf("Original ASCII =%s\n",ascii1);
      printf("Converted ASCII=%s\n",ascii2);
      //free(pdu);
      free(ascii2);
    }
    free(ascii1);

    return 0;
}
