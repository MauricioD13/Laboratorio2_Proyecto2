/* 
 * File:   adc.h
 * Author: guasonito
 *
 * Created on 15 de marzo de 2021, 02:44 PM
 */

#ifndef ADC_H
#define	ADC_H
#define ADC_FLAG PIR1bits.ADIF
#define START_CONVERSION ADCON0bits.ADGO
void config_ADC(void);
int read_ADC(void);
#endif	/* ADC_H */

