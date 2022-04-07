/*
 * File:   common_adc.c
 * Author: thomas
 *
 * Created on 05 April 2022, 23:43
 */

#include <xc.h>
#include <pic18f4550.h>

int readChannel(int channel) {
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    ADCON0 = ADCON0 | (channel * 4); // shift channel by 2 bits on the left as ADCON0 set channel on bits 2 to 5
    ADCON0bits.GO = 1;
    ADCON0bits.ADON = 1;
    while (ADCON0bits.GO_nDONE == 1);
    return (ADRESH * 256) | (ADRESL);
}
