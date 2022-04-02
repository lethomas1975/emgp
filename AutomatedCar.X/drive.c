/*
 * File:   drive.c
 * Author: thomas
 *
 * Created on 27 March 2022, 18:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

#include "init.h"
#include "common.h"
#include "drive.h"

void left(int step) {
    LEDPin = ~LEDPin;
    delayInMs(500);
}

void right(int step) {
    LEDPin = ~LEDPin;
    delayInMs(500);
}

void forward(int step) {
    LEDPin = ~LEDPin;
    delayInMs(500);
}

void backward(int step) {
    LEDPin = ~LEDPin;
    delayInMs(500);
}

void uturn() {
    LEDPin = ~LEDPin;
    delayInMs(500);
    uturnBool = ++uturnBool % 2;
}

void proximityDetection() {
    int forwardBool = PS1In == 0;
    int leftBool = PS1In == 1 && PS2In == 0;
    int rightBool = PS1In == 1 && PS2In == 1 && PS3In == 0;
    int uturnBool = PS1In == 1 && PS2In == 1 && PS3In == 1;

    if (forwardBool) {
        forward(1);
    } else {
        backward(1);        
        if (leftBool) {
            left(1);
        } else if (rightBool) {
            right(1);
        } else if (uturnBool) {
            uturn();
        }
    }
    
}
