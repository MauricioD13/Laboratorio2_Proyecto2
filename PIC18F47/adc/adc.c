
#include <pic18f47k42.h>

#include "adc.h"

void config_ADC(void){
    ADCON0 = 0x00;
    ADCON1 = 0x00;
    ADCON2 = 0x00;
    ADSTAT = 0x00;
    //Enable ADC
    ADCON0bits.ADON = 1;
    
    //Port channel
    TRISBbits.TRISB0 = 0;
    ANSELBbits.ANSELB0 = 1;
    //Channel selection
    ADPCHbits.ADPCH3 = 1; //ANB0
    //Voltage reference
    ADREF = 0x00;
    //Clock source
    ADCLK = 0x00; //Fosc/2 (1us)
    //Interrupt control
    PIE1bits.ADIE = 1;
    //Result format
    ADCON0bits.FM = 1; //right justify
    //Conversion trigger
    //Disable autotrigger
}

int read_ADC(void){
    int value;
    value = ADRESL | (ADRESH<<8);
    return value;
}