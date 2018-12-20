function hfcns = stellarisExternalModeOpen()
%stellarisEXTERNALMODEOPEN Implements external mode using the External Mode Open Protocol
%   stellarisEXTERNALMODEOPEN Implements external mode using the External Mode Open Protocol

%   Copyright 2007-2008 The MathWorks, Inc.

% Get handles to the target independent functionality
targetsExternalMode_hfcns = TargetsExternalModeOpen();

hfcns.i_UserHandleError           = targetsExternalMode_hfcns.i_UserHandleError;
hfcns.i_UserInit                  = @i_UserInit;
hfcns.i_UserConnect               = targetsExternalMode_hfcns.i_UserConnect;
hfcns.i_UserSetParam              = targetsExternalMode_hfcns.i_UserSetParam;
hfcns.i_UserGetParam              = targetsExternalMode_hfcns.i_UserGetParam;
hfcns.i_UserSignalSelect          = targetsExternalMode_hfcns.i_UserSignalSelect;
hfcns.i_UserSignalSelectFloating  = targetsExternalMode_hfcns.i_UserSignalSelectFloating;
hfcns.i_UserTriggerSelect         = targetsExternalMode_hfcns.i_UserTriggerSelect;
hfcns.i_UserTriggerSelectFloating = targetsExternalMode_hfcns.i_UserTriggerSelectFloating;
hfcns.i_UserTriggerArm            = targetsExternalMode_hfcns.i_UserTriggerArm;
hfcns.i_UserTriggerArmFloating    = targetsExternalMode_hfcns.i_UserTriggerArmFloating;
hfcns.i_UserCancelLogging         = targetsExternalMode_hfcns.i_UserCancelLogging;
hfcns.i_UserCancelLoggingFloating = targetsExternalMode_hfcns.i_UserCancelLoggingFloating;
hfcns.i_UserStart                 = targetsExternalMode_hfcns.i_UserStart;
hfcns.i_UserStop                  = targetsExternalMode_hfcns.i_UserStop;
hfcns.i_UserPause                 = targetsExternalMode_hfcns.i_UserPause;
hfcns.i_UserStep                  = targetsExternalMode_hfcns.i_UserStep;
hfcns.i_UserContinue              = targetsExternalMode_hfcns.i_UserContinue;
hfcns.i_UserGetTime               = targetsExternalMode_hfcns.i_UserGetTime;
hfcns.i_UserDisconnect            = targetsExternalMode_hfcns.i_UserDisconnect;
hfcns.i_UserDisconnectImmediate   = targetsExternalMode_hfcns.i_UserDisconnectImmediate;
hfcns.i_UserDisconnectConfirmed   = targetsExternalMode_hfcns.i_UserDisconnectConfirmed;
hfcns.i_UserTargetStopped         = targetsExternalMode_hfcns.i_UserTargetStopped;
hfcns.i_UserFinalUpload           = targetsExternalMode_hfcns.i_UserFinalUpload;
hfcns.i_UserCheckData             = targetsExternalMode_hfcns.i_UserCheckData;

%**************************************************************************
%                          PUBLIC FUNCTIONS
%**************************************************************************

function glbVars = i_UserInit(glbVars)
%
% Called at the very beginning of the External Mode connect process before
% the model has been compiled and before the 'Connect' message has been issued.
% This is the place to perform any initialization needed at the start of an
% External Mode session, so long as the model checksum is not changed (which
% will cause the ensuing 'Connect' message to fail).
%

targetsExternalMode_hfcns = TargetsExternalModeOpen();
% Call the target independent part of this function
glbVars = targetsExternalMode_hfcns.i_UserInit(glbVars);

glbVars.target.ExternalModeOpen = stellarisExternalMode_ExternalModeOpen('modelName', glbVars.glbModel, 'ASAP2File', glbVars.target.target_file_asap2);

% end i_UserInit

