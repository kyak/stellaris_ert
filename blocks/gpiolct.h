#ifndef __GPIOLCT_H
#define __GPIOLCT_H

#ifndef MATLAB_MEX_FILE
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#endif

void GPIOWrite(unsigned long ulPort, unsigned char ucPins, unsigned char ucValue);
long GPIORead(unsigned long ulPort, unsigned char ucPins);
void GPIOSetup(unsigned long ulPeripheral, unsigned long ulPort, unsigned char ucPinsOutput);

#endif
