/*
 * File:   os.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:47
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
#include "../AutomatedCar.X/zebra.h"

// change the port and its pin number depending on your own design.


void main(void) {
    init();
    buzzOff();
    
    while (1) {
        if (OS1In == 0) {
            LEDPin = 1;	// Toggle LED Pin
        } else {
            LEDPin = 0;
        }
        //LEDPin = ~OS1In;
        zebraDetected();
        delayInMs(100);
    }
}
