
#include <pic18f47k42.h>

#include "adc.h"

void config_ADC(void){
    //Enable ADC
    ADCON0 = 0x90;
    ADCON1 = 0x00;
    ADCON2 = 0x00;
    ADSTAT = 0x00;
    
    
    
    //Port channel
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    
    //Channel selection
    ADPCH = 0; //ANB0
    
    //Voltage reference
    ADREF = 0x00;
    
    //Clock source
    ADCLK = 0x00; //Fosc/2 (1us)
    
    //Interrupt control
    PIE1bits.ADIE = 1;
    
    //Result format
    ADCON0bits.FM = 1; //right justify

}

int read_ADC(void){
    int value;
    value = ADRESL | (ADRESH<<8);
    return value;
}