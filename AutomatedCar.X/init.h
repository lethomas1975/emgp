#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include <stdio.h>
#include <stdlib.h>
#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic18f4550.h>
#endif	/* XC_HEADER_TEMPLATE_H */

#ifndef INIT_H
#define INIT_H

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
#ifndef C2_USE_ADC
#define C2_USE_ADC
#endif

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

#ifdef C2_USE_ADC
void resetAllDigital(void);
#endif
#endif
