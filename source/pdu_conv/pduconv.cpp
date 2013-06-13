/***************************************************************************
 *
 * Functions for converting between an ISO-8859-1 ASCII string and a 
 * PDU-coded string as described in ETSI GSM 03.38 and ETSI GSM 03.40.
 *
 * This code is released to the public domain in 2003 by Mats Engstrom,
 * Nerdlabs Consulting. ( matseng at nerdlabs dot org )
 *
 **************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#include "pduconv.h"

#define VERSION 0.1

/* Define Non-Printable Characters as a question mark */
#define NPC7    63
#define NPC8    '?'



/****************************************************************************
    This lookup table converts from ISO-8859-1 8-bit ASCII to the
    7 bit "default alphabet" as defined in ETSI GSM 03.38

    ISO-characters that don't have any correspondning character in the
    7-bit alphabet is replaced with the NPC7-character.  If there's
    a close match between the ISO-char and a 7-bit character (for example
    the letter i with a circumflex and the plain i-character) a substitution
    is done. These "close-matches" are marked in the lookup table by
    having its value negated.
    
    There are some character (for example the curly brace "}") that must
    be converted into a 2 byte 7-bit sequence.  These characters are
    marked in the table by having 256 added to its value.              
****************************************************************************/

int lookup_ascii8to7[]={
    NPC7,       /*     0      null [NUL]                              */
    NPC7,       /*     1      start of heading [SOH]                  */
    NPC7,       /*     2      start of text [STX]                     */
    NPC7,       /*     3      end of text [ETX]                       */
    NPC7,       /*     4      end of transmission [EOT]               */
    NPC7,       /*     5      enquiry [ENQ]                           */
    NPC7,       /*     6      acknowledge [ACK]                       */
    NPC7,       /*     7      bell [BEL]                              */
    NPC7,       /*     8      backspace [BS]                          */
    NPC7,       /*     9      horizontal tab [HT]                     */
    10,         /*    10      line feed [LF]                          */
    NPC7,       /*    11      vertical tab [VT]                       */
    10+256,     /*    12      form feed [FF]                          */
    13,         /*    13      carriage return [CR]                    */
    NPC7,       /*    14      shift out [SO]                          */
    NPC7,       /*    15      shift in [SI]                           */
    NPC7,       /*    16      data link escape [DLE]                  */
    NPC7,       /*    17      device control 1 [DC1]                  */
    NPC7,       /*    18      device control 2 [DC2]                  */
    NPC7,       /*    19      device control 3 [DC3]                  */
    NPC7,       /*    20      device control 4 [DC4]                  */
    NPC7,       /*    21      negative acknowledge [NAK]              */
    NPC7,       /*    22      synchronous idle [SYN]                  */
    NPC7,       /*    23      end of trans. block [ETB]               */
    NPC7,       /*    24      cancel [CAN]                            */
    NPC7,       /*    25      end of medium [EM]                      */
    NPC7,       /*    26      substitute [SUB]                        */
    NPC7,       /*    27      escape [ESC]                            */
    NPC7,       /*    28      file separator [FS]                     */
    NPC7,       /*    29      group separator [GS]                    */
    NPC7,       /*    30      record separator [RS]                   */
    NPC7,       /*    31      unit separator [US]                     */
    32,         /*    32      space                                   */
    33,         /*    33    ! exclamation mark                        */
    34,         /*    34    " double quotation mark                   */
    35,         /*    35    # number sign                             */
    2,          /*    36    $ dollar sign                             */
    37,         /*    37    % percent sign                            */
    38,         /*    38    & ampersand                               */
    39,         /*    39    ' apostrophe                              */
    40,         /*    40    ( left parenthesis                        */
    41,         /*    41    ) right parenthesis                       */
    42,         /*    42    * asterisk                                */
    43,         /*    43    + plus sign                               */
    44,         /*    44    , comma                                   */
    45,         /*    45    - hyphen                                  */
    46,         /*    46    . period                                  */
    47,         /*    47    / slash,                                  */
    48,         /*    48    0 digit 0                                 */
    49,         /*    49    1 digit 1                                 */
    50,         /*    50    2 digit 2                                 */
    51,         /*    51    3 digit 3                                 */
    52,         /*    52    4 digit 4                                 */
    53,         /*    53    5 digit 5                                 */
    54,         /*    54    6 digit 6                                 */
    55,         /*    55    7 digit 7                                 */
    56,         /*    56    8 digit 8                                 */
    57,         /*    57    9 digit 9                                 */
    58,         /*    58    : colon                                   */
    59,         /*    59    ; semicolon                               */
    60,         /*    60    < less-than sign                          */
    61,         /*    61    = equal sign                              */
    62,         /*    62    > greater-than sign                       */
    63,         /*    63    ? question mark                           */
    0,          /*    64    @ commercial at sign                      */
    65,         /*    65    A uppercase A                             */
    66,         /*    66    B uppercase B                             */
    67,         /*    67    C uppercase C                             */
    68,         /*    68    D uppercase D                             */
    69,         /*    69    E uppercase E                             */
    70,         /*    70    F uppercase F                             */
    71,         /*    71    G uppercase G                             */
    72,         /*    72    H uppercase H                             */
    73,         /*    73    I uppercase I                             */
    74,         /*    74    J uppercase J                             */
    75,         /*    75    K uppercase K                             */
    76,         /*    76    L uppercase L                             */
    77,         /*    77    M uppercase M                             */
    78,         /*    78    N uppercase N                             */
    79,         /*    79    O uppercase O                             */
    80,         /*    80    P uppercase P                             */
    81,         /*    81    Q uppercase Q                             */
    82,         /*    82    R uppercase R                             */
    83,         /*    83    S uppercase S                             */
    84,         /*    84    T uppercase T                             */
    85,         /*    85    U uppercase U                             */
    86,         /*    86    V uppercase V                             */
    87,         /*    87    W uppercase W                             */
    88,         /*    88    X uppercase X                             */
    89,         /*    89    Y uppercase Y                             */
    90,         /*    90    Z uppercase Z                             */
    60+256,     /*    91    [ left square bracket                     */
    47+256,     /*    92    \ backslash                               */
    62+256,     /*    93    ] right square bracket                    */
    20+256,     /*    94    ^ circumflex accent                       */
    17,         /*    95    _ underscore                              */
    -39,        /*    96    ` back apostrophe                         */
    97,         /*    97    a lowercase a                             */
    98,         /*    98    b lowercase b                             */
    99,         /*    99    c lowercase c                             */
    100,        /*   100    d lowercase d                             */
    101,        /*   101    e lowercase e                             */
    102,        /*   102    f lowercase f                             */
    103,        /*   103    g lowercase g                             */
    104,        /*   104    h lowercase h                             */
    105,        /*   105    i lowercase i                             */
    106,        /*   106    j lowercase j                             */
    107,        /*   107    k lowercase k                             */
    108,        /*   108    l lowercase l                             */
    109,        /*   109    m lowercase m                             */
    110,        /*   110    n lowercase n                             */
    111,        /*   111    o lowercase o                             */
    112,        /*   112    p lowercase p                             */
    113,        /*   113    q lowercase q                             */
    114,        /*   114    r lowercase r                             */
    115,        /*   115    s lowercase s                             */
    116,        /*   116    t lowercase t                             */
    117,        /*   117    u lowercase u                             */
    118,        /*   118    v lowercase v                             */
    119,        /*   119    w lowercase w                             */
    120,        /*   120    x lowercase x                             */
    121,        /*   121    y lowercase y                             */
    122,        /*   122    z lowercase z                             */
    40+256,     /*   123    { left brace                              */
    64+256,     /*   124    | vertical bar                            */
    41+256,     /*   125    } right brace                             */
    61+256,     /*   126    ~ tilde accent                            */
    NPC7,       /*   127      delete [DEL]                            */
    NPC7,       /*   128                                              */
    NPC7,       /*   129                                              */
    -39,        /*   130      low left rising single quote            */
    -102,       /*   131      lowercase italic f                      */
    -34,        /*   132      low left rising double quote            */
    NPC7,       /*   133      low horizontal ellipsis                 */
    NPC7,       /*   134      dagger mark                             */
    NPC7,       /*   135      double dagger mark                      */
    NPC7,       /*   136      letter modifying circumflex             */
    NPC7,       /*   137      per thousand (mille) sign               */
    -83,        /*   138      uppercase S caron or hacek              */
    -39,        /*   139      left single angle quote mark            */
    -214,       /*   140      uppercase OE ligature                   */
    NPC7,       /*   141                                              */
    NPC7,       /*   142                                              */
    NPC7,       /*   143                                              */
    NPC7,       /*   144                                              */
    -39,        /*   145      left single quotation mark              */
    -39,        /*   146      right single quote mark                 */
    -34,        /*   147      left double quotation mark              */
    -34,        /*   148      right double quote mark                 */
    -42,        /*   149      round filled bullet                     */
    -45,        /*   150      en dash                                 */
    -45,        /*   151      em dash                                 */
    -39,        /*   152      small spacing tilde accent              */
    NPC7,       /*   153      trademark sign                          */
    -115,       /*   154      lowercase s caron or hacek              */
    -39,        /*   155      right single angle quote mark           */
    -111,       /*   156      lowercase oe ligature                   */
    NPC7,       /*   157                                              */
    NPC7,       /*   158                                              */
    -89,        /*   159      uppercase Y dieresis or umlaut          */
    -32,        /*   160      non-breaking space                      */
    64,         /*   161    ¡ inverted exclamation mark               */
    -99,        /*   162    ¢ cent sign                               */
    1,          /*   163    £ pound sterling sign                     */
    36,         /*   164    ¤ general currency sign                   */
    3,          /*   165    ¥ yen sign                                */
    -33,        /*   166    ¦ broken vertical bar                     */
    95,         /*   167    § section sign                            */
    -34,        /*   168    ¨ spacing dieresis or umlaut              */
    NPC7,       /*   169    © copyright sign                          */
    NPC7,       /*   170    ª feminine ordinal indicator              */
    -60,        /*   171    « left (double) angle quote               */
    NPC7,       /*   172    ¬ logical not sign                        */
    -45,        /*   173    ­ soft hyphen                             */
    NPC7,       /*   174    ® registered trademark sign               */
    NPC7,       /*   175    ¯ spacing macron (long) accent            */
    NPC7,       /*   176    ° degree sign                             */
    NPC7,       /*   177    ± plus-or-minus sign                      */
    -50,        /*   178    ² superscript 2                           */
    -51,        /*   179    ³ superscript 3                           */
    -39,        /*   180    ´ spacing acute accent                    */
    -117,       /*   181    µ micro sign                              */
    NPC7,       /*   182    ¶ paragraph sign, pilcrow sign            */
    NPC7,       /*   183    · middle dot, centered dot                */
    NPC7,       /*   184    ¸ spacing cedilla                         */
    -49,        /*   185    ¹ superscript 1                           */
    NPC7,       /*   186    º masculine ordinal indicator             */
    -62,        /*   187    » right (double) angle quote (guillemet)  */
    NPC7,       /*   188    ¼ fraction 1/4                            */
    NPC7,       /*   189    ½ fraction 1/2                            */
    NPC7,       /*   190    ¾ fraction 3/4                            */
    96,         /*   191    ¿ inverted question mark                  */
    -65,        /*   192    À uppercase A grave                       */
    -65,        /*   193    Á uppercase A acute                       */
    -65,        /*   194    Â uppercase A circumflex                  */
    -65,        /*   195    Ã uppercase A tilde                       */
    91,         /*   196    Ä uppercase A dieresis or umlaut          */
    14,         /*   197    Å uppercase A ring                        */
    28,         /*   198    Æ uppercase AE ligature                   */
    9,          /*   199    Ç uppercase C cedilla                     */
    -31,        /*   200    È uppercase E grave                       */
    31,         /*   201    É uppercase E acute                       */
    -31,        /*   202    Ê uppercase E circumflex                  */
    -31,        /*   203    Ë uppercase E dieresis or umlaut          */
    -73,        /*   204    Ì uppercase I grave                       */
    -73,        /*   205    Í uppercase I acute                       */
    -73,        /*   206    Î uppercase I circumflex                  */
    -73,        /*   207    Ï uppercase I dieresis or umlaut          */
    -68,        /*   208    Ð uppercase ETH                           */
    93,         /*   209    Ñ uppercase N tilde                       */
    -79,        /*   210    Ò uppercase O grave                       */
    -79,        /*   211    Ó uppercase O acute                       */
    -79,        /*   212    Ô uppercase O circumflex                  */
    -79,        /*   213    Õ uppercase O tilde                       */
    92,         /*   214    Ö uppercase O dieresis or umlaut          */
    -42,        /*   215    × multiplication sign                     */
    11,         /*   216    Ø uppercase O slash                       */
    -85,        /*   217    Ù uppercase U grave                       */
    -85,        /*   218    Ú uppercase U acute                       */
    -85,        /*   219    Û uppercase U circumflex                  */
    94,         /*   220    Ü uppercase U dieresis or umlaut          */
    -89,        /*   221    Ý uppercase Y acute                       */
    NPC7,       /*   222    Þ uppercase THORN                         */
    30,         /*   223    ß lowercase sharp s, sz ligature          */
    127,        /*   224    à lowercase a grave                       */
    -97,        /*   225    á lowercase a acute                       */
    -97,        /*   226    â lowercase a circumflex                  */
    -97,        /*   227    ã lowercase a tilde                       */
    123,        /*   228    ä lowercase a dieresis or umlaut          */
    15,         /*   229    å lowercase a ring                        */
    29,         /*   230    æ lowercase ae ligature                   */
    -9,         /*   231    ç lowercase c cedilla                     */
    4,          /*   232    è lowercase e grave                       */
    5,          /*   233    é lowercase e acute                       */
    -101,       /*   234    ê lowercase e circumflex                  */
    -101,       /*   235    ë lowercase e dieresis or umlaut          */
    7,          /*   236    ì lowercase i grave                       */
    7,          /*   237    í lowercase i acute                       */
    -105,       /*   238    î lowercase i circumflex                  */
    -105,       /*   239    ï lowercase i dieresis or umlaut          */
    NPC7,       /*   240    ð lowercase eth                           */
    125,        /*   241    ñ lowercase n tilde                       */
    8,          /*   242    ò lowercase o grave                       */
    -111,       /*   243    ó lowercase o acute                       */
    -111,       /*   244    ô lowercase o circumflex                  */
    -111,       /*   245    õ lowercase o tilde                       */
    124,        /*   246    ö lowercase o dieresis or umlaut          */
    -47,        /*   247    ÷ division sign                           */
    12,         /*   248    ø lowercase o slash                       */
    6,          /*   249    ù lowercase u grave                       */
    -117,       /*   250    ú lowercase u acute                       */
    -117,       /*   251    û lowercase u circumflex                  */
    126,        /*   252    ü lowercase u dieresis or umlaut          */
    -121,       /*   253    ý lowercase y acute                       */
    NPC7,       /*   254    þ lowercase thorn                         */
    -121        /*   255    ÿ lowercase y dieresis or umlaut          */
};



/****************************************************************************
   This lookup table converts from the 7 bit "default alphabet" as 
    defined in ETSI GSM 03.38 to a standard ISO-8859-1 8-bit ASCII.  
    
    Some characters in the 7-bit alphabet does not exist in the ISO
    character set, they are replaced by the NPC8-character.
    
    If the character is decimal 27 (ESC) the following character have
    a special meaning and must be handled separately.
****************************************************************************/

int lookup_ascii7to8[]={
    64,         /*  0      @  COMMERCIAL AT                           */      
    163,        /*  1      £  POUND SIGN                              */      
    36,         /*  2      $  DOLLAR SIGN                             */      
    165,        /*  3      ¥  YEN SIGN                                */      
    232,        /*  4      è  LATIN SMALL LETTER E WITH GRAVE         */      
    233,        /*  5      é  LATIN SMALL LETTER E WITH ACUTE         */      
    249,        /*  6      ù  LATIN SMALL LETTER U WITH GRAVE         */      
    236,        /*  7      ì  LATIN SMALL LETTER I WITH GRAVE         */      
    242,        /*  8      ò  LATIN SMALL LETTER O WITH GRAVE         */      
    199,        /*  9      Ç  LATIN CAPITAL LETTER C WITH CEDILLA     */      
    10,         /*  10        LINE FEED                               */      
    216,        /*  11     Ø  LATIN CAPITAL LETTER O WITH STROKE      */      
    248,        /*  12     ø  LATIN SMALL LETTER O WITH STROKE        */      
    13,         /*  13        CARRIAGE RETURN                         */      
    197,        /*  14     Å  LATIN CAPITAL LETTER A WITH RING ABOVE  */      
    229,        /*  15     å  LATIN SMALL LETTER A WITH RING ABOVE    */      
    NPC8,       /*  16        GREEK CAPITAL LETTER DELTA              */
    95,         /*  17     _  LOW LINE                                */      
    NPC8,       /*  18        GREEK CAPITAL LETTER PHI                */
    NPC8,       /*  19        GREEK CAPITAL LETTER GAMMA              */
    NPC8,       /*  20        GREEK CAPITAL LETTER LAMBDA             */
    NPC8,       /*  21        GREEK CAPITAL LETTER OMEGA              */
    NPC8,       /*  22        GREEK CAPITAL LETTER PI                 */
    NPC8,       /*  23        GREEK CAPITAL LETTER PSI                */
    NPC8,       /*  24        GREEK CAPITAL LETTER SIGMA              */
    NPC8,       /*  25        GREEK CAPITAL LETTER THETA              */
    NPC8,       /*  26        GREEK CAPITAL LETTER XI                 */
    27,         /*  27        ESCAPE TO EXTENSION TABLE               */
    198,        /*  28     Æ  LATIN CAPITAL LETTER AE                 */                 
    230,        /*  29     æ  LATIN SMALL LETTER AE                   */      
    223,        /*  30     ß  LATIN SMALL LETTER SHARP S (German)     */      
    201,        /*  31     É  LATIN CAPITAL LETTER E WITH ACUTE       */      
    32,         /*  32        SPACE                                   */       
    33,         /*  33     !  EXCLAMATION MARK                        */       
    34,         /*  34     "  QUOTATION MARK                          */       
    35,         /*  35     #  NUMBER SIGN                             */       
    164,        /*  36     ¤  CURRENCY SIGN                           */       
    37,         /*  37     %  PERCENT SIGN                            */       
    38,         /*  38     &  AMPERSAND                               */       
    39,         /*  39     '  APOSTROPHE                              */       
    40,         /*  40     (  LEFT PARENTHESIS                        */       
    41,         /*  41     )  RIGHT PARENTHESIS                       */       
    42,         /*  42     *  ASTERISK                                */       
    43,         /*  43     +  PLUS SIGN                               */       
    44,         /*  44     ,  COMMA                                   */       
    45,         /*  45     -  HYPHEN-MINUS                            */       
    46,         /*  46     .  FULL STOP                               */       
    47,         /*  47     /  SOLIDUS (SLASH)                         */       
    48,         /*  48     0  DIGIT ZERO                              */       
    49,         /*  49     1  DIGIT ONE                               */       
    50,         /*  50     2  DIGIT TWO                               */       
    51,         /*  51     3  DIGIT THREE                             */       
    52,         /*  52     4  DIGIT FOUR                              */       
    53,         /*  53     5  DIGIT FIVE                              */       
    54,         /*  54     6  DIGIT SIX                               */       
    55,         /*  55     7  DIGIT SEVEN                             */       
    56,         /*  56     8  DIGIT EIGHT                             */       
    57,         /*  57     9  DIGIT NINE                              */       
    58,         /*  58     :  COLON                                   */       
    59,         /*  59     ;  SEMICOLON                               */       
    60,         /*  60     <  LESS-THAN SIGN                          */       
    61,         /*  61     =  EQUALS SIGN                             */       
    62,         /*  62     >  GREATER-THAN SIGN                       */                                       
    63,         /*  63     ?  QUESTION MARK                           */       
    161,        /*  64     ¡  INVERTED EXCLAMATION MARK               */       
    65,         /*  65     A  LATIN CAPITAL LETTER A                  */       
    66,         /*  66     B  LATIN CAPITAL LETTER B                  */       
    67,         /*  67     C  LATIN CAPITAL LETTER C                  */       
    68,         /*  68     D  LATIN CAPITAL LETTER D                  */       
    69,         /*  69     E  LATIN CAPITAL LETTER E                  */       
    70,         /*  70     F  LATIN CAPITAL LETTER F                  */       
    71,         /*  71     G  LATIN CAPITAL LETTER G                  */       
    72,         /*  72     H  LATIN CAPITAL LETTER H                  */       
    73,         /*  73     I  LATIN CAPITAL LETTER I                  */       
    74,         /*  74     J  LATIN CAPITAL LETTER J                  */       
    75,         /*  75     K  LATIN CAPITAL LETTER K                  */       
    76,         /*  76     L  LATIN CAPITAL LETTER L                  */       
    77,         /*  77     M  LATIN CAPITAL LETTER M                  */       
    78,         /*  78     N  LATIN CAPITAL LETTER N                  */       
    79,         /*  79     O  LATIN CAPITAL LETTER O                  */       
    80,         /*  80     P  LATIN CAPITAL LETTER P                  */       
    81,         /*  81     Q  LATIN CAPITAL LETTER Q                  */       
    82,         /*  82     R  LATIN CAPITAL LETTER R                  */       
    83,         /*  83     S  LATIN CAPITAL LETTER S                  */       
    84,         /*  84     T  LATIN CAPITAL LETTER T                  */       
    85,         /*  85     U  LATIN CAPITAL LETTER U                  */       
    86,         /*  86     V  LATIN CAPITAL LETTER V                  */       
    87,         /*  87     W  LATIN CAPITAL LETTER W                  */       
    88,         /*  88     X  LATIN CAPITAL LETTER X                  */       
    89,         /*  89     Y  LATIN CAPITAL LETTER Y                  */       
    90,         /*  90     Z  LATIN CAPITAL LETTER Z                  */       
    196,        /*  91     Ä  LATIN CAPITAL LETTER A WITH DIAERESIS   */       
    214,        /*  92     Ö  LATIN CAPITAL LETTER O WITH DIAERESIS   */       
    209,        /*  93     Ñ  LATIN CAPITAL LETTER N WITH TILDE       */       
    220,        /*  94     Ü  LATIN CAPITAL LETTER U WITH DIAERESIS   */       
    167,        /*  95     §  SECTION SIGN                            */       
    191,        /*  96     ¿  INVERTED QUESTION MARK                  */       
    97,         /*  97     a  LATIN SMALL LETTER A                    */       
    98,         /*  98     b  LATIN SMALL LETTER B                    */       
    99,         /*  99     c  LATIN SMALL LETTER C                    */       
    100,        /*  100    d  LATIN SMALL LETTER D                    */       
    101,        /*  101    e  LATIN SMALL LETTER E                    */       
    102,        /*  102    f  LATIN SMALL LETTER F                    */                                       
    103,        /*  103    g  LATIN SMALL LETTER G                    */       
    104,        /*  104    h  LATIN SMALL LETTER H                    */       
    105,        /*  105    i  LATIN SMALL LETTER I                    */       
    106,        /*  106    j  LATIN SMALL LETTER J                    */       
    107,        /*  107    k  LATIN SMALL LETTER K                    */       
    108,        /*  108    l  LATIN SMALL LETTER L                    */       
    109,        /*  109    m  LATIN SMALL LETTER M                    */       
    110,        /*  110    n  LATIN SMALL LETTER N                    */       
    111,        /*  111    o  LATIN SMALL LETTER O                    */       
    112,        /*  112    p  LATIN SMALL LETTER P                    */       
    113,        /*  113    q  LATIN SMALL LETTER Q                    */       
    114,        /*  114    r  LATIN SMALL LETTER R                    */       
    115,        /*  115    s  LATIN SMALL LETTER S                    */       
    116,        /*  116    t  LATIN SMALL LETTER T                    */       
    117,        /*  117    u  LATIN SMALL LETTER U                    */       
    118,        /*  118    v  LATIN SMALL LETTER V                    */       
    119,        /*  119    w  LATIN SMALL LETTER W                    */       
    120,        /*  120    x  LATIN SMALL LETTER X                    */       
    121,        /*  121    y  LATIN SMALL LETTER Y                    */       
    122,        /*  122    z  LATIN SMALL LETTER Z                    */       
    228,        /*  123    ä  LATIN SMALL LETTER A WITH DIAERESIS     */       
    246,        /*  124    ö  LATIN SMALL LETTER O WITH DIAERESIS     */       
    241,        /*  125    ñ  LATIN SMALL LETTER N WITH TILDE         */       
    252,        /*  126    ü  LATIN SMALL LETTER U WITH DIAERESIS     */       
    224         /*  127    à  LATIN SMALL LETTER A WITH GRAVE         */         

/*  The double bytes below must be handled separately after the
    table lookup.
    
    12             27 10      FORM FEED                                       
    94             27 20   ^  CIRCUMFLEX ACCENT                               
    123            27 40   {  LEFT CURLY BRACKET                              
    125            27 41   }  RIGHT CURLY BRACKET                             
    92             27 47   \  REVERSE SOLIDUS (BACKSLASH)                     
    91             27 60   [  LEFT SQUARE BRACKET                             
    126            27 61   ~  TILDE                                           
    93             27 62   ]  RIGHT SQUARE BRACKET                            
    124            27 64   |  VERTICAL BAR                             */

};




/*
 * Use a lookup table to convert from the 7-bit default alphabet
 * used by SMS to an ISO-8859-1 ASCII string. 
 *  
 *  *a7bit   An array of the 7-bit 'string' to convert
 *
 *  length   The length of the a7bit-array
 *
 *  **ascii  A pointer to the string that the result is stored in,
 *           the space is malloced by this function
 *
 *  Returns the length of the ascii-string
 *
 *  Note:  The ascii-string must be free()'ed by te caller
 */

static int convert_7bit_to_ascii(char *a7bit, int length, char **ascii) {
    int     r;
    int     w;

    /* Allocate sufficient memory for the result string */
    *ascii=(char*)malloc(length*2+1);

    w=0;
    for (r=0; r<length; r++) {
        if ((lookup_ascii7to8[(unsigned char)a7bit[r]])!=27) {
            (*ascii)[w++]=lookup_ascii7to8[(unsigned char)a7bit[r]];
        } else {
            /* If we're escaped then the next byte have a special meaning. */
            r++;
            switch (a7bit[r]) {
                case    10:
                    (*ascii)[w++]=12;
                    break;
                case    20:
                    (*ascii)[w++]='^';
                    break;
                case    40:
                    (*ascii)[w++]='{';
                    break;
                case    41:
                    (*ascii)[w++]='}';
                    break;
                case    47:
                    (*ascii)[w++]='\\';
                    break;
                case    60:
                    (*ascii)[w++]='[';
                    break;
                case    61:
                    (*ascii)[w++]='~';
                    break;
                case    62:
                    (*ascii)[w++]=']';
                    break;
               case    64:
                    (*ascii)[w++]='|';
                    break;
                default:
                    (*ascii)[w++]=NPC8;
                    break;
            }
        }
    }

    /* Terminate the result string and realloc to the correct size */
    (*ascii)[w]=0;
    *ascii=(char*)realloc(*ascii,w+1);

    return w;
}    
    


/*
 * Use a lookup table to convert from an ISO-8859-1 string to 
 * the 7-bit default alphabet used by SMS. 
 *  
 *  *scii   The string to convert
 *
 *  **a7bit  A pointer to the array that the result is stored in,
 *           the space is malloced by this function
 *
 *  Returns the length of the a7bit-array
 *
 *  Note:  The a7bit-array must be free()'ed by te caller
 */

static int convert_ascii_to_7bit(char *ascii, char **a7bit) {
    int r;
    int w;

    r=0;
    w=0;

    /* Allocate sufficient memory for the result string */
    *a7bit=(char*)malloc(strlen(ascii)*2+1);

    while (ascii[r]!=0) {
        if ((lookup_ascii8to7[(unsigned char)ascii[r]])<256) {
            (*a7bit)[w++]=abs(lookup_ascii8to7[(unsigned char)ascii[r++]]);
        } else {
            (*a7bit)[w++]=27;
            (*a7bit)[w++]=lookup_ascii8to7[(unsigned char)ascii[r++]]-256;
        }
    }
    
    /* Realloc the result array to the correct size */
    *a7bit=(char*)realloc(*a7bit,w);

    return w;
}





/*
 *  Convert a PDU-coded string to ISO-8859-1 ASCII 
 *
 *  *pdu      The pdu-array to convert to cleartext
 *
 *  pdulength The length of the pdu-array
 *
 *  **ascii   A pointer to the buffer that the cleartext will be written to,
 *            the space for the buffer will be allocated by this function
 *
 *  Returns the length of the ascii-string
 *
 *  Note:  Don't forget to free() the ascii-string when you're finished 
 *         with it.
 *
 */

int pdu_to_ascii(unsigned char *pdu, int pdulength, char **ascii) {
  int   r;
  int   w;
  int   length;
  unsigned char *ascii7bit;

  /* Allocate sufficient memory for the 7-bit string */
  ascii7bit=(unsigned char*)malloc(pdulength*2+1);
  w=0;
  
  for (r=0; r<pdulength; r++) {
    if (r%7==0) {
      ascii7bit[w++]=(pdu[r]<<0)&0x7F;
    } else if (r%7==6) {
      ascii7bit[w++]=((pdu[r]<<6)|(pdu[r-1]>>2))&0x7F;
      ascii7bit[w++]=(pdu[r]>>1)&0x7F;
    } else {
      ascii7bit[w++]=((pdu[r]<<(r%7))|(pdu[r-1]>>(7+1-(r%7))))&0x7F;
    }
  }

  length=convert_7bit_to_ascii((char*)ascii7bit,w,ascii);
  free(ascii7bit);
  
  return length;
}






/*
 *  Convert an ISO-8859-1 ASCII string to an array of PDU-coded bytes
 * 
 *  *ascii  The ISO-cleartext to convert
 *
 *  **pdu   Pointer to an array where the pdu-bytes will be stored in, this
 *          function allocates the neccesary memory for the array
 *
 *  Returns the number of bytes stored in the pdu-array
 *
 *  Note:  Don't forget to free() the pdu-array when you're finished with it.
 *  
 */

int ascii_to_pdu(char *ascii, unsigned char * pdu) {
    int r;
    int w;
    char *ascii7bit;
    int  len7bit;

    /* Start by converting the ISO-string to a 7bit-string */
    len7bit=convert_ascii_to_7bit(ascii,&ascii7bit);
    //*pdu=(unsigned char*)malloc(len7bit);

    /* Now, we can create a PDU string by packing the 7bit-string */
    r=0;
    w=0;
    while (r<len7bit) {
        *(pdu + w)=((ascii7bit[r]>>(w%7))&0x7F) | ((ascii7bit[r+1]<<(7-(w%7)))&0xFF);
        if ((w%7)==6) r++;
        r++;
        w++;
    }
 
    free(ascii7bit);
    return w;
}



