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
    
    SevenSEGOut = 0;
    SevenSEGTrisOut = 0;

    //PS1In = 0;
    //PS2In = 0;
    //PS3In = 0;
    PS1TrisIn = 1;
    PS2TrisIn = 1;
    PS3TrisIn = 1;

    OS1In = 1;
    OS1TrisIn = 1;

    BUZZOut = 0;
    BUZZOut = 1; // to switch off after initialization
    BUZZTrisOut = 0;

    SM1Out0 = 0;
    SM1Out1 = 0;
    SM1Out2 = 0;
    SM1Out3 = 0;
    SM2Out0 = 0;
    SM2Out1 = 0;
    SM2Out2 = 0;
    SM2Out3 = 0;
    SM1TrisOut0 = 0;
    SM1TrisOut1 = 0;
    SM1TrisOut2 = 0;
    SM1TrisOut3 = 0;
    SM2TrisOut0 = 0;
    SM2TrisOut1 = 0;
    SM2TrisOut2 = 0;
    SM2TrisOut3 = 0;

    LEDTris = 0;	//Set LED Pin data direction to OUTPUT

}
