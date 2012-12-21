function stellaris_download(modelName,makertwObj)

disp(['### Downloading ', modelName, ' to Stellaris LaunchPad...']);

TargetRoot = getpref('stellaris','TargetRoot');
CCSRoot = getpref('stellaris','CCSRoot');
CompilerRoot = getpref('stellaris','CompilerRoot');

%assignin('base','makertwObj',makertwObj);
%TODO: parse the PROGRAM_FILE_EXT from target_tools.mk
if (ischar(makertwObj)) %String 'PIL'
    outfile = modelName;
else
    outfile = fullfile(makertwObj.BuildDirectory, [modelName, '.out']);
end
if isunix
    % Convert out to bin for lm4flash
    system([CCSRoot,'/utils/tiobj2bin/tiobj2bin ',outfile,' ',fileparts(outfile),'.bin ',...
        CompilerRoot,'/bin/armofd ',CompilerRoot, '/bin/armhex ',CCSRoot,'/utils/tiobj2bin/mkhex4bin']);
    %TODO fail gracefully here.
    system(['lm4flash ',fileparts(outfile),'.bin']);
else
    system(['"',CCSRoot,'/ccs_base/scripting/examples/loadti/loadti.bat" -a ',...
        '-c "',TargetRoot,'/Stellaris_LaunchPad.ccxml" ',...
        '"',outfile,'"']);
end
end