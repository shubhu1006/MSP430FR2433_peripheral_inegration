/*
 * my_GPIO.c
 *
 *  Created on: 11-Feb-2021
 *      Author: skm
 */

#include <msp430.h>
#include "my_GPIO.h"

void initGPIO( void )
{
    LED_DIR |= LED_PIN;
    LED_OUT &= ~LED_PIN;

    // Configure GPIO
    P1SEL1 &= ~(BIT4 | BIT5);                 // USCI_A0 UART operation
    P1SEL0 |= BIT4 | BIT5;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
}


