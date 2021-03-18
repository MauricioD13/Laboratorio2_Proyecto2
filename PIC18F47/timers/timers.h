/* 
 * File:   timers.h
 * Author: guasonito
 *
 * Created on 15 de marzo de 2021, 12:04 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

typedef struct STATES{
    unsigned int ADC_number;
    short int integer;
    short int decimal_one;
    short int decimal_two;
    short int read_ADC_flag;
    short int value_transmitted;
}STATES;

typedef struct COUNTERS{
    
    short int base_counter;
    short int counter;
    int count_to;
    
}COUNTERS;

void config_T1(void);

void change_parameters(COUNTERS *counters, int *parameter); // count_to = (micro_seconds/1000) * 2

void oscilator_module(void);

#endif	/* TIMERS_H */

