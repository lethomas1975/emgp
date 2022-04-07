/*
 * File:   buzzer.c
 * Author: thomas
 *
 * Created on 27 March 2022, 18:15
 */


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

#include "init.h"
#include "common.h"
#include "buzzer.h"


void buzz() {
    BUZZOut = 1;
    delayInMs(50);
}

void buzzOff() {
    BUZZOut = 0;
}