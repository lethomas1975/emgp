/*
 * File:   common.c
 * Author: thomas
 *
 * Created on 01 April 2022, 04:53
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

#include "common.h"

void delayInMs(int ms) {
    for (int i = 0; i < ms / 10; i++) {
        __delay_ms(10);
    }    
}
