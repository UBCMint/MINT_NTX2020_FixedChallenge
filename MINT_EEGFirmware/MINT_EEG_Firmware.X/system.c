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
#include "system.h"          /* variables/params used by system.c             */

/******************************************************************************/
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c                                           */
/*                                                                            */
/******************************************************************************/

/* <Initialize variables in system.h and put code for system code here.>      */

void InitSPI(void) {
    LATDbits.LATD1 = 1;                     // Set CS high (idle state)
     
    IEC0bits.SPI1EIE = 0;       // SPI interrupts disabled
    IEC0bits.SPI1RXIE = 0;
    IEC0bits.SPI1TXIE = 0;
     
    SPI1CONbits.ON = 0;         // Turn off SPI module
     
    SPI1BUF = 0;                // Clear the receive buffer
     
    SPI1BRG = 62499;                // FSCK = 160 Hz 
     
    SPI1STATbits.SPIROV = 0;    // Clear overflow flag
     
     
    /* SPI1CON settings */
    SPI1CONbits.FRMEN = 0;      // Framed SPI support is disabled
    SPI1CONbits.SIDL = 0;       // Continue operation in IDLE mode
    SPI1CONbits.DISSDO = 0;     // SDO1 pin is controlled by the module
    SPI1CONbits.MODE16 = 1;     // 16 bit mode
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.CKP = 1;        // Idle state for clock is high, active state is low
    SPI1CONbits.CKE = 0;        // Output data changes on transition from idle to active
    SPI1CONbits.SSEN = 0;       // Not in slave mode
    SPI1CONbits.MSTEN = 1;      // Master mode
    SPI1CONbits.SMP = 1;        // Input data sampled at the end of data output time
     
    SPI1CONbits.ON = 1;         // Turn module on
}


short WriteReadSPI(unsigned short i) {
    TRISDbits.TRISD1 = 0;           // Set the chip select low
    SPI1BUF = i;                    // Write to buffer for transmission
    while (!SPI1STATbits.SPIRBF);   // Wait for transfer to be completed
    TRISDbits.TRISD1 = 1;           // Set the chip select back high
    return SPI1BUF;                 // Return the received value
}
