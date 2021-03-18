#include "spi.h"
#include <PIC18F47K42.h>

void config_SPI(void){
    
    //Enable SPI
    SPI1CON0 = 0x82;
    SPI1CON1 = 0x00;
    SPI1CON2 = 0x04;
    
    //Clock selection
    SPI1CLK = 0x01; //HFINTOSC
    //Interrupts
    SPI1INTE = 0x80;
    SPI1INTF = 0x80; 
    
    SPI1TCNTL = 16;
    //Baud Rate
    SPI1BAUD = 138; //BAUD = (SPI clock/(2*Fbaud))-1
}

void send_to_DAC(unsigned int *value){
    //*value = (*value) | (0<<15);
    //*value = (*value) | (0<<14);
    //*value = (*value) | (0<<13);
    *value = (*value) | (1<<12);
    SPI_TRANSMIT = (unsigned char) *value;
}