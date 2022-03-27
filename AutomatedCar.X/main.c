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

#include "../AutomatedCar.X/init.h"
#include "../AutomatedCar.X/drive.h"
#include "../AutomatedCar.X/zebra.h"
#include "../AutomatedCar.X/buzzer.h"

void main(void) {
    init();
    
    while (1) {
        // drive
    }
}
