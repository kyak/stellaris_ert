function stellaris_customcode(buildInfo)
% Add startup_ccs.c to list of source files
% TODO: what is user wants to provide his own?... How to extend this
% file anyway? Seems i have to generate it dynamically via TLC.
buildInfo.addSourceFiles('startup_ccs.c',getpref('stellaris','TargetRoot'),'CustomCode');