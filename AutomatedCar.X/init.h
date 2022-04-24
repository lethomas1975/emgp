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

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

// TODO Insert appropriate #include <>
#include <xc.h> // include processor files - each processor file is guarded.  

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

#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>

#pragma config FOSC = INTOSCIO_EC   	// Internal oscillator, port function on RA6, EC used by USB. 
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
#pragma config WDT = OFF        // Disable watchdog timer

// definition for Stepper Motor 1 and 2 (left and right)
// SM1 low bits SM2 high bits
#define SMOut LATD
#define SMTrisOut TRISD

// definition for the 7-Segment
#define SevenSEGOut0 LATBbits.LATB1 // RB1 segment b
#define SevenSEGOut1 LATBbits.LATB4 // RB4 segment a
#define SevenSEGOut2 LATBbits.LATB2 // RB2 segment f
#define SevenSEGOut3 LATBbits.LATB3 // RB3 segment g
#define SevenSEGOut4 LATCbits.LATC0 // RC0 segment e
#define SevenSEGOut5 LATCbits.LATC1 // RC1 segment d
#define SevenSEGOut6 LATCbits.LATC2 // RC2 segment c
#define SevenSEGTrisOut0 TRISBbits.TRISB1
#define SevenSEGTrisOut1 TRISBbits.TRISB4
#define SevenSEGTrisOut2 TRISBbits.TRISB2
#define SevenSEGTrisOut3 TRISBbits.TRISB3
#define SevenSEGTrisOut4 TRISCbits.TRISC0
#define SevenSEGTrisOut5 TRISCbits.TRISC1
#define SevenSEGTrisOut6 TRISCbits.TRISC2

// definition for the optical sensor
#define OS1In PORTBbits.RB0
#define OS1TrisIn TRISBbits.RB0

// definition for the Buzzer
#define BUZZOut LATEbits.LATE2
#define BUZZTrisOut TRISEbits.TRISE2


// test led pin
#define LEDRPin LATEbits.LATE0       	// Define LEDPin as PORT E Pin 0 for right turn
#define LEDRTris TRISEbits.TRISE0    	// Define LEDTris as TRISE Pin 0 as output mode
#define LEDPin LATEbits.LATE1       	// Define LEDPin as PORT E Pin 1 for left turn and other tests
#define LEDTris TRISEbits.TRISE1    	// Define LEDTris as TRISE Pin 1 as output mode

// use ADC, comment the line below to use digital
#define C2_USE_ADC

//definition for the Proximity Sensor 1, 2 and 3
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

// prototype of the init function
void init(void);

// global variable whether to increment the 7-Segment counter or decrement.
// 0 to increment and 1 to decrement.
int incrementing = 0;
#endif
