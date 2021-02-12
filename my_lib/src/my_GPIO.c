/*
 * my_GPIO.c
 *
 *  Created on: 11-Feb-2021
 *      Author: skm
 */

#include <msp430.h>
#include "gpio.h"
#include "my_GPIO.h"

void initGPIO( void )
{
    LED_DIR |= LED_PIN;
    LED_OUT &= ~LED_PIN;

    /* Set Port 1- Pin 2 Reset */
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN2);

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
}


