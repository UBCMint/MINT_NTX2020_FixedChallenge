/* 
 * File:   main.c
 * Author: alxshev
 *
 * Created on November 16, 2020, 9:37 PM
 */

#include <stdio.h>
#include <stdlib.h>


// PIC32MX450F256H Configuration Bit Settings

// 'C' source line config statements

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
#pragma config UPLLIDIV = DIV_1         // USB PLL Input Divider (1x Divider)
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
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is Disabled)
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


#define SYS_FREQ 8000000 // 8Mhz

// See  https://www.digikey.com/eewiki/display/microcontroller/Getting+Started+with+the+PIC32+and+MPLAB+X
// for more explanation of UART config
void initUART(void)
{
    RPD3Rbits.RPD3R = 0b0011; // Configure RPD3 pin as U1TX
    U1RXRbits.U1RXR = 0b0000; // Configure RPD2 pin as U1RX
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

void sendSampleData() {
    int i;
    for (i = 1; i < 10; i++) {
        while(U1STAbits.UTXBF);         // Wait while buffer is full
        U1TXREG = i;
    }
}

int main(int argc, char** argv) {
    initUART();
    while(1) {
        // Try this first. It should give a square wave ('U' in ASCII)
        sendChar('U');
        
        // If line above works try uncommenting this line, it sends array of ints
        // sendSampleData();
    }
    return (EXIT_SUCCESS);
}
