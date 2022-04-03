/*
 * File:   sm.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

//#pragma config FOSC = INTOSC_HS  	// Internal oscillator, HS used by USB.
#pragma config FOSC = INTOSCIO_EC   	// Internal oscillator, port function on RA6, EC used by USB. 
#pragma config WDT = OFF            	// Disable watchdog timer

#include "../AutomatedCar.X/init.h"
#include "../AutomatedCar.X/common.h"
#include "../AutomatedCar.X/drive.h"

unsigned char STEP1 = 0x99; //0b10011001
unsigned char STEP2 = 0x55; //0b01010101
unsigned char STEP3 = 0x66; //0b01100110
unsigned char STEP4 = 0xAA; //0b10011001

void main(void) {
    init();
    
    
    while (1) {
        SMOut = STEP1;
        delayInMs(10);
        SMOut = STEP2;
        delayInMs(10);
        SMOut = STEP3;
        delayInMs(10);
        SMOut = STEP4;
        delayInMs(10);
    }
}
