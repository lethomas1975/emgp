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
#include <math.h>

#include "init.h"
#include "common.h"
#include "drive.h"
#include "buzzer.h"
#include "zebra.h"

int count = -1;
int currentState = -1;

void increment() {
    count++;
}

void decrement() {
    count--;
}

void resetCounter() {
    count = -1;
}

void incrementAndDisplay() {
    increment();
    setSevenSegment(count);
}

void decrementAndDisplay() {
    decrement();
    setSevenSegment(count);
}

void setSegmentByBit(int a, int b, int c, int d, int e, int f, int g) {
    SevenSEGOut0 = b;
    SevenSEGOut1 = a;
    SevenSEGOut2 = f;
    SevenSEGOut3 = g;
    SevenSEGOut4 = e;
    SevenSEGOut5 = d;
    SevenSEGOut6 = c;
}

void setSevenSegment(int display) {
    int tmp = abs(display) % 10;
    switch (tmp) {
        case 0:
            setSegmentByBit(1, 1, 1, 1, 1, 1, 0);
            break;
        case 1:
            setSegmentByBit(0, 1, 1, 0, 0, 0, 0);
            break;
        case 2:
            setSegmentByBit(1, 1, 0, 1, 1, 0, 1);
            break;
        case 3:
            setSegmentByBit(1, 1, 1, 1, 0, 0, 1);
            break;
        case 4:
            setSegmentByBit(0, 1, 1, 0, 0, 1, 1);
            break;
        case 5:
            setSegmentByBit(1, 0, 1, 1, 0, 1, 1);
            break;
        case 6:
            setSegmentByBit(1, 0, 1, 1, 1, 1, 1);
            break;
        case 7:
            setSegmentByBit(1, 1, 1, 0, 0, 0, 0);
            break;
        case 8:
            setSegmentByBit(1, 1, 1, 1, 1, 1, 1);
            break;
        case 9:
            setSegmentByBit(1, 1, 1, 1, 0, 1, 1);
            break;            
    }
    delayInMs(10);
}

void zebraDetected() {
    if (currentState != OS1In) {
        currentState = OS1In;
        if (currentState == 0) {
            if (uturnBool == 0) {
                incrementAndDisplay();
            } else {
                decrementAndDisplay();
            }
            buzz();
            buzzOff();
        } else if (currentState == 1) {
            buzzOff();
        }
    }
}