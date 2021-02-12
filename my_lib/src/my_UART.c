/*
 * my_UART.c
 *
 *  Created on: 11-Feb-2021
 *      Author: skm
 */

#include <msp430.h>
#include "gpio.h"
#include "my_UART.h"

void initUART( void )
{
    // Configure GPIO
    P1SEL1 &= ~(BIT4 | BIT5);                 // USCI_A0 UART operation
    P1SEL0 |= BIT4 | BIT5;

    // Configure USCI_A0 for UART mode
    UCA0CTLW0 |= UCSWRST;                      // Put eUSCI in reset
#if UART_MODE == SMCLK_115200

    UCA0CTLW0 |= UCSSEL__SMCLK;               // CLK = SMCLK
    // Baud Rate Setting
    // Use Table 21-5
    UCA0BRW = 8;
    UCA0MCTLW |= UCOS16 | UCBRF_10 | 0xF700;   //0xF700 is UCBRSx = 0xF7

#elif UART_MODE == SMCLK_9600

    UCA0CTLW0 |= UCSSEL__SMCLK;               // CLK = SMCLK
    // Baud Rate Setting
    // Use Table 21-5
    UCA0BRW = 104;
    UCA0MCTLW |= UCOS16 | UCBRF_2 | 0xD600;   //0xD600 is UCBRSx = 0xD6
#else
    # error "Please specify baud rate to 115200 or 9600"
#endif

    UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
//    UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

void msp430FR2433_UARTCharPut(unsigned char ucData)
{
    while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = ucData;                   // Load data onto buffer
}


