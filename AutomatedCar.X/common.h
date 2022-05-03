#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include <stdio.h>
#include <stdlib.h>
#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic18f4550.h>
#endif	/* XC_HEADER_TEMPLATE_H */

#ifndef COMMON_H
#define COMMON_H
#define _XTAL_FREQ 8000000              // for __delay_ms() function

void delayInMs(int ms);
void delayInUs(int us);
#endif
