#ifndef __ADCLCT_H
#define __ADCLCT_H

#ifndef MATLAB_MEX_FILE
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/rom.h"
#endif

void ADCInit(unsigned char Base, unsigned char Factor, unsigned char * SSX_ENA,
             unsigned int * Config0, unsigned int * Config1,
             unsigned int * Config2, unsigned int Config3,
             unsigned int * Trigger, unsigned int * Priority,
             unsigned int Speed);
void ADCStep(unsigned char Base, unsigned char * SSX_ENA,
             unsigned int * ulSS0Value, unsigned int * ulSS1Value,
             unsigned int * ulSS2Value, unsigned int * ulSS3Value);

#endif
