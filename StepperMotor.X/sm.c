/*
 * File:   sm.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:49
 */

#include "../AutomatedCar.X/init.h"
#include "../AutomatedCar.X/common.h"
#include "../AutomatedCar.X/drive.h"

void main(void) {
    init();
    while (1) {
        forward();
        left();
        right();
        backward();
        forward();
        uturn();
        delayInMs(1000);
    }
}
