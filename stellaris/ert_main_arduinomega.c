/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'arduinomega2560_communication'.
 *
 * Model version                  : 1.142
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 19 2013)
 * C/C++ source code generated on : Tue Apr 09 21:04:57 2013
 *
 * Target selection: realtime.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "arduinomega2560_communication.h"
#include "Arduino.h"
#include <ext_work.h>                  /* External mode header files */
#include <ext_svr.h>
#include <ext_share.h>
#include <updown.h>
#define STEP_SIZE                      (unsigned long) (100000)

int_T main(void)
{
  unsigned long oldtime = 0L;
  unsigned long actualtime;
  init();

  /* initialize external mode */
  rtParseArgsForExtMode(0, NULL);
  arduinomega2560_communication_initialize();

  /* External mode */
  rtSetTFinalForExtMode(&rtmGetTFinal(arduinomega2560_communicatio_M));
  rtExtModeCheckInit(1);

  {
    boolean_T rtmStopReq = FALSE;
    rtExtModeWaitForStartPkt(arduinomega2560_communicatio_M->extModeInfo, 1,
      &rtmStopReq);
    if (rtmStopReq) {
      rtmSetStopRequested(arduinomega2560_communicatio_M, TRUE);
    }
  }

  rtERTExtModeStartMsg();

#ifdef _RTT_USE_SERIAL1_

  Serial_begin(1, 9600);

#endif

#ifdef _RTT_USE_SERIAL2_

  Serial_begin(2, 9600);

#endif

#ifdef _RTT_USE_SERIAL3_

  Serial_begin(3, 9600);

#endif

  /* The main step loop */
  while ((rtmGetErrorStatus(arduinomega2560_communicatio_M) == (NULL)) &&
         !rtmGetStopRequested(arduinomega2560_communicatio_M)) {
    actualtime = micros();
    if ((unsigned long) (actualtime - oldtime) >= STEP_SIZE) {
      oldtime = actualtime;

      /* External mode */
      {
        boolean_T rtmStopReq = FALSE;
        rtExtModeOneStep(arduinomega2560_communicatio_M->extModeInfo, 1,
                         &rtmStopReq);
        if (rtmStopReq) {
          rtmSetStopRequested(arduinomega2560_communicatio_M, TRUE);
        }
      }

      arduinomega2560_communication_output();

      /* Get model outputs here */

      /* External mode */
      rtExtModeUploadCheckTrigger(1);

      {                                /* Sample time: [0.1s, 0.0s] */
        rtExtModeUpload(0, arduinomega2560_communicatio_M->Timing.taskTime0);
      }

      arduinomega2560_communication_update();
      rtExtModeCheckEndTrigger();
    }
  }

  rtExtModeShutdown(1);
  delay(1000);
  arduinomega2560_communication_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
