/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ     SYS_FREQ 8000000 // 8Mhz
#define FCY          SYS_FREQ

#include "configuration_bits.c"

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void InitSPI(void); 
short WriteReadSPI(unsigned short i); 
void InitUART(void); 
void sendChar(char c);
