/*
 * my_SPI.c
 *
 *  Created on: 12-Feb-2021
 *      Author: skm
 */

#include <msp430.h>
#include "eusci_a_spi.h"
#include "gpio.h"
#include "cs.h"
#include "my_SPI.h"

void enableCS( void )
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN7);
}

void disableCS( void )
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN7);
}

void SendSPIData(uint16_t baseAddress, uint8_t val)
{
    //USCI_A0 TX buffer ready?
//    while (!EUSCI_A_SPI_getInterruptStatus(baseAddress,
//              EUSCI_A_SPI_TRANSMIT_INTERRUPT)) ;

    EUSCI_A_SPI_transmitData(baseAddress, val);

    while(EUSCI_A_SPI_isBusy(baseAddress));
}

uint8_t readSPIData(uint16_t baseAddress)
{
//    SendSPIData(baseAddress, 0x00);

    while(EUSCI_A_SPI_isBusy(baseAddress));

    return EUSCI_A_SPI_receiveData(EUSCI_A0_BASE);
}

void initSPI( void )
{
    EUSCI_A_SPI_initMasterParam mSpi_param = {0};

    // Configure SPI Pins for UCA0CLK, UCA0SIMO and UCA0SOMI
    /*
    * Select Port 1
    * Set Pin 4, Pin 5 and Pin 6 to input Secondary Module Function
    */
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P1,
        GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    /* Set Port 1- PIN7 as CS */
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN7);

    mSpi_param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
    mSpi_param.clockSourceFrequency = CS_getSMCLK();                         //SMCLK = 16MHz
    mSpi_param.desiredSpiClock = 2000000;
    mSpi_param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
    mSpi_param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
    mSpi_param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
    mSpi_param.spiMode = EUSCI_A_SPI_3PIN;

    EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, &mSpi_param);
    EUSCI_A_SPI_enable(EUSCI_A0_BASE);
}


