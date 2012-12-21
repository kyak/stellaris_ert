#include "buttonslct.h"

#ifndef MATLAB_MEX_FILE
#define LEFT_BUTTON     GPIO_PIN_4
#define RIGHT_BUTTON    GPIO_PIN_0
#define ALL_BUTTONS     (LEFT_BUTTON | RIGHT_BUTTON)

/* Holds the current, debounced state of each button */
static unsigned char g_ucButtonStates = ALL_BUTTONS;
#endif

void ButtonsInit(void)
{
#ifndef MATLAB_MEX_FILE
    /* Enable the GPIO port to which the pushbuttons are connected */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    /* Unlock PF0 so we can change it to a GPIO input
       Once we have enabled (unlocked) the commit register then re-lock it
       to prevent further changes.  PF0 is muxed with NMI thus a special case */
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY_DD;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    /* Set each of the button GPIO pins as an input with a pull-up */
    ROM_GPIODirModeSet(GPIO_PORTF_BASE, ALL_BUTTONS, GPIO_DIR_MODE_IN);
    ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, ALL_BUTTONS,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    /* Initialize the debounced button state */
    g_ucButtonStates = ROM_GPIOPinRead(GPIO_PORTF_BASE, ALL_BUTTONS);
#endif
}

unsigned char ButtonsRead(unsigned char *pucRawState)
{
#ifndef MATLAB_MEX_FILE
    unsigned long ulDelta;
    unsigned long ulData;
    static unsigned char ucSwitchClockA = 0;
    static unsigned char ucSwitchClockB = 0;

    /* Read the raw state of the push buttons.  Save the raw state
       (inverting the bit sense) if the caller supplied storage for the
       raw value. */
    ulData = (ROM_GPIOPinRead(GPIO_PORTF_BASE, ALL_BUTTONS));
    if(pucRawState)
    {
        *pucRawState = (unsigned char)~ulData;
    }

    /* Determine the switches that are at a different state than the debounced
       state. */
    ulDelta = ulData ^ g_ucButtonStates;

    /* Increment the clocks by one. */
    ucSwitchClockA ^= ucSwitchClockB;
    ucSwitchClockB = ~ucSwitchClockB;

    /* Reset the clocks corresponding to switches that have not changed state. */
    ucSwitchClockA &= ulDelta;
    ucSwitchClockB &= ulDelta;

    /* Get the new debounced switch state. */
    g_ucButtonStates &= ucSwitchClockA | ucSwitchClockB;
    g_ucButtonStates |= (~(ucSwitchClockA | ucSwitchClockB)) & ulData;

    /* Determine the switches that just changed debounced state. */
    ulDelta ^= (ucSwitchClockA | ucSwitchClockB);

    /* Return the debounced buttons states to the caller. */
    return(~g_ucButtonStates);
#endif
}
