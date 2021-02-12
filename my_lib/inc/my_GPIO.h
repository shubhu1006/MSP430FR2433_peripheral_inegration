/*
 * my_GPIO.h
 *
 *  Created on: 11-Feb-2021
 *      Author: skm
 */

#ifndef MY_LIB_MY_GPIO_MY_GPIO_H_
#define MY_LIB_MY_GPIO_MY_GPIO_H_

#define LED_OUT     P1OUT
#define LED_DIR     P1DIR
#define LED_PIN     BIT0

extern void initGPIO( void );


#endif /* MY_LIB_MY_GPIO_MY_GPIO_H_ */
