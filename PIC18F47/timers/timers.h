/* 
 * File:   timers.h
 * Author: guasonito
 *
 * Created on 15 de marzo de 2021, 12:04 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H
#define HINTOSC_STATUS OSCSTATbits.HFOR
typedef struct STATES{
    int ADC_number;
    short int integer;
    short int decimal_one;
    short int decimal_two;
    short int read_ADC_flag;
    short int value_transmitted;
}STATES;
typedef struct COUNTERS{
    long int base_counter;
    long int counter;
    int transmit_counter;
    long int count_to;
    
}COUNTERS;

void config_T0(void);

void change_parameters(*count_to, int *parameter); // count_to = (micro_seconds/1000) * 2

void oscillator_module(void);

#endif	/* TIMERS_H */

