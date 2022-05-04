/*
 * File:   common.c
 * Author: thomas
 *
 * Created on 01 April 2022, 04:53
 */

#include "common.h"

void delayInMs(int ms) {
    if (ms/10 > 1) {
        for (int i = 0; i < ms / 10; i++) {
            _delay(10);
        }
    } else {
        _delay(1);
    }
}

void delayInUs(int us) {

    if (us/10 >= 1) {
        for (int i = 0; i < us / 10; i++) {
            _delay(10);
        }
    } else {
        _delay(5);
    }
}
