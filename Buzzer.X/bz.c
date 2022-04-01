/*
 * File:   bz.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:52
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
#include "../AutomatedCar.X/buzzer.h"

void main(void) {
    init();

    BUZZOut = 1;
    
    while (1) {
        BUZZOut = ~BUZZOut;
        delayInMs(500);
    }
}
