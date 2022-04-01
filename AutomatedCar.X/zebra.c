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
#include "buzzer.h"
#include "zebra.h"

int count = 0;

void increment() {
    count = (count + 1) % 10;
    // set the 7 segment based on the counter
}

void decrement() {
    count = (count - 1) % 10;
    // let see if we need that one
}

void zebraDetected() {
    if (OS1In == 1) {
        increment();
        buzz();
        buzzOff();
    } else {
        buzzOff();
    }
}