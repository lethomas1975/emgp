/*
 * File:   7s.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:51
 */
#include "../AutomatedCar.X/init.h"
#include "../AutomatedCar.X/common.h"
#include "../AutomatedCar.X/zebra.h"

void main(void) {
    init();
    
    while (1) {
        for (int i = 0; i < 10; i++) {
            incrementAndDisplay();
            delayInMs(100);
        }
        increment();
        for (int i = 0; i < 10; i++) {
            decrementAndDisplay();
            delayInMs(100);
        }
        resetCounter();
    }
}
