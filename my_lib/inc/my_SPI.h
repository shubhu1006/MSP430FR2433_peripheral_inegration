/*
 * my_SPI.h
 *
 *  Created on: 12-Feb-2021
 *      Author: skm
 */

#ifndef MY_LIB_INC_MY_SPI_H_
#define MY_LIB_INC_MY_SPI_H_

extern void initSPI( void );
extern void SendSPIData(uint16_t baseAddress, uint8_t val);
extern uint8_t readSPIData(uint16_t baseAddress);
extern void enableCS( void );
extern void disableCS( void );

#endif /* MY_LIB_INC_MY_SPI_H_ */
