#include "adclct.h"

/* Base: 0 for ADC0, 1 for ADC1
 * Factor: 0,2,4,8,16,32,64 - Hardware oversampling factor
 * SSX_ENA: 4-element array, index is sample sequencer number. 0 - SS disabled, 1 - SS enabled.
 * Config0: 8-element array, index is step number of SS0. Contains ready to use configuration for according step of SS0.
 * Config1/Config2: 4-element arrays, index is step number of SS1/SS2. Contain ready to use configuration for SS1/SS2.
 * Config3: Scalar, contains ready to use configuration for SS3.
 * Trigger: 4-element array, index is sample sequencer number. Contains ready to use SS trigger source.
 * Priority: 4-element array, index is sample sequencer number. Contains ready to use SS priority.
 * Speed: 1/2/3/4 for SYSCTL_ADCSPEED_125KSPS/SYSCTL_ADCSPEED_250KSPS/SYSCTL_ADCSPEED_500KSPS/SYSCTL_ADCSPEED_1MSPS
 */
void ADCInit(unsigned char Base, unsigned char Factor, unsigned char * SSX_ENA,
             unsigned int * Config0, unsigned int * Config1,
             unsigned int * Config2, unsigned int Config3,
             unsigned int * Trigger, unsigned int * Priority,
             unsigned int Speed)
{
#ifndef MATLAB_MEX_FILE
    unsigned long adc_base = 0;
    int SS = 0;
    int Step = 0;
  
    //configure ADC Base address
    switch (Base) {
        case 0:
            ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
            adc_base = ADC0_BASE;            
            break;
        case 1:
            ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
            adc_base = ADC1_BASE;
            break;
        default:
            ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
            adc_base = ADC0_BASE;
    }
    
    //configure ADC speed
    switch (Speed) {
        case 1:
            ROM_SysCtlADCSpeedSet(SYSCTL_ADCSPEED_125KSPS);
            break;
        case 2:
            ROM_SysCtlADCSpeedSet(SYSCTL_ADCSPEED_250KSPS);
            break;
        case 3:
            ROM_SysCtlADCSpeedSet(SYSCTL_ADCSPEED_500KSPS);
            break;
        case 4:
            ROM_SysCtlADCSpeedSet(SYSCTL_ADCSPEED_1MSPS);
            break;
        default:
            ROM_SysCtlADCSpeedSet(SYSCTL_ADCSPEED_250KSPS);
    }
 
    //Configure hardware oversample
    ROM_ADCHardwareOversampleConfigure(adc_base, Factor);
    //Disable sequencers we are about to configure.
    //Seems weird, but disable sequencers that were
    //chosen to be active: SSX_ENA(SSX_ENA==1)
    for (SS=0; SS<4; SS++) {
        if (SSX_ENA[SS] > 0) {
            //Is it Ok to disable and configure SS by SS? Maybe must disable all before configure?
            ROM_ADCSequenceDisable(adc_base, SS);
            //Configure sequence
            ROM_ADCSequenceConfigure(adc_base, SS, Trigger[SS], Priority[SS]);
        }
    }
    
    //If SS0 is enabled
    if (SSX_ENA[0] > 0) {
        //For steps from 0 to 7
        for (Step=0; Step<8; Step++) {
            //If the step is configured
            if (Config0[Step] > 0) {
                //Apply the configuration
                ROM_ADCSequenceStepConfigure(adc_base, 0, Step, Config0[Step]);
            }
        }
    }
    
    //If SS1 is enabled
    if (SSX_ENA[1] > 0) {
        //For steps from 0 to 3
        for (Step=0; Step<4; Step++) {
            //If the step is configured
            if (Config1[Step] > 0) {
                //Apply the configuration
                ROM_ADCSequenceStepConfigure(adc_base, 1, Step, Config1[Step]);
            }
        }
    }
    
    //If SS2 is enabled
    if (SSX_ENA[2] > 0) {
        //For steps from 0 to 3
        for (Step=0; Step<4; Step++) {
            //If the step is configured
            if (Config2[Step] > 0) {
                //Apply the configuration
                ROM_ADCSequenceStepConfigure(adc_base, 2, Step, Config2[Step]);
            }
        }
    }
    
    //If SS3 is enabled
    if (SSX_ENA[3] > 0) {
        //If the step is configured
        if (Config3 > 0) {
            //Apply the configuration
            ROM_ADCSequenceStepConfigure(adc_base, 3, 0, Config3);
        }
    }

    //Now to enable the sequencers
    for (SS=0; SS<4; SS++) {
        if (SSX_ENA[SS] > 0) {
            ROM_ADCSequenceEnable(adc_base, SS);
        }
    }
#endif
}

void ADCStep(unsigned char Base, unsigned char * SSX_ENA,
             unsigned int * ulSS0Value, unsigned int * ulSS1Value,
             unsigned int * ulSS2Value, unsigned int * ulSS3Value)
{
#ifndef MATLAB_MEX_FILE  
    unsigned long adc_base = 0;
    int SS = 0;
  
    //configure ADC Base address
    switch (Base) {
        case 0:
            adc_base = ADC0_BASE;            
            break;
        case 1:
            adc_base = ADC1_BASE;
            break;
        default:
            adc_base = ADC0_BASE;
    }
    
    //we need to clear interrupts just in case
    for (SS=0; SS<4; SS++) {
        if (SSX_ENA[SS] > 0) {
            ROM_ADCIntClear(adc_base, SS);
        }
    }

    //we don't use interrupts at the moment...
    for (SS=0; SS<4; SS++) {
        if (SSX_ENA[SS] > 0) {
            ROM_ADCProcessorTrigger(adc_base, SS);
        }
    }

    //this is bad.. a series of while loops to wait for data...
    if (SSX_ENA[0] > 0) {
        while(!ROM_ADCIntStatus(adc_base, 0, false))
            {
            }
        ROM_ADCSequenceDataGet(adc_base, 0, ulSS0Value);
    }
    
    if (SSX_ENA[1] > 0) {
        while(!ROM_ADCIntStatus(adc_base, 1, false))
            {
            }
        ROM_ADCSequenceDataGet(adc_base, 1, ulSS1Value);
    }

    if (SSX_ENA[2] > 0) {
        while(!ROM_ADCIntStatus(adc_base, 2, false))
            {
            }
        ROM_ADCSequenceDataGet(adc_base, 2, ulSS2Value);
    }

    if (SSX_ENA[3] > 0) {
        while(!ROM_ADCIntStatus(adc_base, 3, false))
            {
            }
        ROM_ADCSequenceDataGet(adc_base, 3, ulSS3Value);
    }

#endif
}
