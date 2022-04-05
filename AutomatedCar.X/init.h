/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>                     //xc8 compiler header file.
#include <pic18f4550.h>
//#include <p18f4550.h>

//#pragma config FOSC = INTOSC_HS  	// Internal oscillator, HS used by USB.
#pragma config FOSC = INTOSCIO_EC   	// Internal oscillator, port function on RA6, EC used by USB. 
#pragma config WDT = OFF            	// Disable watchdog timer

#define SMOut LATD
#define SMTrisOut TRISD

#define SevenSEGOut0 LATBbits.LATB0 // RB0 b
#define SevenSEGOut1 LATBbits.LATB1 // RB1 a
#define SevenSEGOut2 LATBbits.LATB2 // RB2 f
#define SevenSEGOut3 LATBbits.LATB3 // RB3 g
#define SevenSEGOut4 LATEbits.LATE0 // RE0 e
#define SevenSEGOut5 LATEbits.LATE1 // RE1 d
#define SevenSEGOut6 LATEbits.LATE2 // RE2 c
#define SevenSEGTrisOut0 TRISBbits.TRISB0
#define SevenSEGTrisOut1 TRISBbits.TRISB1
#define SevenSEGTrisOut2 TRISBbits.TRISB2
#define SevenSEGTrisOut3 TRISBbits.TRISB3
#define SevenSEGTrisOut4 TRISEbits.TRISE0
#define SevenSEGTrisOut5 TRISEbits.TRISE1
#define SevenSEGTrisOut6 TRISEbits.TRISE2

#define OS1In PORTCbits.RC0
#define OS1TrisIn TRISCbits.RC0

#define BUZZOut LATCbits.LATC1
#define BUZZTrisOut TRISCbits.TRISC1


// test led pin
#define LEDPin LATCbits.LATC2       	// Define LEDPin as PORT C Pin 0
#define LEDTris TRISCbits.TRISC2    	// Define LEDTris as TRISC Pin 0 as output mode

// use ADC comment the line below to use digital
//#define C2_USE_ADC

#ifdef C2_USE_ADC
    #define PS1In PORTAbits.AN0 // front
    #define PS2In PORTAbits.AN1 // left
    #define PS3In PORTAbits.AN2 // right
#else
    #define PS1In PORTAbits.RA0 // front
    #define PS2In PORTAbits.RA1 // left
    #define PS3In PORTAbits.RA2 // right
#endif

#define PS1TrisIn TRISAbits.TRISA0
#define PS2TrisIn TRISAbits.TRISA1
#define PS3TrisIn TRISAbits.TRISA2

void init();


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

