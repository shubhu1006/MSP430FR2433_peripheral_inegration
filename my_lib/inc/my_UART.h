/*
 * my_UART.h
 *
 *  Created on: 11-Feb-2021
 *      Author: skm
 */

#ifndef MY_LIB_MY_UART_MY_UART_H_
#define MY_LIB_MY_UART_MY_UART_H_

#define SMCLK_115200    0
#define SMCLK_9600      1

#define UART_MODE       SMCLK_115200//SMCLK_9600//

extern void initUART( void );
extern void msp430FR2433_UARTCharPut(unsigned char ucData);

#endif /* MY_LIB_MY_UART_MY_UART_H_ */
