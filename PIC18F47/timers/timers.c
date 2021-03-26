
#include "timers.h"
#include <PIC18F47K42.h>




void config_T0(void){
    /*
     T0CON0
        Enable timer
        8-bit timer
        Postscaler config*/
    T0CON0 = 0x80; //500ns clock period
    
    /*
     T0CON1
        Timer Clock Source
        Asyncronization
        Prescaler config*/
    T0CON1 = 0x70;
    PMD1bits.TMR0MD = 0;
    //Interrupts
    PIE3bits.TMR0IE = 1; 
}


void oscillator_module (void){
    /*
     OSCCON1
        New oscillator source 
        New divider*/
    OSCCON1 = 0x60;
    
    /*
     OSCCON2
        Oscillator source
        divider*/
    OSCCON2 = 0x60;
    
    /*
     OSCCON3
        Clock switch hold
        Secondary oscillator power
        */
    OSCCON3 = 0x80;
    
    
    OSCTUNE = 0x00;
    
    /*
     OSCFRQ
        Frequency selection*/
    OSCFRQ = 0x08;
    
    /*
      OSCEN
        Oscillator manual enable*/
    OSCENbits.HFOEN = 1;
    
}