/*
 * my_PRINTF.h
 *
 *  Created on: 11-Feb-2021
 *      Author: skm
 */

#ifndef MY_LIB_MY_PRINTF_MY_PRINTF_H_
#define MY_LIB_MY_PRINTF_MY_PRINTF_H_

extern void uart_puts(const char *str );
extern int uart_printf(const char *pcformat, ...);

#endif /* MY_LIB_MY_PRINTF_MY_PRINTF_H_ */
