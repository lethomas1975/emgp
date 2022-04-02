/*
 * File:   7s.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:51
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
#include "../AutomatedCar.X/zebra.h"

void main(void) {
    init();
    
    while (1) {
        for (int i = 0; i < 10; i++) {
            incrementAndDisplay();
        }
        increment();
        for (int i = 0; i < 10; i++) {
            decrementAndDisplay();
        }
        resetCounter();
    }
}
