/*
 * my_CLK.h
 *
 *  Created on: 11-Feb-2021
 *      Author: skm
 */

#ifndef MY_LIB_INC_MY_CLK_H_
#define MY_LIB_INC_MY_CLK_H_

#define DELAY_MS            16000U       // count for 1 ms of delay at 16Mhz

extern void initClockTo16MHz( void );
void MCU_delayMillisecond(uint32_t n_ms);

#endif /* MY_LIB_INC_MY_CLK_H_ */
