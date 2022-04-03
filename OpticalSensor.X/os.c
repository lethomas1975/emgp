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

#include "../AutomatedCar.X/init.h"
#include "../AutomatedCar.X/common.h"
#include "../AutomatedCar.X/buzzer.h"
#include "../AutomatedCar.X/zebra.h"

// change the port and its pin number depending on your own design.


void main(void) {
    init();
    buzzOff();
    
    while (1) {
        LEDPin = ~OS1In;
        zebraDetected();
    }
}
