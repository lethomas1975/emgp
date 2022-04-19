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

// 4 higher bits for Right wheel
// 4 lower bits for Left wheel
// 0xRRRRLLLL
unsigned char FWD[] = { 0b10000001, 0b11000011, 0b01000010, 0b01100110, 0b00100100, 0b00111100, 0b00011000, 0b10011001 };
unsigned char LFT[] = { 0b10000000, 0b11000000, 0b01000000, 0b01100000, 0b00100000, 0b00110000, 0b00010000, 0b10010000 };
unsigned char RGT[] = { 0b00000001, 0b00000011, 0b00000010, 0b00000110, 0b00000100, 0b00001100, 0b00001000, 0b00001001 };
unsigned char ULFT[] = { 0b10001000, 0b11001100, 0b01000100, 0b01100110, 0b00100010, 0b00110011, 0b00010001, 0b10011001 };
unsigned char URGT[] = { 0b00010001, 0b00110011, 0b00100010, 0b01100110, 0b01000100, 0b11001100, 0b10001000, 0b10011001 };


/*
 * direction is one of the array above,
 * clockwise, 0 for anticlockwise and 1 for clockwise
 * rev is the number of steps
 * led, 0 for no LED, 1 for left LED, 2 for right LED and 3 for both
 * move is the current move (left, right, front back to check 
 */
int rotate(unsigned char direction[], int clockwise, int rev, int led, int move);

int canContinue(int direction);

int convertVoltageToDigital(int adcDigital) {
    float voltage = ((float)adcDigital)*5.0/1023.0;
    if (voltage >= 2.5) {
        return 1;
    }
    return 0;
}

int rotate(unsigned char direction[], int clockwise, int rev, int led, int move) {
    LEDRPin = (led & 0x0002) >> 1;
    LEDPin = led & 0x0001;
    for (int j = 0; j < rev; j++) {
        if ((j % 6) == 0 && !canContinue(move)) {
            break;
        }
        // run through 8 steps so it would turn 11.xx degree
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
    rotate(LFT, 1, (STEPS_PER_REV + 1) * 4, 1, 1);
}

void slightLeft() {
    rotate(LFT, 1, STEPS_PER_REV, 1, 2);
}

void right() {
    rotate(RGT, 1, (STEPS_PER_REV + 1) * 4, 2, 3);
}

void slightRight() {
    rotate(RGT, 1, STEPS_PER_REV, 2, 4);
}

void forward() {
    rotate(FWD, 1, STEPS_PER_REV / 2, 0, -1);
}

void backward() {
    rotate(FWD, 0, STEPS_PER_REV * 4, 3, -1);
}

void slightBackward() {
    rotate(FWD, 0, STEPS_PER_REV * 2, 3, -1);
}

void uturn() {
    uturnBool = ++uturnBool % 2;
    rotate(ULFT, 1, (STEPS_PER_REV + 1) * 4, 1, 5);
}


int canContinue(int direction) {
    if (direction == -1) {
        return 1;
    }
    int ps1 = convertVoltageToDigital(readChannel(0));
    int ps2 = convertVoltageToDigital(readChannel(1));
    int ps3 = convertVoltageToDigital(readChannel(2));
    switch (direction) {
        case 0: // forward
            return ps1 == 0;
        case 5: //uturn
        case 1: // left
        case 2: // slight left
            return ps2 == 0;
        case 3: // right
        case 4: // slight right
            return ps3 == 0;
    }
    return 1;
}

void proximityDetection() {
    
#ifdef C2_USE_ADC
    int ps1 = convertVoltageToDigital(readChannel(0));
    int ps2 = convertVoltageToDigital(readChannel(1));
    int ps3 = convertVoltageToDigital(readChannel(2));
#else
    int ps1 = PS1In;
    int ps2 = PS2In;
    int ps3 = PS3In;
#endif

    // PS1 | PS2 | PS3 | Direction
    // 0   | 0   | 0   | Forward
    // 1   | 0   | 0   } left (90 degree left turn)
    // 1   | 0   | 1   | left (90 degree left turn)
    // 0   | 0   | 1   | slight left ( 45 degree left turn)
    // 1   | 1   | 0   | right (90 degree right turn)
    // 0   | 1   | 0   | slight right (45 degree right turn)
    // 1   | 1   | 1   | u-turn
    // 0   | 1   | 1   | u-turn
    int forwardBool = ps1 == 0 && ps2 == 0 && ps3 == 0;
    int leftBool = (ps1 == 1 && ps2 == 0 && ps3 == 0) || (ps1 == 1 && ps2 == 0 && ps3 == 1);
    int slightLeftBool = ps1 == 0 && ps2 == 0 && ps3 == 1;
    int rightBool = ps1 == 1 && ps2 == 1 && ps3 == 0;
    int slightRightBool = ps1 == 0 && ps2 == 1 && ps3 == 0;
    int uturnBool = (ps1 == 1 && ps2 == 1 && ps3 == 1) || (ps1 == 0 && ps2 == 1 && ps3 == 1);

    if (forwardBool) {
        forward();
    } else {
        buzz();
        buzzOff();
        
        if (!slightLeftBool && !slightRightBool) {
            backward();            
        } else {
            slightBackward();
        }
        if (leftBool) {
            left();
        } else if (slightLeftBool) {
            slightLeft();
        } else if (rightBool) {
            right();
        } else if (slightRightBool){
            slightRight();
        } else if (uturnBool) {
            uturn();
        }
    }
}
