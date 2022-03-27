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

#include "../AutomatedCar.X/init.h"
#include "../AutomatedCar.X/zebra.h"

void increment() {
    // increment a counter
    // set the 7 segment based on the counter
}

void decrement() {
    // let see if we need that one
}

void zebraDetected() {
    if (OS1In == 1) {
        increment();
    }
}