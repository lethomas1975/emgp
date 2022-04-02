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

int direction = 0;

void setLED(int move);

void left(int step) {
    setLED(2);
}

void right(int step) {
    setLED(3);
}

void forward(int step) {
    setLED(1);
}

void backward(int step) {
    setLED(3);
}

void uturn() {
    setLED(4);
    uturnBool = ++uturnBool % 2;
}

void setLED(int move) {
    if (direction != move) {
        LEDPin = ~LEDPin;
        delayInMs(500);
    } else { 
        delayInMs(100);
    }
    direction = move;

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
