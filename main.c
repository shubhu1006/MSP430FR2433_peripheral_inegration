//******************************************************************************
//   MSP430FR243x Demo - eUSCI_A0, UART Echo received character
//                     (ACLK 9600/SMCLK 9600/SMCLK 115200)
//
//   Description: The device will wait in LPM0/LPM3 (based on clock source)
//   until a UART character is received.
//   Then the device will echo the received character.
//   The UART can operate using ACLK at 9600, SMCLK at 115200 or SMCLK at 9600.
//   To configure the UART mode, change the following line:
//
//      #define UART_MODE       SMCLK_115200
//      to any of:
//      #define UART_MODE       SMCLK_115200
//      #define UART_MODE       SMCLK_9600
//      #define UART_MODE       ACLK_9600
//
//   UART RX ISR is used to handle communication.
//   ACLK = 32.768kHz, MCLK = SMCLK = DCO 16MHz.
//
//
//
//                   MSP430FR2633
//                 -----------------
//            /|\ |             P1.5|<-- Receive Data (UCA0RXD)
//             |  |                 |
//             ---|RST          P1.4|--> Transmit Data (UCA0TXD)
//                |                 |
//                |                 |
//                |                 |
//   Error LED  <-|P1.0             |
//                |                 |
//                |                 |
//
//   Nima Eskandari and Ryan Meredith
//   Texas Instruments Inc.
//   November 2017
//   Built with CCS V7.3
//******************************************************************************

#include <msp430.h>
#include <stdio.h>
#include <file.h>
#include <wdt_a.h>
#include "my_GPIO.h"
#include "my_PRINTF.h"
#include "my_UART.h"
#include "my_CLK.h"

//******************************************************************************
// Main ************************************************************************
// Enters LPM0 if SMCLK is used and waits for UART interrupts. If ACLK is used *
// then the device will enter LPM3 mode instead. The UART RX interrupt handles *
// the received character and echoes it.                                       *
//******************************************************************************

int main(void)
{

  WDT_A_hold(WDT_A_BASE);                       // Stop Watchdog

  initGPIO();
  initClockTo16MHz();
  initUART();

  uart_printf("hello new uart %d\r\n", 10);

  __bis_SR_register(LPM0_bits + GIE);         // Since SMCLK is source, enter LPM0, interrupts enabled
  __no_operation();                           // For debugger

  return 0;
}

//******************************************************************************
// UART Interrupt ***********************************************************
//******************************************************************************

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
      while(!(UCA0IFG&UCTXIFG));
      UCA0TXBUF = UCA0RXBUF;
      __no_operation();
      break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
  }
}

