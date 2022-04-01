/*
 * File:   main.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:53
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

//#pragma config FOSC = INTOSC_HS  	// Internal oscillator, HS used by USB.
#pragma config FOSC = INTOSCIO_EC   	// Internal oscillator, port function on RA6, EC used by USB. 
#pragma config WDT = OFF            	// Disable watchdog timer

#include "init.h"
#include "common.h"
#include "drive.h"
#include "zebra.h"
#include "buzzer.h"

void main(void) {
    init();
    
    while (1) {
        // drive
    }
}
