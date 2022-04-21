/*
 * File:   bz.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:52
 */

#include "../AutomatedCar.X/init.h"
#include "../AutomatedCar.X/common.h"
#include "../AutomatedCar.X/buzzer.h"

void main(void) {
    init();

    BUZZOut = 0;
    
    while (1) {
        BUZZOut = ~BUZZOut;
        delayInMs(50);
    }
}
