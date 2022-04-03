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
int STEPS = 2048;

unsigned char FWD_STEP1 = 0x99; //0b10011001
unsigned char FWD_STEP2 = 0x55; //0b01010101
unsigned char FWD_STEP3 = 0x66; //0b01100110
unsigned char FWD_STEP4 = 0xAA; //0b10011001

unsigned char BWD_STEP1 = 0xAA; //0b10011001
unsigned char BWD_STEP2 = 0x66; //0b01010101
unsigned char BWD_STEP3 = 0x55; //0b01100110
unsigned char BWD_STEP4 = 0x99; //0b10011001

unsigned char LFT_STEP1 = 0xA9; //0b10011001
unsigned char LFT_STEP2 = 0x65; //0b01010101
unsigned char LFT_STEP3 = 0x56; //0b01100110
unsigned char LFT_STEP4 = 0x9A; //0b10011001

unsigned char RGT_STEP1 = 0x9A; //0b10011001
unsigned char RGT_STEP2 = 0x56; //0b01010101
unsigned char RGT_STEP3 = 0x65; //0b01100110
unsigned char RGT_STEP4 = 0xA9; //0b10011001

void setLED(int move);

void left(int step) {
    setLED(2);
    for (int i = 0; i < step; i++) {
        SMOut = LFT_STEP1;
        delayInMs(10);
        SMOut = LFT_STEP2;
        delayInMs(10);
        SMOut = LFT_STEP3;
        delayInMs(10);
        SMOut = LFT_STEP4;
        delayInMs(10);
    }
}

void right(int step) {
    setLED(3);
    for (int i = 0; i < step; i++) {
        SMOut = RGT_STEP1;
        delayInMs(10);
        SMOut = RGT_STEP2;
        delayInMs(10);
        SMOut = RGT_STEP3;
        delayInMs(10);
        SMOut = RGT_STEP4;
        delayInMs(10);
    }
}

void forward(int step) {
    setLED(1);
    for (int i = 0; i < step; i++) {
        SMOut = FWD_STEP1;
        delayInMs(10);
        SMOut = FWD_STEP2;
        delayInMs(10);
        SMOut = FWD_STEP3;
        delayInMs(10);
        SMOut = FWD_STEP4;
        delayInMs(10);
    }

}

void backward(int step) {
    setLED(3);
    for (int i = 0; i < step; i++) {
        SMOut = BWD_STEP1;
        delayInMs(10);
        SMOut = BWD_STEP2;
        delayInMs(10);
        SMOut = BWD_STEP3;
        delayInMs(10);
        SMOut = BWD_STEP4;
        delayInMs(10);
    }
}

void uturn() {
    setLED(4);
    uturnBool = ++uturnBool % 2;
    for (int i = 0; i < STEPS; i++) {
        left(STEPS);
    }
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
        forward(STEPS);
    } else {
        backward(STEPS);        
        if (leftBool) {
            left(STEPS);
        } else if (rightBool) {
            right(STEPS);
        } else if (uturnBool) {
            uturn();
        }
    }
    
}
