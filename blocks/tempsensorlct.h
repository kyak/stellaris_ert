#ifndef __TEMPSENSORLCT_H
#define __TEMPSENSORLCT_H

#ifndef MATLAB_MEX_FILE
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/rom.h"
#endif

void TempSensorInit(void);
unsigned long TempSensorRead(unsigned char);

#endif
