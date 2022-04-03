/*
 * File:   init.c
 * Author: thomas
 *
 * Created on 27 March 2022, 18:17
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

#include "init.h"

void init() {
    ADCON1 = 0x0F;
    CMCON = 0x07;
    
    /*SevenSEGOut = 0;
    SevenSEGTrisOut = 0;*/
    
    SMOut = 0;
    SMTrisOut = 0;

    PS1In = 0;
    PS2In = 0;
    PS3In = 0;
    PS1TrisIn = 1;
    PS2TrisIn = 1;
    PS3TrisIn = 1;

    OS1In = 0;
    OS1TrisIn = 1;

    BUZZOut = 0;
    BUZZOut = 1; // to switch off after initialization
    BUZZTrisOut = 0;

    SevenSEGOut0 = 0;
    SevenSEGOut1 = 0;
    SevenSEGOut2 = 0;
    SevenSEGOut3 = 0;
    SevenSEGOut4 = 0;
    SevenSEGOut5 = 0;
    SevenSEGOut6 = 0;
    SevenSEGTrisOut0 = 0;
    SevenSEGTrisOut1 = 0;
    SevenSEGTrisOut2 = 0;
    SevenSEGTrisOut3 = 0;
    SevenSEGTrisOut4 = 0;
    SevenSEGTrisOut5 = 0;
    SevenSEGTrisOut6 = 0;

    LEDTris = 0;	//Set LED Pin data direction to OUTPUT

}
