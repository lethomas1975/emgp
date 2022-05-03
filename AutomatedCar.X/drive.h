#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include <stdio.h>
#include <stdlib.h>
#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic18f4550.h>
#endif	/* XC_HEADER_TEMPLATE_H */

#ifndef DRIVE_H
#define DRIVE_H

// functions for the Stepper Motors
void left(void);
void slightLeft(void);
void right(void);
void slightRight(void);
void forward(void);
void backward(void);
void slightBackward(void);
void uturn(void);

void stop(void);

// functions for the Proximity sensors
void proximityDetection(void);

#ifdef C2_USE_ADC
    int convertVoltageToDigital(int adcDigital);
#endif

#endif

