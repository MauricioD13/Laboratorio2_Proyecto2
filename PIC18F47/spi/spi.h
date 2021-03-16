/* 
 * File:   spi.h
 * Author: guasonito
 *
 * Created on 16 de marzo de 2021, 11:13 AM
 */

#ifndef SPI_H
#define	SPI_H

#define SPI_FLAG SPI1INTFbits.SRMTIF
#define SPI_TRANSMIT SPI1T1B 

void config_SPI(void);
void send_to_DAC(int *value);
#endif	/* SPI_H */

