/*
 * File:   os.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:47
 */

#include "../AutomatedCar.X/init.h"
#include "../AutomatedCar.X/common.h"
#include "../AutomatedCar.X/buzzer.h"
#include "../AutomatedCar.X/zebra.h"

void main(void) {
    init();
    buzzOff();
    
    while (1) {
        LEDPin = ~OS1In;
        zebraDetected();
        //delayInMs(100);
    }
}
