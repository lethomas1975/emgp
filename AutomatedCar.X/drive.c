/*
 * File:   drive.c
 * Author: thomas
 *
 * Created on 27 March 2022, 18:41
 */

#include "init.h"
#include "common.h"
#include "common_adc.h"
#include "buzzer.h"
#include "drive.h"
#include "zebra.h"

const float VREF = 5.0f;
const float DETECTION_VOLT = 1.10f;

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

int backwardBool = 0;

int stepCount = 0;
int stepTotal = -1;

int previousDetection = -1;

/*
 * direction is one of the array above,
 * clockwise, 0 for anticlockwise and 1 for clockwise
 * rev is the number of steps
 * led, 0 for no LED, 1 for left LED, 2 for right LED and 3 for both
 * move is the current move (left, right, front back to check 
 */
void rotate(unsigned char direction[], int clockwise, int led);

int detectedPath(int forward, int left, int slightLeft, int right, int slightRight, int uturn);

void initCounters(void);

void rotate(unsigned char direction[], int clockwise, int led) {
    LEDRPin = (led & 0x0002) >> 1;
    LEDPin = led & 0x0001;
    // rotate 8 steps per rev. if rev = 512, then there would be 4096 steps to do a full 360 degree
    for (int j = 0; j < STEPS_PER_REV / 2; j++) {
        // run through 8 steps so it would turn 11.xx degree
        stepCount++;
        zebraDetected();
        for (int i = 0; i < 8; i++) {
            int k = i;
            if (clockwise == 0) {
                k = 8 - i - 1;
            }
            SMOut = direction[k];
            delayInUs(STEP_DELAY);
        }
    }    
    LEDRPin = 0;
    LEDPin = 0;
}

void left(void) {
    rotate(LFT, 1, 1);
}

void right(void) {
    rotate(RGT, 1, 2);
}

void forward(void) {
    rotate(FWD, 1, 0);
}

void backward(void) {
    rotate(FWD, 0, 3);
}

void uturn(void) {
    if (stepCount == 0) {
        switchIncrement();
    }
    rotate(ULFT, 1, 1);
}


#ifdef C2_USE_ADC
int convertVoltageToDigital(int adcDigital) {
    float voltage = ((float)adcDigital) * VREF/1023.0f;
    if (voltage > DETECTION_VOLT) {
        return 1;
    }
    return 0;
}
#endif

void initCounters(void) {
    backwardBool = 0;
    stepCount = 0;
    stepTotal = -1;
    previousDetection = 1;
}

int detectedPath(int forward, int left, int slightLeft, int right, int slightRight, int uturn) {
    if (left) {
        return 2;
    }
    if (slightLeft) {
        return 3;
    }
    if (right) {
        return 4;
    }
    if (slightRight) {
        return 5;
    }
    if (uturn) {
        return 6;
    }
    return 1;
}

void proximityDetection(void) {

    int stop = 0;
    if (hasIncremented() == 1 && isIncrementing() == 0 && counterValue() == 0) {
        stop = 1;
    }
    
    if (stop) {
        buzz();
        LEDPin = ~LEDPin;
        LEDRPin = ~LEDRPin;
        _delay(50);
        buzzOff();
        return;
    }
    
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

    if (backwardBool == 0) {
        if (forwardBool) {
            //buzzOff();
            forward();
        } else {
            //buzz();
            backwardBool = 1;
            previousDetection = detectedPath(forwardBool, leftBool, slightLeftBool, rightBool, slightRightBool, uturnBool);
        }
    }
    
    if (backwardBool == 1 && !forwardBool) {
        if (ps1 == 1 && ps2 == 0 && ps3 == 0) {
            stepCount = 0;        
            stepTotal = STEPS_PER_REV * 4;
            while (stepCount < stepTotal) {
                backward();                            
            }
            stepTotal = -1;
        } else {
            backward();            
        }
        stepCount = 0;        
        if (stepTotal != -1) {
            initCounters();
        }
    } else {
        if (stepTotal == -1 || stepCount < stepTotal) {
            switch (previousDetection) {
                case 2:
                    stepTotal = STEPS_PER_REV * 4;
                    left();
                    break;
                case 3:
                    stepTotal = STEPS_PER_REV;
                    left();
                    break;
                case 4:
                    stepTotal = STEPS_PER_REV * 4;
                    right();
                    break;
                case 5:
                    stepTotal = STEPS_PER_REV;
                    right();
                    break;
                case 6:
                    stepTotal = STEPS_PER_REV * 4;
                    uturn();
                    break;
            }
        } else {
            initCounters();
        }
    }

}
