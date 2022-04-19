/*
 * File:   ps.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

//#pragma config FOSC = INTOSC_HS  	// Internal oscillator, HS used by USB.
#pragma config FOSC = INTOSCIO_EC   	// Internal oscillator, port function on RA6, EC used by USB. 
#pragma config WDT = OFF            	// Disable watchdog timer

#include "../AutomatedCar.X/init.h"
#include "../AutomatedCar.X/common.h"
#include "../AutomatedCar.X/common_adc.h"
#include "../AutomatedCar.X/drive.h"
#include "../AutomatedCar.X/buzzer.h"

void main(void) {
    init();
    while (1) {
#ifdef C2_USE_ADC
    int ps1 = convertVoltageToDigital(readChannel(0));
    int ps2 = convertVoltageToDigital(readChannel(1));
    int ps3 = convertVoltageToDigital(readChannel(2));
#else
    int ps1 = PS1In;
    int ps2 = PS2In;
    int ps3 = PS3In;
#endif
        int forwardBool = ps1 == 0 && ps2 == 0 && ps3 == 0;
        int leftBool = (ps1 == 1 && ps2 == 0 && ps3 == 0) || (ps1 == 1 && ps2 == 0 && ps3 == 1);
        int slightLeftBool = ps1 == 0 && ps2 == 0 && ps3 == 1;
        int rightBool = ps1 == 1 && ps2 == 1 && ps3 == 0;
        int slightRightBool = ps1 == 0 && ps2 == 1 && ps3 == 0;
        int uturnBool = (ps1 == 1 && ps2 == 1 && ps3 == 1) || (ps1 == 0 && ps2 == 1 && ps3 == 1);

        if (forwardBool) {
            buzz();
            buzzOff();
            delayInMs(50);
        } else {
            if (leftBool) {
                buzzOff();
                delayInMs(100);
            } else if (slightLeftBool) {
                buzzOff();
                delayInMs(100);
            } else if (rightBool) {
                buzzOff();
                delayInMs(100);
            } else if (slightRightBool){
                buzzOff();
                delayInMs(100);
            } else if (uturnBool) {
                buzzOff();
                delayInMs(100);
            }
        }
    }
}
