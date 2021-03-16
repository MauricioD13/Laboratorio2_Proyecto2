#include "spi.h"
#include <PIC18F47K42.h>

void config_SPI(void){
    
    //Enable SPI
    SPI1CON0 = 0x82;
    SPI1CON1 = 0x00;
    SPI1CON2 = 0x04;
    
    //Clock selection
    SPI1CLK = 0x00; //Fosc
    //Interrupts
    SPI1INTE = 0x80;
    
    //Baud Rate
    SPI1BAUD = 416; //BAUD = (SPI clock/(2*Fbaud))-1
}

void send_to_DAC(int *value){
    SPI_TRANSMIT = *value;
}