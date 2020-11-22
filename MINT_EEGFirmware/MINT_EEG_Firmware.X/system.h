/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

#define MCU_SCI_INDEX 1b0000    // pin 51 
#define MCU_SDO_INDEX 0b1000    // pin 52 
#define MCU_SS_INDEX 0b0111     // pin 63
#define SCK_INDEX 0b0000        // pin 50 

/* Define system operating frequency */
#define SYS_FREQ     SYS_FREQ 8000000 // 8Mhz
/* Microcontroller MIPs (FCY) */
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
