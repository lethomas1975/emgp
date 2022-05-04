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
int incremented = 0;

// private function to set each segment of the 7-Segment display. prototype not defined in header but here
void setSegmentByBit(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f, unsigned char g);

/**
 * hasIncremented()
 * check if there has been an increment
 * 
 * Return:
 *  0 if no increment
 *  1 for increment
 * 
 * Author: Thomas Le 03/05/2022
 */
int hasIncremented(void) {
    return incremented;
}

/**
 * increment()
 * increment the 7-Segment counter
 * 
 * Author: Lily Zhang 27/03/2022
 * Author: Thomas Le 03/05/2022
 */
void increment(void) {
    incremented = 1;
    if (count < 9) {
        count++;
    }
}

/**
 * decrement()
 * decrement the 7-Segment counter
 * 
 * Author: Lily Zhang 27/03/2022
 */
void decrement(void) {
    if (count > 0) {
        count--;
    }
}

/**
 * resetCounter()
 * reset the 7-Segment counter
 * 
 * Author: Lily Zhang 27/03/2022
 */
void resetCounter(void) {
    count = -1;
    previousState = -1;
    incrementing = 1;
}

/**
 * incrementAndDisplay()
 * increment the 7-Segment counter and display the value
 * 
 * Author: Lily Zhang 27/03/2022
 */
void incrementAndDisplay(void) {
    increment();
    setSevenSegment(count);
}

/**
 * decrementAndDisplay()
 * decrement the 7-Segment counter and display the value
 * 
 * Author: Lily Zhang 27/03/2022
 */
void decrementAndDisplay(void) {
    decrement();
    setSevenSegment(count);
}

/**
 * counterValue()
 * get the count
 * 
 * Return:
 *  the count is return
 * 
 * Author: Thomas Le 03/05/2022
 */
int counterValue(void) {
    return count;
}

/**
 * switchIncrement()
 * switch between incrementing and decrementing
 * 
 * Return:
 *  the count is return
 * 
 * Author: Thomas Le 03/05/2022
 */
void switchIncrement(void) {
    incrementing = (incrementing + 1) % 2;
}

/**
 * isIncrementing()
 * check if it is incrementing or decrementing
 * 
 * Return:
 *  0 for decrementing
 *  1 for incrementing
 * 
 * Author: Thomas Le 03/05/2022
 */
int isIncrementing(void) {
    return incrementing;
}

/**
 * setSegmentByBit()
 * setting each segment its value
 * 
 * Parameters:
 *  a: segment a either 0 or 1
 *  b: segment b either 0 or 1
 *  c: segment c either 0 or 1
 *  d: segment d either 0 or 1
 *  e: segment e either 0 or 1
 *  f: segment f either 0 or 1
 *  g: segment g either 0 or 1
 * 
 * Author: Lily Zhang 27/03/2022
 */
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
/**
 * setSevenSegment()
 * display the count on the display
 * 
 * Parameters:
 *  display: value to display
 * 
 * Author: Lily Zhang 27/03/2022
 */
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

/**
 * zebraDetected()
 * detection of the zebra and display the count and buzz
 * 
 * 
 * Author: Thomas Le 02/04/2022
 */
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