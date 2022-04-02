/*
 * File:   zebra.c
 * Author: thomas
 *
 * Created on 27 March 2022, 18:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

#include "init.h"
#include "common.h"
#include "drive.h"
#include "buzzer.h"
#include "zebra.h"

int count = -1;
int direction = 0;

void increment() {
    count = (count + 1) % 10;
    // set the 7 segment based on the counter
    setSevenSegment(count);
}

void decrement() {
    count = (count - 1) % 10;
    if (count < 0) {
        count = ~count;
    }
    // let see if we need that one
    setSevenSegment(count);
}

void setSevenSegment(int count) {
    switch (count) {
        case 0:
            SevenSEGOut = 0b00111111;
            break;
        case 1:
            SevenSEGOut = 0b00100001;
            break;
        case 2:
            SevenSEGOut = 0b01110110;
            break;
        case 3:
            SevenSEGOut = 0b01110101;
            break;
        case 4:
            SevenSEGOut = 0b01101001;
            break;
        case 5:
            SevenSEGOut = 0b01011101;
            break;
        case 6:
            SevenSEGOut = 0b01011111;
            break;
        case 7:
            SevenSEGOut = 0b00110001;
            break;
        case 8:
            SevenSEGOut = 0b01111111;
            break;
        case 9:
            SevenSEGOut = 0b01111101;
            break;            
    }
    delayInMs(100);
}

void zebraDetected() {
    if (OS1In == 0) {
        if (uturnBool == 0) {
            increment();
        } else {
            decrement();
        }
        buzz();
        buzzOff();
    } else {
        buzzOff();
    }
}