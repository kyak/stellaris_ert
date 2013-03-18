%% GPIO Write
% Populate legacy_code structure with information
GPIOWrite = legacy_code('initialize');
GPIOWrite.SFunctionName = 'sfun_GPIOWrite';
GPIOWrite.HeaderFiles = {'gpiolct.h'};
GPIOWrite.SourceFiles = {'gpiolct.c'};
GPIOWrite.OutputFcnSpec = 'GPIOWrite(uint32 p1, uint8 u1, uint8 u2)';
% Support calling from within For-Each subsystem
GPIOWrite.Options.supportsMultipleExecInstances = true;
%% GPIO Read
GPIORead = legacy_code('initialize');
GPIORead.SFunctionName = 'sfun_GPIORead';
GPIORead.HeaderFiles = {'gpiolct.h'};
GPIORead.SourceFiles = {'gpiolct.c'};
GPIORead.OutputFcnSpec = 'int32 y1 = GPIORead(uint32 p1, uint8 u1)';
GPIORead.Options.supportsMultipleExecInstances = true;
%% GPIO Setup
GPIOSetup = legacy_code('initialize');
GPIOSetup.SFunctionName = 'sfun_GPIOSetup';
GPIOSetup.HeaderFiles = {'gpiolct.h'};
GPIOSetup.SourceFiles = {'gpiolct.c'};
GPIOSetup.StartFcnSpec = 'GPIOSetup(uint32 p1, uint32 p2, uint8 p3)';
GPIOSetup.Options.supportsMultipleExecInstances = true;
%% Push Buttons
Buttons = legacy_code('initialize');
Buttons.SFunctionName = 'sfun_Buttons';
Buttons.HeaderFiles = {'buttonslct.h'};
Buttons.SourceFiles = {'buttonslct.c'};
Buttons.StartFcnSpec = 'ButtonsInit()';
Buttons.OutputFcnSpec = 'uint8 y1 = ButtonsRead(uint8 y2[1])';
%% UART Read
UARTRead = legacy_code('initialize');
UARTRead.SFunctionName = 'sfun_UARTRead';
UARTRead.HeaderFiles = {'uartlct.h'};
UARTRead.SourceFiles = {'uartlct.c'};
UARTRead.StartFcnSpec = 'UARTInit()';
UARTRead.OutputFcnSpec = 'int32 y1 = UARTRead(uint8 p1, uint8 y2[1])';
UARTRead.Options.supportsMultipleExecInstances = true;
%% UART Write
UARTWrite = legacy_code('initialize');
UARTWrite.SFunctionName = 'sfun_UARTWrite';
UARTWrite.HeaderFiles = {'uartlct.h'};
UARTWrite.SourceFiles = {'uartlct.c'};
UARTWrite.StartFcnSpec = 'UARTInit()';
UARTWrite.OutputFcnSpec = 'UARTWrite(uint8 p1, uint8 u1)';
UARTWrite.Options.supportsMultipleExecInstances = true;
%% Built-in temperature sensor
TempSensor = legacy_code('initialize');
TempSensor.SFunctionName = 'sfun_TempSensor';
TempSensor.HeaderFiles = {'tempsensorlct.h'};
TempSensor.SourceFiles = {'tempsensorlct.c'};
TempSensor.StartFcnSpec = 'TempSensorInit()';
TempSensor.OutputFcnSpec = 'uint32 y1 = TempSensorRead(uint8 p1)';
%% ADC
ADC = legacy_code('initialize');
ADC.SFunctionName = 'sfun_ADC';
ADC.HeaderFiles = {'adclct.h'};
ADC.SourceFiles = {'adclct.c'};
ADC.StartFcnSpec = 'ADCInit(uint8 p1, uint8 p2, uint8 p3[4], uint32 p4[8], uint32 p5[4], uint32 p6[4], uint32 p7, uint32 p8[4], uint32 p9[4], uint32 p10)';
ADC.OutputFcnSpec = 'ADCStep(uint8 p1, uint8 p3[4], uint32 y1[8], uint32 y2[4], uint32 y3[4], uint32 y4[1])';
%legacy_code('generate_for_sim', ADC);
%legacy_code('sfcn_tlc_generate', ADC)
%legacy_code('slblock_generate', ADC);
%% Put multiple registration files together
def = [GPIOWrite(:);GPIORead(:);GPIOSetup(:);Buttons(:);UARTRead(:);UARTWrite(:);TempSensor(:);ADC(:)];
%% Legacy Code Tool
% Generate, compile and link S-function for simulation
legacy_code('generate_for_sim', def);
% Generate TLC file for Code Generation
legacy_code('sfcn_tlc_generate', def);
% Generate according Simulink Block
%legacy_code('slblock_generate', def);
% Generate rtwmakecfg.m file to automatically set up some build options
legacy_code('rtwmakecfg_generate', def);