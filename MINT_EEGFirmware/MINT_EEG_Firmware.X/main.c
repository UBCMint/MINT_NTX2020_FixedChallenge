/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/

#define _SUPPRESS_PLIB_WARNING //SurpressesPlib warnings

#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
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
