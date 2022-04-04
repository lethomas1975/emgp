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

void main(void) {
    init();
    while (1) {
        forward();
        delayInMs(100);
        left();
        delayInMs(100);
        leftBackward();
        delayInMs(100);
        right();
        delayInMs(100);
        rightBackward();
        delayInMs(100);
        backward();
        delayInMs(100);
        uturn();
        delayInMs(100);
    }
}
