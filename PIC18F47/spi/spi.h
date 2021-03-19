/* 
 * File:   spi.h
 * Author: guasonito
 *
 * Created on 16 de marzo de 2021, 11:13 AM
 */

#ifndef SPI_H
#define	SPI_H

#define SPI_FLAG SPI1INTFbits.SRMTIF
#define SPI_TRANSMIT SPI1TXB 
    
void config_SPI(void);
void send_to_DAC(unsigned int *value);

#endif	/* SPI_H */

