/*
 * File:   main.c
 * Author: guasonito
 *
 * Created on 13 de marzo de 2021, 09:03 AM
 */

#include "timers/timers.h"
#include "adc/adc.h"
#include "uart/uart.h"
#include <xc.h>
#include <PIC18F47K42.h>



void __interrupt(IRQ_TMR2,base(0x0008)) T2_isr(){
    if(counters.base_counter == 200){
        //100 us
        counters->counter == counters->count_to ? START_CONVERSION = 1: counters->counter++;
        counters.base_counter = 0;
        
    }else{
        counters.base_counter++;
    }
}
void __interrupt(IRQ_AD,base(0x0008)) ADC_isr(){
    states.ADC_number = read_ADC();
    states.read_ADC_flag = 1;
}
void __interrupt(IRQ_U1RX,base(0x0008)) UART_isr(){
    received = receive_UART();
    change_parameters(&counters,*received);
}

void convert_number(float value,STATES *states){
    
    (states->integer) = (int) (value);
    (states->decimal_one)= (int)((value*10)-((states->integer)*10));
    (states->decimal_two) = (int)((value*100)-((states->integer *100)+(states->decimal_one *10)));
    
}

void init_PIC(void){
    config_T2();
    config_ADC();
    config_UART();
}
//GLOBAL VARIABLES 
STATES states;
COUNTERS counters;
int received;
int cont_tx = 0;

void main(void) {
    
    init_PIC();
   
    
    //MAIN LOOP
    while(1){
        if(states.read_ADC_flag == 1){
            //SPI SEND
            if(SPI_FLAG == 1){
                send_to_DAC(&states.ADC_number);
            }
            
            //UART SEND
            if(TX_FLAG == 1){
                convert_number(&states);
                cont_tx++;
                //Serial communication works sending each digit separate by '-' and when the number ends it send '#'
                if(cont_tx == 1){
                    transmit_UART(states.integer);
                }
                else if (cont_tx == 2){
                    transmit_UART(45);
                }
                else if (cont_tx == 3){
                    transmit_UART(states.decimal_one);
                }
                else if (cont_tx == 4){
                    transmit_UART(45);
                }
                else if (cont_tx == 5){
                    transmit_UART(states.decimal_two);
                }
                else if (cont_tx == 6){
                    transmit_UART(35);
                    cont_tx = 0;
                }
            }
            
        }
        
    }
    
}
