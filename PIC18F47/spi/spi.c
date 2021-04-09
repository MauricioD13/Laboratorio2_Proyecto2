#include "spi.h"
#include <PIC18F47K42.h>

void config_SPI(void){
    
   //Enable SPI
    SPI1CON0 = 0x82;
    SPI1CON1 = 0x20;
    SPI1CON2 = 0x02;

    //Clock selection
    SPI1CLK = 0x01; //HFINTOSC
    
    //Transmit size   
    SPI1TCNT = 16; //Transfer counter LSB   16 bits SPI1TWIDTH+(SPI1TCNT*8)
    SPI1TWIDTH = 8;
    
    // Output signals
    RC5PPS = 0x1F; //SDO1
    
    RC3PPS = 0x1E;//SCK1
    //SPI1SCKPPS = 0x1E;
    TRISCbits.TRISC3 = 0;
    ANSELCbits.ANSELC3 = 0;
    TRISCbits.TRISC5 = 0;
    ANSELCbits.ANSELC5 = 0;
    
    PMD5bits.SPI1MD = 0; // Enable module
    
    //CS configuration
    TRISEbits.TRISE0 = 0;// As output
    ANSELEbits.ANSELE0 = 0; //As digital
    PORTEbits.RE0 = 1;
    
    //LDAC Configuration
    TRISBbits.TRISB4 = 0;// As output
    ANSELBbits.ANSELB4 = 0; //As digital
    PORTBbits.RB4 = 1;
    
    //Baud Rate
    SPI1BAUD = 138; //BAUD = (SPI clock/(2*Fbaud))-1  57600 bauds
    
    //Interrupts
    SPI1INTEbits.SRMTIE = 1;
    PIE2bits.SPI1TXIE = 1;
}

void send_to_DAC(unsigned int *value){
    //*value = (*value) | (0<<15);
    //*value = (*value) | (0<<14);
    //*value = (*value) | (0<<13);
    *value = (*value) | (1<<12);
    SPI_TRANSMIT = (unsigned char)*value;
}