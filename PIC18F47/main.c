/*
 * File:   main.c
 * Author: guasonito
 *
 * Created on 13 de marzo de 2021, 09:03 AM
 */

#include "timers/timers.h"
#include "adc/adc.h"
#include "uart/uart.h"
#include "spi/spi.h"
#include <xc.h>
#include <PIC18F47K42.h>

// CONFIG1L
#pragma config FEXTOSC = OFF    // External Oscillator Selection (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_64MHZ// Reset Oscillator Selection (HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1)

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock out Enable bit (CLKOUT function is disabled)
#pragma config PR1WAY = ON     // PRLOCKED One-Way Set Enable bit (PRLOCK bit can be cleared and set only once)
#pragma config CSWEN = OFF      // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // MCLR Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTS = PWRT_OFF // Power-up timer selection bits (PWRT is disabled)
#pragma config MVECEN = ON      // Multi-vector enable bit (Multi-vector enabled, Vector table used for interrupts)
#pragma config IVT1WAY = ON     // IVTLOCK bit One-way set enable bit (IVTLOCK bit can be cleared and set only once)
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit (ULPBOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_2P45 // Brown-out Reset Voltage Selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config DEBUG = OFF      // Debugger Enable bit (Background debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period selection bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled; SWDTEN is ignored)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4L
#pragma config BBSIZE = BBSIZE_512// Boot Block Size selection bits (Boot Block size is 512 words)
#pragma config BBEN = OFF       // Boot Block enable bit (Boot block disabled)
#pragma config SAFEN = OFF      // Storage Area Flash enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block write protection bit (Application Block not write protected)

// CONFIG4H
#pragma config WRTB = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-30000Bh) not write-protected)
#pragma config WRTC = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config WRTSAF = OFF     // SAF Write protection bit (SAF not Write Protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

// CONFIG5L
#pragma config CP = OFF         // PFM and Data EEPROM Code Protection bit (PFM and Data EEPROM code protection disabled)

// CONFIG5H

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//GLOBAL VARIABLES 
STATES states;
COUNTERS counters;
int channel = 0;
int received = 1;
int rx;
int aux_states;
short int cont = 0;
char MSB_spi_A;
char LSB_spi_A;
char MSB_spi_B;
char LSB_spi_B;
int aux_tx = 0;
int aux_A;
int aux_B;
int j=0;

void convert_number(STATES *states){
    for(int i = 0; i < 2 ; i++){
        
        double voltage  = (double)(0.001220703125)*states->ADC_number[i];
        (states->integer[i]) = (short int) (voltage);
        (states->decimal_one[i])= (short int)((voltage*10)-((states->integer[i])*10));
        (states->decimal_two[i]) = (short int)((voltage*100)-((states->integer[i] *100)+(states->decimal_one[i] *10)));
        
    }
    
}

//Timer interrupt
void __interrupt(irq(IRQ_TMR0),base(0x0008)) T0_isr(){
    //1us
    
    counters.counter == counters.count_to ? START_CONVERSION = 1,PORTDbits.RD1 = 1,counters.counter = 0:counters.counter++;
    PORTDbits.RD1 = 0;
    INTCON0bits.GIEL = 1;
    PIR3bits.TMR0IF = 0;
 
}

//ADC Interrupt
void __interrupt(irq(IRQ_AD),base(0x0008)) ADC_isr(){
    
    
    
    PIR1bits.ADIF = 0;
    states.channel_flag = channel;
  
    if(channel==0){
        states.ADC_number[channel] =  read_ADC();
        ADPCH = 1;
        channel = 1;
        
    }else if(channel == 1)
    {
        states.ADC_number[channel] =  read_ADC();
        states.read_ADC_flag = 1;
        ADPCH = 0;
        channel = 0;
    }
    PIR1bits.ADIF = 0;
}

void __interrupt(irq(IRQ_U1RX),base(0x0008)) U1RX_isr(){
    
    rx = U1RXB;
    counters.cont_rx++;
    PIR3bits.U1RXIF = 0;
}
void __interrupt(irq(IRQ_SPI1TX),base(0x0008)) SPI_isr(){
    
        aux_A = states.ADC_number[0] + 4096;
        LSB_spi_A = (char) aux_A;
        aux_A = aux_A>>8;
        MSB_spi_A = (char) aux_A;

        aux_B = states.ADC_number[1] + 36864; //Change channel 
        LSB_spi_B = (char) aux_B;
        aux_B = aux_B>>8;
        MSB_spi_B = (char) aux_B;
        
        if(cont == 0){
            PORTBbits.RB4 = 0;//LDAC
            PORTBbits.RB4 = 1;

            PORTEbits.RE0 = 1;//CS
            PORTEbits.RE0 = 0;
            SPI1TXB = LSB_spi_A;
            cont++;
        }
        else if(cont == 1){
            SPI1TXB = MSB_spi_A;
            cont++;
        }
        else if(cont == 2){
            
            PORTBbits.RB4 = 0;//LDAC
            PORTBbits.RB4 = 1;

            PORTEbits.RE0 = 1;//CS
            PORTEbits.RE0 = 0;
            SPI1TXB = LSB_spi_B;
            cont++;
        }
        else if(cont == 3){
            SPI1TXB = MSB_spi_B;
            cont = 0;
        }
    
    PIR2bits.SPI1TXIF = 0;
    
}

void init_PIC(void){
    config_T0();
    config_ADC();
    config_UART();
    config_SPI();
}

int main(void) {
    
    INTCON0 = 0xE0; 
    IPR0 = 0x00;
    IPR1 = 0x00;
    IPR2 = 0x00;
    IPR3 = 0x88; //TIMER 0 High priority UART RX High priority 0x88
    IPR4 = 0x00;
    IPR5 = 0x00;
    IPR6 = 0x00;
    IPR7 = 0x00;
    IPR8 = 0x00;
    IPR9 = 0x00;
    IPR10 = 0x00;
    
    
    
    int status_tx = 0;
    oscillator_module();
    counters.count_to = (12*received) - (received-1);
    states.channel_convert = 0;
    states.channel_flag = 1;
    states.convert_done = 0;
    states.value_convert = 0;
   
    init_PIC();
    //Ecuacion para los valores: (x*25) - ((x-1))
    
    //Ports to measure time
    TRISD = 0x00;
    ANSELD = 0x00;
    
    //MAIN LOOP
    while(1){

            
        if(states.read_ADC_flag == 1){
            
            if(states.convert_done == 0){
                
                states.channel_convert = states.channel_flag;
                convert_number(&states);
                states.convert_done = 1;
                states.value_convert = 1;
                
            }
            
            
                if(TX_FLAG == 1 && states.convert_done == 1){
                    
                    counters.cont_tx++;
                    //Serial communication works sending each separate by '-' and when the number ends it send '#'
                    if(counters.cont_tx == 1){
                        status_tx = transmit_UART(states.integer[j]);
                    }

                    else if (counters.cont_tx == 2){
                        status_tx = transmit_UART(states.decimal_one[j]);
                    }
                    else if (counters.cont_tx == 3){
                        status_tx = transmit_UART(states.decimal_two[j]);
                    }
                    else if (counters.cont_tx == 4){
                        if(j==0){
                            TO_TRANSMIT = 44;
                            j++;
                        }else{
                            TO_TRANSMIT = 35;
                            j=0;
                        }
                        
                        states.convert_done = 0;
                        counters.cont_tx = 0;
                    }
                
                TX_FLAG = 0;
                }
                
            
        }
        
        if(counters.cont_rx == 1){
            received = rx;
            }
            else if(counters.cont_rx == 2){
                rx = (rx<<8);
                received = (received) |(rx);
                counters.count_to = (25*received) - (received-1);
                counters.counter = 0;
                counters.cont_rx = 0;
                rx = 0;
        }
        PORTDbits.RD3 = INTCON0bits.GIEL;
    
    }
    
}
