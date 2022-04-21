/*
 * File:   main.c
 * Author: thomas
 *
 * Created on 27 March 2022, 17:53
 */
#include "init.h"
#include "common.h"
#include "drive.h"
#include "zebra.h"
#include "buzzer.h"

void main(void) {
    init();
    
    while (1) {
        proximityDetection();
    }
}
