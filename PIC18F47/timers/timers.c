
#include "timers.h"
#include <PIC18F47K42.h>


typedef struct STATES{
    int ADC_number;
    short int integer;
    short int decimal_one;
    short int decimal_two;
    short int read_ADC_flag;
}STATES;

typedef struct COUNTERS{
    
    short int base_counter;
    short int counter;
    int count_to;
    
}COUNTERS;

void config_T2(void){
    T2CLK = 0x02;
    T2PR = 200;
    T2CON = 0xB0; //500ns clock period
    
    
    T2HLT = 0x01; 
    /* 
        Mode 1 free running - period pulse
        Hardware gate, active-high  
    */   
}

void change_parameters(COUNTERS *counters,int *parameter){
    
    counters->count_to = *parameter;
    
}
