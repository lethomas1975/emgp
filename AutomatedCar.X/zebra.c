/*
 * File:   zebra.c
 * Author: thomas
 *
 * Created on 27 March 2022, 18:43
 */

#include <math.h>

#include "init.h"
#include "common.h"
#include "buzzer.h"
#include "zebra.h"

// current state of the Optical Sensor. only trigger event on state change
int previousState = -1;

// 7-Segment counter
int count = 0;

// global variable whether to increment the 7-Segment counter or decrement.
// 1 to increment and 0 to decrement.
int incrementing = 1;

// private function to set each segment of the 7-Segment display. prototype not defined in header but here
void setSegmentByBit(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f, unsigned char g);

// increment the 7-Segment counter
void increment(void) {
    if (count < 9) {
        count++;
    }
}

// decrement the 7-Segment counter
void decrement(void) {
    if (count > 0) {
        count--;
    }
}

// reset the 7-Segment counter
void resetCounter(void) {
    count = -1;
    previousState = -1;
    incrementing = 1;
}

// increment the 7-Segment counter and display the value
void incrementAndDisplay(void) {
    increment();
    setSevenSegment(count);
}

// decrement the 7-Segment counter and display the value
void decrementAndDisplay(void) {
    decrement();
    setSevenSegment(count);
}

int counterValue(void) {
    return count;
}

void switchIncrement(void) {
    incrementing = (incrementing + 1) % 2;
}

int isIncrementing(void) {
    return incrementing;
}

// implementation of the private prototype
void setSegmentByBit(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f, unsigned char g) {
    SevenSEGOut1 = a;
    SevenSEGOut0 = b;
    SevenSEGOut6 = c;
    SevenSEGOut5 = d;
    SevenSEGOut4 = e;
    SevenSEGOut2 = f;
    SevenSEGOut3 = g;
}

// a | b | c | d | e | f | g | display
// 1 | 1 | 1 | 1 | 1 | 1 | 0 | 0
// 0 | 1 | 1 | 0 | 0 | 0 | 0 | 1
// 1 | 1 | 0 | 1 | 1 | 0 | 1 | 2
// 1 | 1 | 1 | 1 | 0 | 0 | 1 | 3
// 0 | 1 | 1 | 0 | 0 | 1 | 1 | 4
// 1 | 0 | 1 | 1 | 0 | 1 | 1 | 5
// 1 | 0 | 1 | 1 | 1 | 1 | 1 | 6
// 1 | 1 | 1 | 0 | 0 | 0 | 0 | 7
// 1 | 1 | 1 | 1 | 1 | 1 | 1 | 8
// 1 | 1 | 1 | 1 | 0 | 1 | 1 | 9
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
}

void zebraDetected(void) {
    if (previousState != OS1In) {
        previousState = OS1In;
        if (previousState == 1) {
            if (incrementing == 1) {
                incrementAndDisplay();
            } else {
                decrementAndDisplay();
            }
            buzz();
        } else {
            buzzOff();            
        }
    }
}