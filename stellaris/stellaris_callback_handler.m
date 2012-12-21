function stellaris_callback_handler(hDlg, hSrc)

% Setup the hardware configuration
slConfigUISetVal(hDlg, hSrc, 'ProdHWDeviceType', 'Texas Instruments->TMS470');
        
% Set the target language to C and disable modification
slConfigUISetVal(hDlg, hSrc, 'TargetLang', 'C');
slConfigUISetEnabled(hDlg, hSrc, 'TargetLang', 0);

% The target is model reference compliant
slConfigUISetVal(hDlg, hSrc, 'ModelReferenceCompliant', 'on');
slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceCompliant', false);

% Configure solver
slConfigUISetVal(hDlg, hSrc, 'SolverType', 'Fixed-step');
slConfigUISetVal(hDlg, hSrc, 'Solver', 'FixedStepDiscrete');

% Use our own ert_main.c and disable this option at all
slConfigUISetVal(hDlg, hSrc, 'ERTCustomFileTemplate', 'stellaris_srmain.tlc');
slConfigUISetVal(hDlg, hSrc, 'GenerateSampleERTMain', 'off');
slConfigUISetEnabled(hDlg, hSrc, 'GenerateSampleERTMain',0);

% Configure PostCodeGen Command to execute
slConfigUISetVal(hDlg, hSrc, 'PostCodeGenCommand', 'stellaris_customcode(buildInfo)');