#include "uartlct.h"

void UARTInit(void)
{
#ifndef MATLAB_MEX_FILE
    /* Enable the peripherals used */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    
    /* Set GPIO A0 and A1 as UART pins. */
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Configure the UART for 115,200, 8-N-1 operation. */
    ROM_UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 115200,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
            UART_CONFIG_PAR_NONE));
    
    /* Enable UART */
    ROM_UARTEnable(UART0_BASE);
#endif
}

void UARTWrite (unsigned char nbFlag, unsigned char ucData) {
#ifndef MATLAB_MEX_FILE
    if (nbFlag > 0)
        ROM_UARTCharPutNonBlocking(UART0_BASE,ucData);
    else
        ROM_UARTCharPut(UART0_BASE,ucData);
#endif
}

long UARTRead (unsigned char nbFlag, unsigned char *errorFlag) {
#ifndef MATLAB_MEX_FILE
    /* The output is static to hold previous output value */
    static long out = 0;
    /* Error flag is used for non-blocking reads */
    *errorFlag = 0;
    if (nbFlag > 0) {
        /* Non-blocking read */
        if (ROM_UARTCharsAvail(UART0_BASE)) {
            out = ROM_UARTCharGetNonBlocking(UART0_BASE);
        } else {
            /* If there is nothing in read buffer, set error flag and output previous value */
            *errorFlag = 1;
        }
    } else {
        /* Blocking read */
        out = ROM_UARTCharGet(UART0_BASE);
    }
    return out;
#endif
}
