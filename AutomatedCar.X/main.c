/*
 * File:   main.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:53
 */
#include "init.h"
#include "common.h"
#include "drive.h"
#include "zebra.h"
#include "buzzer.h"

void main(void) {
    init();
    for (int i = 0; i < 5; i++) {
        LEDPin = ~LEDPin;
        LEDRPin = ~LEDPin;
        delayInMs(30);
    }
    LEDPin = 0;
    LEDRPin = 0;
    int stop = 0;
    while (!stop) {
        proximityDetection();
        if (isIncrementing() == 0 && counterValue() == 0) {
            stop = 1;
        }
    }
    resetAllDigital();
    resetCounter();
    buzz();
    delayInMs(50);
    buzzOff();
    delayInMs(50);
    buzz();
    delayInMs(50);
    buzzOff();
}
