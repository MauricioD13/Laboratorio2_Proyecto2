
#include "uart.h"
#include <pic18f47k42.h>

void config_UART(){
     
    //TX
    U1CON0bits.TXEN = 1;
    //TRISCbits.TRISC2 = 0; // Output TX
    ANSELCbits.ANSELC2 = 0; //As digital
    RC6PPS = 0x13;// 0b00010011;
    U1FIFObits.STPMD = 0;
    U1FIFObits.TXBE = 1;
    
    //RX
    U1CON0bits.RXEN = 1;//Rx Enable
    U1CON1bits.WUE = 1;
    TRISCbits.TRISC3 = 1; // Input RX
    ANSELCbits.ANSELC3 = 0; // As digital 
    PIE3bits.U1RXIE = 1; //Interrupt enable
    RC7PPS = 0x17; //0b00010111;
    
    PIE3bits.U1IE = 1;
    
   
    //Enable Serial port
    U1CON1bits.ON = 1;
    
    U1CON2 = 0x00;
    
    //X = ((Fosc/Desired baud rate)/16) - 1
    
    U1BRGL = 207;//19200
    U1BRGH = 0;
    
    //Enable receiver interrupts
    //PIE3bits.U1RXIE = 1;
   
}

int transmit_UART(int value){
    
    if (value == 0){
        TO_TRANSMIT = 48;
    }
    else if(value ==1){
        TO_TRANSMIT = 49;
    }
    else if(value ==2){
        TO_TRANSMIT = 50;
    }
    else if(value ==3){
        TO_TRANSMIT = 51;
    }
    else if(value ==4){
       TO_TRANSMIT = 52;
    }
    else if(value ==5){
       TO_TRANSMIT = 53;
    }
    else if(value ==6){
        TO_TRANSMIT = 54;
    }
    else if(value ==7){
        TO_TRANSMIT = 55;
    }
    else if(value ==8){
        TO_TRANSMIT = 56;
    }
    else if(value ==9){
        TO_TRANSMIT = 57;
    }
    else if(value == 45){
        TO_TRANSMIT = 45;
    }
    else if(value == 35){
        TO_TRANSMIT = 35;
    }
    else{
        
        return 1;
    }
}

int receive_UART(){
    return RECEIVED;
}