#include "gpiolct.h"

void GPIOWrite(unsigned long ulPort, unsigned char ucPins, unsigned char ucValue)
{
#ifndef MATLAB_MEX_FILE
    ROM_GPIOPinWrite(ulPort, ucPins, ucValue);
#endif
}

long GPIORead(unsigned long ulPort, unsigned char ucPins)
{
#ifndef MATLAB_MEX_FILE
    long lValue = 0;
    lValue = ROM_GPIOPinRead(ulPort, ucPins);
    return lValue;
#endif
}

void GPIOSetup(unsigned long ulPeripheral, unsigned long ulPort, unsigned char ucPinsOutput)
{
#ifndef MATLAB_MEX_FILE
    ROM_SysCtlPeripheralEnable(ulPeripheral);
    ROM_GPIOPinTypeGPIOOutput(ulPort, ucPinsOutput);
    /* The rest pins are configured as inputs */
    //disable for now, since it breaks Button SW1. The pins are initialized as inputs on reset anyway.
    //ROM_GPIOPinTypeGPIOInput(ulPort, ucPinsOutput ^ 0xFF);
#endif
}
