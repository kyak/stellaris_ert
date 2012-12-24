#ifndef __UARTLCT_H
#define __UARTLCT_H

#ifndef MATLAB_MEX_FILE
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/uart.h"
#endif

void UARTInit(void);
void UARTWrite (unsigned char nbFlag, unsigned char ucData);
long UARTRead (unsigned char nbFlag, unsigned char *errorFlag);

#endif
