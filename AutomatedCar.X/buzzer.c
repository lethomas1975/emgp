/*
 * File:   buzzer.c
 * Author: thomas
 *
 * Created on 27 March 2022, 18:15
 */
#include "init.h"
#include "common.h"
#include "buzzer.h"


void buzz(void) {
    BUZZOut = 1;
    delayInMs(50);
}

void buzzOff(void) {
    BUZZOut = 0;
}