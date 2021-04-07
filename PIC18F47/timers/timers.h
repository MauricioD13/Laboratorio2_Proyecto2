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
    double voltage;
    int ADC_number;
    short int integer;
    short int decimal_one;
    short int decimal_two;
    short int channel_convert;
    short int read_ADC_flag;
    short int value_transmitted;
    short int channel_flag;
    short int convert_done;
}STATES;
typedef struct COUNTERS{
    long int base_counter;
    long int counter;
    int transmit_counter;
    long int count_to;
    short int cont_tx;
    short int cont_rx;
    short int cont_spi;
}COUNTERS;

void config_T0(void);

void oscillator_module(void);

#endif	/* TIMERS_H */

