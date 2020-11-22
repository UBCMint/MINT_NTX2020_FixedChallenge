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
#include "configuration_bits.c"

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
    SPI1Rbits.SDI1R = MCU_SCI_INDEX;
    RPD4Rbits.RPD4R = MCU_SDO_INDEX;
    // RPD2bits.RPD2R = SCK_INDEX: 
    SCK1Rbits.SCK1R = SCK_INDEX;
    RPE3Rbits.RPE3R = MCU_SS_INDEX; 
    
    LATDbits.LATD1 = 1;         // Set CS high (idle state)
     
    IEC0bits.SPI1EIE = 0;       // SPI interrupts disabled
    IEC0bits.SPI1RXIE = 0;
    IEC0bits.SPI1TXIE = 0;
     
    SPI1CONbits.ON = 0;         // Turn off SPI module
     
    SPI1BUF = 0;                // Clear the receive buffer
     
    SPI1BRG = 33333;                // FSCK = 160 Hz 
     
    SPI1STATbits.SPIROV = 0;    // Clear overflow flag
     
     
    /* SPI1CON settings */
    SPI1CONbits.FRMEN = 0;      // Framed SPI support is disabled
    SPI1CONbits.SIDL = 0;       // Continue operation in IDLE mode
    SPI1CONbits.DISSDO = 0;     // SDO1 pin is controlled by the module
    SPI1CONbits.MODE16 = 1;     // 16 bit mode
    SPI1CONbits.MODE32 = 0;     // 32 bit mode 
    SPI1CONbits.CKP = 1;        // Idle state for clock is high, active state is low
    SPI1CONbits.CKE = 0;        // Output data changes on transition from idle to active
    SPI1CONbits.SSEN = 0;       // Not in slave mode
    SPI1CONbits.MSTEN = 1;      // Yes in master mode
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


// See  https://www.digikey.com/eewiki/display/microcontroller/Getting+Started+with+the+PIC32+and+MPLAB+X
// for more explanation of UART config
void InitUART(void) {
    RPB3Rbits.RPB3R = U1TX_INDEX ;// Configure RPB3 pin as U1TX
    U1RXRbits.U1RXR = U1RX_RPB10_INDEX; // Configure RPB10 pin as U1RX
    
    U1MODEbits.BRGH = 0; // Turn on UART1 module
    U1BRG = 129; // Set Baud Rate; 129 corresponds to 9600. See article above for formula
    
    U1MODEbits.SIDL = 0;                // Continue operation in SLEEP mode
    U1MODEbits.IREN = 0;                // IrDA is disabled
    U1MODEbits.RTSMD = 0;               // U1RTS pin is in Flow Control mode
    U1MODEbits.UEN = 0b00;              // U1TX, U1RX are enabled
    U1MODEbits.WAKE = 1;                // Wake-up enabled
    U1MODEbits.LPBACK = 0;              // Loopback mode is disabled
    U1MODEbits.RXINV = 0;               // U1RX IDLE state is '1'
    U1MODEbits.PDSEL = 0b00;            // 8-bit data, no parity
    U1MODEbits.STSEL = 0;               // 1 stop bit
    U1STAbits.UTXINV = 0;               // U1TX IDLE state is '1'
    U1MODEbits.ON = 1;                  // UART1 is enabled
    U1STAbits.URXEN = 1;                // UART1 receiver is enabled, don't need but just in case
    U1STAbits.UTXEN = 1;                // UART1 transmitter is enabled
}


void sendChar(char c) {
    while(U1STAbits.UTXBF);             // Wait while buffer is full
    U1TXREG = c;                        // Transmit character
}

