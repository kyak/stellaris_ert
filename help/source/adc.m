%% Analog to Digital Converter
% An analog-to-digital converter (ADC) is a peripheral that converts a
% continuous analog voltage to a discrete digital number. Two identical
% converter modules are included, which share 12 input channels. The
% Stellaris® ADC module features 12-bit conversion resolution and supports
% 12 input channels, plus an internal temperature sensor. Each ADC module
% contains four programmable sequencers allowing the sampling of multiple
% analog input sources.
%% Description
% The ADC block implementation is based completely on DriverLib ADC*
% functions. Refer to <http://www.ti.com/tool/SW-DRL-UG DriverLib User
% Guide> for more information.
%
% Additional information can (and probably should) be found in
% <http://www.ti.com/product/lm4f120h5qr Stellaris LM4F120H5QR
% Microcontroller Data Sheet>.
%
% It is advised that you make yourself acquainted with ADC peripheral as it
% would greatly help understand how to set up and use this Simulink
% block.
%
% By default, this block is precofigured to sample internal temperature
% sensor values.
%% Block parameters
%
% Note that there is a limited amount of checks (really limited) on chosen
% setup both in ADC block and DriverLib. It is user's responsibility to
% choose parameters so that they make sense and don't conflict.
%
% *Main tab:*
% 
% * Base address of ADC module
%
% TI Stellaris LaunchPad is equipped with two ADC modules. You may choose
% between ADC0 and ADC1.
%
% * Hardware oversampling of ADC
%
% This function configures the hardware oversampling for the ADC, which can
% be used to provide better resolution on the sampled data. Oversampling is
% accomplished by averaging multiple samples from the same analog input.
% Six different oversampling rates are supported; 2x, 4x, 8x, 16x, 32x, and
% 64x. Specifying an oversampling factor of zero disables hardware
% oversampling.
%
% _Reference: see ADCHardwareOversampleConfigure in DriverLib User
% Guide._
%
% * ADC sample rate
%
% This function configures the rate at which the ADC samples are captured
% by the ADC block. Enabling hardware oversampling will affect the actual
% sample rate ADC will operate with.
%
% _Reference: see SysCtlADCSpeedSet in DriverLib User Guide._
%
% *SSX tabs:*
%
% * Enable Sample Sequencer
%
% This popup controls whether the specific Sample Sequencer (SS) is
% enabled. All other parameters are greyed out if the SS is disabled.
%
% _Reference: see ADCSequenceEnable in DriverLib User Guide._
%
% * Trigger source to initiate sequence
%
% Choose the trigger source to initiate capture sequence. You may choose
% one of the following trigger sources:
%
% _ADC_TRIGGER_PROCESSOR_: A trigger generated by the processor.
%
% _ADC_TRIGGER_COMP0/ADC_TRIGGER_COMP1_: A trigger generated by the
% first/second analog comparator. (*NOT IMPLEMENTED*)
%
% _ADC_TRIGGER_EXTERNAL_: A trigger generated by an input from the Port B4
% pin. (*NOT TESTED*)
%
% _ADC_TRIGGER_TIMER_: A trigger generated by a timer. (*NOT IMPLEMENTED*)
%
% _ADC_TRIGGER_ALWAYS_: A trigger that is always asserted, causing the
% sample sequence to capture repeatedly. (*NOT TESTED*)
%
% _Reference: see ADCSequenceConfigure in DriverLib User Guide._
%
% * Priority of sample sequencer
%
% Choose the value between 0 and 3, where 0 represents the highest priority
% and 3 the lowest. All priorities must be unique between sampel
% sequencers.
%
% _Reference: see ADCSequenceConfigure in DriverLib User Guide._
%
% * Step config
%
% Each sequencer has a different number of steps. The table below
% summarizes the possible number of steps for each sequencer.
%
% <html>
% <a name="steps_table">Sequencers and steps</a>
% </html>
%
% <html> <table border=1><tr><td>Sequencer</td><td>Number of
% steps</td></tr> <tr><td>SS0</td><td>8</td></tr>
% <tr><td>SS1</td><td>4</td></tr> <tr><td>SS2</td><td>4</td></tr>
% <tr><td>SS3</td><td>1</td></tr> </table></html>
%
% When the sample sequencer is enabled, you must configure one or more
% steps. The step configuration is carried out by choosing the "New
% configuration..." item in the popup of the specific step.
%
% Upon choosing the "New configuration..." item, you will be presented with
% a simple GUI to choose one or more parameters:
%
% _ADC_CTL_TS_: Select internal temperature sensor.
%
% _ADC_CTL_IE_: Cause an interrupt when the step is complete.
%
% _ADC_CTL_END_: Define the step as the last one in the sequence.
%
% _ADC_CTL_D_: Configure channel for differential operation.
%
% _ADC_CTL_CH0-11_: Choose input channel 0 to 11.
%
% The parameters you've chosen will be logically OR'd and form the
% configuration for the step.
%
% You will be able to see your new configuration for the step after you
% re-open the ADC block.
%
% If you wish to delete the configuration, choose 'None' from the popup.
%
% If you wish to reconfigure the step, first delete the configuration by
% choosing 'None'. After re-opening the ADC block, you will be able to
% choose the 'New configuration..." from the popup.
%
% It is worth mentioning that you may up each step to sample different ADC
% channels.
%
% _Reference: see ADCSequenceStepConfigure in DriverLib User Guide._
%
%% Block outputs
% The block provides four outputs by the number of sequencers. Each output
% is an array of uint32. The size of an array is equal to the number of
% steps for according sample sequencer. See the <#steps_table above table> .
%% Examples
% Built-in temperature sensor
% <tempsensor.html Built-in temperature sensor>