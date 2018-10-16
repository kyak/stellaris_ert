function stellaris_customcode(buildInfo)
% Add startup_ccs.c to list of source files
% TODO: what is user wants to provide his own?... How to extend this
% file anyway? Seems i have to generate it dynamically via TLC.
% Or get rid of it by registering timer interrupt with driverlib functions.
if i_isSIL(buildInfo)
    % Don't add this file for SIL. Remove it, if already exists (when SIL is
    % launched right after PIL).
    buildInfo = remSourceFiles(buildInfo,'startup_ccs.c');
elseif i_isPIL(buildInfo)
    % Remove main_.c from sources for PIL
    buildInfo = remSourceFiles(buildInfo,['main_',buildInfo.ModelName,'.c']);
    buildInfo.addSourceFiles('startup_ccs.c',getpref('stellaris','TargetRoot'),'CustomCode');
else
    buildInfo.addSourceFiles('startup_ccs.c',getpref('stellaris','TargetRoot'),'CustomCode');
end

makertwArgs = buildInfo.BuildArgs;

for i=1:length(makertwArgs)
    if strcmp(makertwArgs(i).DisplayLabel,'EXT_MODE')
        externalMode = str2double(makertwArgs(i).Value);
    end
end

% See comments in stellaris_main.tlc as to why i'm doing this
if (externalMode == 1)
    buildInfo.addSourceFiles('ext_main.c',getpref('stellaris','TargetRoot'),'CustomCode');
end
end

function isSIL = i_isSIL(buildInfo)
if verLessThan('matlab','9.3')
    buildOpts = rtwprivate('get_makertwsettings',buildInfo.ModelName,'BuildOpts');
    isSIL = buildOpts.XilInfo.IsSil;
else
    modelCodegenMgr = coder.internal.ModelCodegenMgr.getInstance(buildInfo.ModelName);
    isSIL = modelCodegenMgr.MdlRefBuildArgs.XilInfo.IsSil;
end
end

function isPIL = i_isPIL(buildInfo)
if verLessThan('matlab','9.3')
    buildOpts = rtwprivate('get_makertwsettings',buildInfo.ModelName,'BuildOpts');
    isPIL = buildOpts.XilInfo.IsPil;
else
    modelCodegenMgr = coder.internal.ModelCodegenMgr.getInstance(buildInfo.ModelName);
    isPIL = modelCodegenMgr.MdlRefBuildArgs.XilInfo.IsPil;
end
end

function buildInfo = remSourceFiles(buildInfo,filename)
files = buildInfo.Src.Files;
idx = [];
for i=1:length(files)
    % If this is our file...
        if strcmp(files(i).DisplayLabel,filename)
            % Mark its position
            idx = [idx i];
        end    
end
% Remove all files at once
files(idx) = [];
% And update buildInfo
buildInfo.Src.Files = files;
end