#include "tempsensorlct.h"

void TempSensorInit(void)
{
#ifndef MATLAB_MEX_FILE
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ROM_SysCtlADCSpeedSet(SYSCTL_ADCSPEED_250KSPS);
    ROM_ADCHardwareOversampleConfigure(ADC0_BASE, 64);
    ROM_ADCSequenceDisable(ADC0_BASE, 1);

    ROM_ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);
    ROM_ADCSequenceEnable(ADC0_BASE, 1);
#endif
}

/* unit: 1/2 (Celsius/Fahrenheit) */
unsigned long TempSensorRead(unsigned char unit)
{
#ifndef MATLAB_MEX_FILE
    unsigned long ulTempValue = 0;
    unsigned long ulADC0Value[4];
    unsigned long ulTempAvg;

    ROM_ADCIntClear(ADC0_BASE, 1);
    ROM_ADCProcessorTrigger(ADC0_BASE, 1);

    while(!ROM_ADCIntStatus(ADC0_BASE, 1, false))
    {
    }

    ROM_ADCSequenceDataGet(ADC0_BASE, 1, ulADC0Value);
    ulTempAvg = (ulADC0Value[0] + ulADC0Value[1] + ulADC0Value[2] + ulADC0Value[3] + 2)/4;
    ulTempValue = (1475 - ((2475 * ulTempAvg)) / 4096)/10;

    if (unit == 2)
    {
        /* Fahrenheit */
        ulTempValue = ((ulTempValue * 9) + 160) / 5;
    }
    return ulTempValue;
#endif
}
