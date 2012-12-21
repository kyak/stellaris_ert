function [ ] = stellarisAfterMakeHook( modelName )
% Check the model if a target_paths.mk should be created
if (strcmp(get_param(modelName,'SystemTargetFile')  ,'stellaris.tlc') && ...
    strcmp(get_param(modelName,'TemplateMakefile')  ,'stellaris_tmf') && ...
    strcmp(get_param(modelName,'TargetHWDeviceType'),'Texas Instruments->TMS470'))
  
    % Check if user chose to Download to Launchpad in Settings
    makertwObj = get_param(gcs, 'MakeRTWSettingsObject');
    makertwArgs = makertwObj.BuildInfo.BuildArgs;
    downloadToLaunchPad = 1;
    for i=1:length(makertwArgs)
        if strcmp(makertwArgs(i).DisplayLabel,'LAUNCHPAD_DOWNLOAD')
            downloadToLaunchPad = str2double(makertwArgs(i).Value);
        end
    end
    
    % allow a back door for tests to skip download to hardware
    if evalin('base','exist(''downloadToLaunchPad'')')
        downloadToLaunchPad = evalin('base', 'downloadToLaunchPad' );
    end
    
    if ~i_isPilSim && ~i_isModelReferenceBuild(modelName) &&...
            downloadToLaunchPad
        stellaris_download(modelName,makertwObj)
    end

end

end

function isPilSim = i_isPilSim
    s = dbstack;
    isPilSim = false;
    for i=1:length(s)
        if strfind(s(i).name,'build_pil_target')
            isPilSim=true;
            break;
        end
    end
end
    
function isMdlRefBuild = i_isModelReferenceBuild(modelName)
    mdlRefTargetType = get_param(modelName, 'ModelReferenceTargetType');
    isMdlRefBuild = ~strcmp(mdlRefTargetType, 'NONE');
end