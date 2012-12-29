#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"

#include "rtiostream.h"

void Timer0IntHandler(void) {
    /* This function is bogus and lives in startup_ccs.c */
    /* TODO: don't add startup_ccs.c to sources in PIL mode */
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

void UARTInit(void)
{
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
}

void BoardInit() {
    ROM_FPULazyStackingEnable();
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    ROM_IntMasterEnable();
}

/* Initialize Serial */
int rtIOStreamOpen(int argc, void *argv[])
{
    BoardInit();
    UARTInit();
    return RTIOSTREAM_NO_ERROR;
}

/* Read data from serial */
int rtIOStreamRecv(
        int      streamID,  // A handle to the stream that was returned by a previous call to rtIOStreamOpen.
        void   * dst,       // A pointer to the start of the buffer where received data must be copied.
        size_t   size, 	    // Size of data to copy into the buffer. For byte-addressable architectures,
                            // size is measured in bytes. Some DSP architectures are not byte-addressable.
                            // In these cases, size is measured in number of WORDs, where sizeof(WORD) == 1.
        size_t * sizeRecvd) // The number of units of data received and copied into the buffer dst (zero if no data was copied).
{
    unsigned char *ptr = (unsigned char *)dst; // Initialize ptr is a pointer to the buffer of chars.
    
    *sizeRecvd=0U; // Initialize the number of received chars to zero.
    
    unsigned int sizeRecvd_nb = 0;
    
    while (sizeRecvd_nb < size) // Try to receive char as many times as commanded.
    {
        if (ROM_UARTCharsAvail(UART0_BASE))
        {
            *ptr++ = ROM_UARTCharGetNonBlocking(UART0_BASE);
            //*ptr++ = ROM_UARTCharGet(UART0_BASE);
            // Increase the number of received chars.
            (*sizeRecvd)++;
        }
        // Increase the number of read attempts, so that we don't block in here
        sizeRecvd_nb++;
    }
    return RTIOSTREAM_NO_ERROR;
}

/* Write data to serial */
int rtIOStreamSend(
        int          streamID,
        const void * src,
        size_t       size,
        size_t     * sizeSent)
{
    
    *sizeSent=0U;
    unsigned char *ptr = (unsigned char *)src;
    
    while (*sizeSent < size) {
        ROM_UARTCharPut(UART0_BASE,*ptr++);
        (*sizeSent)++;
    }
    return RTIOSTREAM_NO_ERROR;
}

int rtIOStreamClose(int streamID)
{
    return RTIOSTREAM_NO_ERROR;
}
