/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#define _SUPPRESS_PLIB_WARNING //SurpressesPlib warnings

#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>            /* Include to use PIC32 peripheral libraries     */
#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* TODO Initialize User Ports/Peripherals/Project here */

void InitJellyfish(void) {
    
}


short ReadEEG(void) {
    short X_H = WriteReadSPI(0b1010100100000000);    // Read first data register
    short X_L = WriteReadSPI(0b1010100000000000);    // Read second data register
    X_L = X_L & 0b0000000011111111;                  // Combine the data from both registers
    X_H = X_H << 8;
    X_H = X_H & 0b1111111100000000;
    signed short X = X_H | X_L;
    float value = X * 0.000061;                      // Convert to units of g
    return value;
}


void sendSampleDataUART() {
    int i;
    for (i = 1; i < 10; i++) {
        while(U1STAbits.UTXBF);         // Wait while buffer is full
        U1TXREG = i;
    }
}
