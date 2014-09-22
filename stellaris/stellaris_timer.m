function hLib = stellaris_timer


hLib = RTW.TflTable;
%---------- entry: code_profile_read_timer ----------- 
hEnt = RTW.TflCFunctionEntry;
hEnt.setTflCFunctionEntryParameters( ...
          'Key', 'code_profile_read_timer', ...
          'Priority', 100, ...
          'ImplementationName', 'profileTimerRead', ...
          'ImplementationSourceFile', fullfile(getpref('stellaris','TargetRoot'),'stellaris_timer.c'));

hEnt.EntryInfo.CountDirection = 'RTW_TIMER_DOWN';
hEnt.EntryInfo.TicksPerSecond = 80000000;
% Conceptual Args

arg = hEnt.getTflArgFromString('y1','uint32');
arg.IOType = 'RTW_IO_OUTPUT';
hEnt.addConceptualArg(arg);

% Implementation Args 

arg = hEnt.getTflArgFromString('y1','uint32');
arg.IOType = 'RTW_IO_OUTPUT';
hEnt.Implementation.setReturn(arg); 

hLib.addEntry( hEnt ); 

