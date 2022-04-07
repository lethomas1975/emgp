/*
 * File:   drive.c
 * Author: thomas
 *
 * Created on 27 March 2022, 18:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>

#include "init.h"
#include "common.h"
#include "common_adc.h"
#include "buzzer.h"
#include "drive.h"
#include "zebra.h"

int direction = 0;
int STEP_DELAY = 1;
int STEPS_PER_REV = (int) (360.0 / ((5.625/64.0) * 8.0)) / 4; // datasheet angle per step 5.625/64
// we will not do a full revolution so can detect obstacles faster.

unsigned char FWD[9] = { 0b10000001, 0b11000011, 0b01000010, 0b01100110, 0b00100100, 0b00111100, 0b00011000, 0b10011001, '\0' };
unsigned char LFT[9] = { 0b10000000, 0b11000000, 0b01000000, 0b01100000, 0b00100000, 0b00110000, 0b00010000, 0b10010000, '\0'};
unsigned char RGT[9] = { 0b00000001, 0b00000011, 0b00000010, 0b00000110, 0b00000100, 0b00001100, 0b00001000, 0b00001001, '\0'};
unsigned char BWD[9] = { 0b00011000, 0b00111100, 0b00100100, 0b01100110, 0b01000010, 0b11000011, 0b10000001, 0b10011001, '\0'};
unsigned char ULFT[9] = { 0b10001000, 0b11001100, 0b01000100, 0b01100110, 0b00100010, 0b00110011, 0b00010001, 0b10011001, '\0'};
unsigned char URGT[9] = { 0b00010001, 0b00110011, 0b00100010, 0b01100110, 0b01000100, 0b11001100, 0b10001000, 0b10011001, '\0'};

int convertVoltageToDigital(int adcDigital);

/*
 * direction is one of the array above,
 * clockwise, 0 for anticlockwise and 1 for clockwise
 * led, 0 for no LED, 1 for left LED, 2 for right LED and 3 for both
 */
int rotate(unsigned char direction[], int clockwise, int rev, int led);

int convertVoltageToDigital(int adcDigital) {
    float voltage = ((float)adcDigital)*5.0/1023.0;
    if (voltage >= 2.5) {
        return 1;
    }
    return 0;
}

int rotate(unsigned char direction[], int clockwise, int rev, int led) {
    LEDRPin = (led & 0x0002) >> 1;
    LEDPin = led & 0x0001;
    for (int j = 0; j < rev; j++) {
        for (int i = 0; i < 8; i++) {
            int k = i;
            if (clockwise == 0) {
                k = 8 - i;
            }
            SMOut = direction[k];
            delayInUs(STEP_DELAY);
        }
        zebraDetected();
    }    
    LEDRPin = 0;
    LEDPin = 0;
}

void left() {
    rotate(LFT, 1, (STEPS_PER_REV + 1) * 4, 1);
}

void leftBackward() {
    rotate(LFT, 0, (STEPS_PER_REV + 1) * 4, 1);
}

void right() {
    rotate(RGT, 1, (STEPS_PER_REV + 1) * 4, 2);
}

void rightBackward() {
    rotate(RGT, 0, (STEPS_PER_REV + 1) * 4, 2);
}

void forward() {
    rotate(FWD, 1, STEPS_PER_REV / 2, 0);
}

void backward() {
    rotate(BWD, 1, STEPS_PER_REV * 4, 3);
}

void uturn() {
    rotate(ULFT, 1, (STEPS_PER_REV + 1) * 4, 1);
    uturnBool = ++uturnBool % 2;
}

void proximityDetection() {
    
#ifdef C2_USE_ADC
    int ps1 = convertVoltageToDigital(readChannel(0));
    int ps2 = convertVoltageToDigital(readChannel(1));
    int ps3 = convertVoltageToDigital(readChannel(2));
    int forwardBool = ps1 == 0;
    int leftBool = ps1 == 1 && ps2 == 0;
    int rightBool = ps1 == 1 && ps2 == 1 && ps3 == 0;
    int uturnBool = ps1 == 1 && ps2 == 1 && ps3 == 1;
#else
    int forwardBool = PS1In == 0;
    int leftBool = PS1In == 1 && PS2In == 0;
    int rightBool = PS1In == 1 && PS2In == 1 && PS3In == 0;
    int uturnBool = PS1In == 1 && PS2In == 1 && PS3In == 1;
#endif
    if (forwardBool) {
        forward();
    } else {
        buzz();
        buzzOff();

        backward();        
        if (leftBool) {
            left();
        } else if (rightBool) {
            right();
        } else if (uturnBool) {
            uturn();
        }
    }
}
