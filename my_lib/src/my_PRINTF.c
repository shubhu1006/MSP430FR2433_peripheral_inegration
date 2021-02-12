/*
 * my_PRINTF.c
 *
 *  Created on: 11-Feb-2021
 *      Author: skm
 */

#if 1
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_UART.h"
#include "my_PRINTF.h"

void uart_puts(const char *str )
{
    if(str != NULL)
    {
        while(*str != '\0')
        {
            msp430FR2433_UARTCharPut(*str++);
        }
    }
}

int uart_printf(const char *pcformat, ...)
{
    int iRet = 0;
    int iSize = 256;

    char *pcBuff, *pcTemp;

    va_list list;

    pcBuff = (char *)malloc(iSize);
    if(pcBuff == NULL)
    {
        return -1;
    }

    while(1)
    {
        va_start(list, pcformat);

        iRet = vsnprintf(pcBuff, iSize, pcformat, list);

        va_end(list);

        if(iRet > -1 && iRet < iSize)
        {
            break;
        }
        else
        {
            iSize *= 2;

            if((pcTemp = realloc(pcBuff, iSize)) == NULL)
            {
                uart_puts("could not reallocate memory \n\r");

                iRet = -1;
                break;
            }
            else
            {
                pcBuff = pcTemp;
            }
        }
    }

    uart_puts(pcBuff);

    free(pcBuff);

    return iRet;
}

#endif
