/* 
 * File:   uart.h
 * Author: guasonito
 *
 * Created on 15 de marzo de 2021, 02:37 PM
 */

#ifndef UART_H
#define	UART_H
#define TX_FLAG U1FIFObits.TXBE
#define RX_BUFFER_EMPTY U1FIFObits.RXBE
#define TX_RESULT U1RXB
#define RX_RESULT U1TXB

void config_UART();
void transmit_UART(int value);
int receive_UART();

#endif	/* UART_H */

