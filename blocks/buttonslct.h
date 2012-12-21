#ifndef __BUTTONSLCT_H
#define __BUTTONSLCT_H

#ifndef MATLAB_MEX_FILE
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#endif

void ButtonsInit(void);
unsigned char ButtonsRead(unsigned char *pucRawState);

#endif
