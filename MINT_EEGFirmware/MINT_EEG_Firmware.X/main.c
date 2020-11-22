/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
// PIC32MX460F512L Configuration Bit Settings

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config FSRSSEL = PRIORITY_7     // Shadow Register Set Priority Select (SRS Priority 7)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = ON           // USB VBUS ON Selection (Controlled by USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider (2x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_4         // System PLL Output Clock Divider (PLL Divide by 4)

// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc with PLL)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#define _SUPPRESS_PLIB_WARNING //SurpressesPlib warnings

#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"           /* User funct/params, such as InitApp             */ 
#include "configuration_bits.c" 

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint32_t <variable_name>; */
#define CS = TRISDbits.TRISD1
#define U1RX_RPB10_INDEX 0b0110
#define U1TX_INDEX 0b0011
#define DRDY_INDEX 0b0000       // pin 49 - same as SCK?? 
#define MCU_SCI_INDEX 1b0000    // pin 51 
#define MCU_SDO_INDEX 0b1000    // pin 52 
#define MCU_SS_INDEX 0b0111     // pin 63
#define SCK_INDEX 0b0000        // pin 50 - same as DRDY? 

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int32_t main(void)
{

#ifndef PIC32_STARTER_KIT
    /*The JTAG is on by default on POR.  A PIC32 Starter Kit uses the JTAG, but
    for other debug tool use, like ICD 3 and Real ICE, the JTAG should be off
    to free up the JTAG I/O */
    DDPCONbits.JTAGEN = 0;
#endif

    /* Initialize I/O and Peripherals for application */
    TRISDbits.TRISD1 = 0;       // make CS an output
    InitSPI();
    InitJellyfish(); 
    InitUART(); 
    float EEGsignal; 

    while(1)
    {
        // SPI transfer ----------
        EEGsignal = ReadEEG(); 
        
        // processing ------------
        // TODO turn float value stored in EEGsignal into an array to be sent over 
        // UART to a computer 
        
        // UART transfer ---------
        // Try this first. It should give a square wave ('U' in ASCII)
        sendChar('U');
        
        // If line above works try uncommenting this line, it sends array of ints
        // sendSampleDataUART();

    }
    
    return(EXIT_SUCCESS); 
}


void InitSPI(void) {
    SPI1Rbits.SDI1R = MCU_SCI_INDEX;
    RPD1Rbits.RPD1R = DRDY_INDEX;
    RPD4Rbits.RPD4R = MCU_SDO_INDEX;
    // RPD2bits.RPD2R = SCK_INDEX: 
    SCK1Rbits.SCK1R = SCK_INDEX;
    RPE3Rbits.RPE3R = MCU_SS_INDEX; 
    
    LATDbits.LATD1 = 1;         // Set chip select high (idle state)
     
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
