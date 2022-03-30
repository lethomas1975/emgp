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

#include "../AutomatedCar.X/drive.h"

void left(int step) {
}

void right(int step) {
}

void forward(int step) {
}

void backward(int step) {
}

void uturn() {
}

void proximityDetection() {
    //ps1 front
    int ps1 = 0; //to be replaced with port. this is just to make the code compiled
    //ps2 left
    int ps2 = 0; //to be replaced with port. this is just to make the code compiled
    //ps3 right
    int ps3 = 0; //to be replaced with port. this is just to make the code compiled
    
    int forwardBool = ps1 == 0;
    int leftBool = ps1 == 1 && ps2 == 0;
    int rightBool = ps1 == 1 && ps2 == 1 && ps3 == 0;
    int uturnBool = ps1 == 1 && ps2 == 1 && ps3 == 1;

    if (forwardBool) {
        forward(1);
    } else {
        backward(1);        
        if (leftBool) {
            left(1);
        } else if (rightBool) {
            right(1);
        } else if (uturnBool) {
            uturn();
        }
    }
    
}
