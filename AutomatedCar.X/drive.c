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
int STEP_DELAY = 1;
int STEPS_PER_REV = (int) (360.0 / ((5.625/64.0) * 8.0)); // datasheet angle per step 5.625/64

unsigned char FWD[9] = { 0b10000001, 0b11000011, 0b01000010, 0b01100110, 0b00100100, 0b00111100, 0b00011000, 0b10011001, '\0' };
unsigned char LFT[9] = { 0b10001000, 0b11001100, 0b01000100, 0b01100110, 0b00100010, 0b00110011, 0b00010001, 0b10011001, '\0'};
unsigned char RGT[9] = { 0b00010001, 0b00110011, 0b00100010, 0b01100110, 0b01000100, 0b11001100, 0b10001000, 0b10011001, '\0'};
unsigned char BWD[9] = { 0b00011000, 0b00111100, 0b00100100, 0b01100110, 0b01000010, 0b11000011, 0b10000001, 0b10011001, '\0'};

void setLED(int move);

void left() {
    setLED(2);
    for (int j = 0; j < STEPS_PER_REV; j++) {
        for (int i = 0; i < 8; i++) {
            SMOut = LFT[i];
            delayInUs(STEP_DELAY);
        }
    }
}

void leftBackward() {
    setLED(5);
    for (int j = 0; j < STEPS_PER_REV; j++) {
        for (int i = 8; i > 0; i--) {
            SMOut = LFT[i];
            delayInUs(STEP_DELAY);
        }
    }
}

void right() {
    setLED(3);
    for (int j = 0; j < STEPS_PER_REV; j++) {
        for (int i = 0; i < 8; i++) {
            SMOut = RGT[i];
            delayInUs(STEP_DELAY);
        }
    }
}

void rightBackward() {
    setLED(6);
    for (int j = 0; j < STEPS_PER_REV; j++) {
        for (int i = 8; i > 0; i--) {
            SMOut = RGT[i];
            delayInUs(STEP_DELAY);
        }
    }
}

void forward() {
    setLED(1);
    for (int j = 0; j < STEPS_PER_REV; j++) {
        for (int i = 0; i < 8; i++) {
            SMOut = FWD[i];
            delayInUs(STEP_DELAY);
        }
    }
}

void backward() {
    setLED(3);
    for (int j = 0; j < STEPS_PER_REV; j++) {
        for (int i = 0; i < 8; i++) {
            SMOut = BWD[i];
            delayInUs(STEP_DELAY);
        }
    }
}

void uturn() {
    setLED(4);
    leftBackward();
    right();
    uturnBool = ++uturnBool % 2;
}

void setLED(int move) {
    if (direction != move) {
        LEDPin = ~LEDPin;
    }
    direction = move;
}

void proximityDetection() {
    int forwardBool = PS1In == 0;
    int leftBool = PS1In == 1 && PS2In == 0;
    int rightBool = PS1In == 1 && PS2In == 1 && PS3In == 0;
    int uturnBool = PS1In == 1 && PS2In == 1 && PS3In == 1;

    if (forwardBool) {
        forward();
    } else {
        backward();        
        if (leftBool) {
            left();
        } else if (rightBool) {
            right();
        } else if (uturnBool) {
            uturn();
        }
    }
}
