/*
 * File:   common.c
 * Author: thomas
 *
 * Created on 01 April 2022, 04:53
 */

#include "common.h"

/**
 * delayInMs()
 * delay in millisecond
 *
 * Parameters:
 *  ms: milliseconds to delay
 * 
 * Author: Thomas Le 01/04/2022
 */
void delayInMs(int ms) {
    if (ms/10 > 1) {
        for (int i = 0; i < ms / 10; i++) {
            _delay(10);
        }
    } else {
        _delay(1);
    }
}

/**
 * delayInUs()
 * delay in microsecond
 *
 * Parameters:
 *  us: microseconds to delay
 * 
 * Author: Thomas Le 01/04/2022
 */
void delayInUs(int us) {

    if (us/10 >= 1) {
        for (int i = 0; i < us / 10; i++) {
            _delay(10);
        }
    } else {
        _delay(5);
    }
}
