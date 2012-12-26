/* stellaris_timer.c
 *
 * Specifies profile timer access functions
 *
 */

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

unsigned long profileTimerRead(void)
{
    static unsigned char firstTime = 0;
    unsigned long out = 0;
    if (firstTime == 0) {
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
        ROM_TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC);
        ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, 0xFFFFFFFF);
        ROM_TimerEnable(TIMER0_BASE, TIMER_A);
        out = 0xFFFFFFFF;
        firstTime = 1;
    } else {
        out = ROM_TimerValueGet(TIMER0_BASE, TIMER_A);
    }
    return out;
}
