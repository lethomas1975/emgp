/*
 * File:   init.c
 * Author: thomas
 *
 * Created on 27 March 2022, 18:17
 */

#include "init.h"

#ifdef C2_USE_ADC
    // ADC init. will only be visible we activate ADC and defining C2_USE_ADC
    void initADC(void);

    void initADC(void) {
        ADCON1 = 0x0C; // AN0, AN1 and AN2 use Analog
        ADCON2 = 0b10001001; // right alignment, 2TAD and FOSC/8
        ADRESH=0;
        ADRESL=0;
    }

    void resetAllDigital(void) {
        ADCON1 = 0x0F;
        CMCON = 0x07;
    }
#endif

void init(void) {
    // disabling ADC
    ADCON0bits.GO = 0;
    ADCON0bits.ADON = 0;
    
    #ifdef C2_USE_ADC
        initADC();
    #else
        // set all ports to digital
        ADCON1 = 0x0F;
        CMCON = 0x07;
    #endif
    
    // set Stepper Motor as output (TRIS to 0) and reset the pins to 0
    SMOut = 0;
    SMTrisOut = 0;

    // set the Proximity sensors as input (TRIS to 1) and reset the pins to 0
    PS1In = 0;
    PS2In = 0;
    PS3In = 0;
    PS1TrisIn = 1;
    PS2TrisIn = 1;
    PS3TrisIn = 1;

    // set the optical sensor as input (TRIS to 1) and reset the pin to 0
    OS1In = 0;
    OS1TrisIn = 1;

    // set the buzzer as output (TRIS to 0) and reset the pin to 0
    BUZZOut = 0;
    BUZZTrisOut = 0;

    // set 7-Segment as output (TRIS to 0) and reset the pins to 0
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

    // set the LED as output (TRIS to 0)
    LEDPin = 0;
    LEDRPin = 0;
    LEDTris = 0;
    LEDRTris = 0;

}
