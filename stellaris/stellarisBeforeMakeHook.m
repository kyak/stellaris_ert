function [ ] = stellarisBeforeMakeHook( modelName )

% Check the model if a target_paths.mk should be created
if (strcmp(get_param(modelName,'SystemTargetFile')  ,'stellaris.tlc') && ...
    strcmp(get_param(modelName,'TemplateMakefile')  ,'stellaris_tmf') && ...
    strcmp(get_param(modelName,'TargetHWDeviceType'),'Texas Instruments->TMS470'))

    TargetRoot = getpref('stellaris','TargetRoot');
	CompilerRoot = getpref('stellaris','CompilerRoot');
    CCSRoot = getpref('stellaris','CCSRoot');
    StellarisWareRoot = getpref('stellaris','StellarisWareRoot');
    
    % Create the target paths makefile
    makefileName = 'target_paths.mk';
    fid = fopen(makefileName,'w');
    fwrite(fid, sprintf('%s\n\n', '# launchpad paths'));
    fwrite(fid, sprintf('CompilerRoot  = %s\n', CompilerRoot));
    fwrite(fid, sprintf('TargetRoot    = %s\n', TargetRoot));
    fwrite(fid, sprintf('CCSRoot       = %s\n', CCSRoot));
    fwrite(fid, sprintf('StellarisWareRoot       = %s\n', StellarisWareRoot));
    fclose(fid);

end
 