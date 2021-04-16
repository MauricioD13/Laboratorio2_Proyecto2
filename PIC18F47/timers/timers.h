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
    long filtered_number_FIR;
    int filtered_number_IIR;
    short int integer;
    short int decimal_one;
    short int decimal_two;
    short int read_ADC_flag;
    short int filter_flag;
    short int timer_flag;
}STATES;
typedef struct COUNTERS{
    long int high_counter;
    long int counter;
    int transmit_counter;
    short int count_to;
    short int count_to_high;
    short int cont_tx;
    short int cont_rx;
    short int cont_spi;
}COUNTERS;

void config_T0(void);

void oscillator_module(void);

#endif	/* TIMERS_H */

