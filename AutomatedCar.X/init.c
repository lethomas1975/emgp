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

void initADC();

void initADC() {
    ADCON1 = 0x0C; // AN0, AN1 and AN2 use Analog
    ADCON2 = 0b10001001; // right alignment, 2TAD and FOSC/8
    ADRESH=0;
    ADRESL=0;
}

void init() {
    ADCON0bits.GO = 0;
    ADCON0bits.ADON = 0;
    
    #ifdef C2_USE_ADC
        initADC();
    #else
        ADCON1 = 0x0F;
        CMCON = 0x07;
    #endif
    
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

    LEDTris = 0;
    LEDRTris = 0;

}
