
#include "uart.h"
#include <pic18f47k42.h>

void config_UART(){
     
    
    U1CON0bits.TXEN = 1;
    U1CON0bits.RXEN = 1;
    
    //TX
    TRISCbits.TRISC2 = 0; // Output TX
    ANSELCbits.ANSELC2 = 0; //As digital
    
    //RX
    TRISCbits.TRISC3 = 1; // Input RX
    ANSELCbits.ANSELC3 = 0; // As digital 
    
    
    U1CON1 = 0x90; 
    //Enable Serial port
    //Wake-up Enable bit
    
    
    //X = ((Fosc/Desired baud rate)/16) - 1
    U1BRGL = 51;
    
    //Enable receiver interrupts
    PIE3bits.U1RXIE = 1;
   
}

void transmit_UART(int value){
    
    if (value == 0){
        TX_RESULT = 48;
    }
    else if(value ==1){
        TX_RESULT = 49;
    }
    else if(value ==2){
        TX_RESULT = 50;
    }
    else if(value ==3){
        TX_RESULT = 51;
    }
    else if(value ==4){
        TX_RESULT = 52;
    }
    else if(value ==5){
        TX_RESULT = 53;
    }
    else if(value ==6){
        TX_RESULT = 54;
    }
    else if(value ==7){
        TX_RESULT = 55;
    }
    else if(value ==8){
        TX_RESULT = 56;
    }
    else if(value ==9){
        TX_RESULT = 57;
    }
    else if(value == 45){
        TX_RESULT = 45;
    }
    else if(value == 35){
        TX_RESULT = 35;
    }
}

int receive_UART(){
    return RX_RESULT;
}