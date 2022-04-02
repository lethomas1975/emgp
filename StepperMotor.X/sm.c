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

void step(int a, int b, int c, int d, int delay);

void step(int a, int b, int c, int d, int delay) {
        SM1Out0 = a;
        SM1Out1 = b;
        SM1Out2 = c;
        SM1Out3 = d;
        delayInMs(delay);    
}

void main(void) {
    init();
    
    step(0,0,0,0,100);

    while (1) {
        step(1,0,0,0,1000);
        step(0,1,0,0,1000);
        step(1,1,0,0,1000);
        step(0,0,1,0,1000);
        step(1,0,1,0,1000);
        step(0,1,1,0,1000);
        step(1,1,1,0,1000);
        step(0,0,0,1,1000);
        step(1,0,0,1,1000);
        step(0,1,0,1,1000);
        step(1,1,0,1,1000);
        step(0,0,1,1,1000);
        step(1,0,1,1,1000);
        step(0,1,1,1,1000);
        step(1,1,1,1,1000);
    }
}
