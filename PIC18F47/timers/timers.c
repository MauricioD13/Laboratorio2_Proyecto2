
#include "timers.h"
#include <PIC18F47K42.h>




void config_T1(void){
    T1CON = 0x01; //500ns clock period
    T1GCON = 0x00;
    T1CLK = 0x02;
    //T2PR = 200;
    TMR1L = 0; 
    
    
    
    
    PIE4bits.TMR1IE = 1;
    IPR4bits.TMR1IP = 0;
    
    
    //T2HLT = 0x00; 
    /* 
        Mode 1 free running - period pulse
        Hardware gate, active-high  
    */   
}

void change_parameters(COUNTERS *counters,int *parameter){
    
    counters->count_to = *parameter;
    
}
void oscilator_module (void){
    OSCCON1 = 0x60;
    OSCCON2 = 0x60;
    OSCFRQ = 0x05;
    OSCENbits.HFOEN = 1;
    
}