#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include <stdio.h>
#include <stdlib.h>
#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic18f4550.h>
#endif	/* XC_HEADER_TEMPLATE_H */

#ifndef ZEBRA_H
#define	ZEBRA_H

// functions for 7-Segment
void resetCounter(void);            // reset the 7-Segment counter
void increment(void);               // increment the 7-Segment counter
void incrementAndDisplay(void);     // increment the 7-Segment counter and display the value on the LED
void decrement(void);               // decrement the 7-Segment counter
void decrementAndDisplay(void);     // decrement the 7-Segment counter and display the value on the LED
void setSevenSegment(int count);    // display the 7-Segment on the LED
int counterValue(void);

void switchIncrement(void);
int isIncrementing(void);
int hasIncremented(void);

// functions for Optical Sensor
void zebraDetected(void);
#endif