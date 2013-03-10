options = struct('format','html','outputDir','../html');
publish('index.m',options);
publish('gs.m',options);
publish('blocks.m',options);
publish('uart.m',options);
publish('gpio.m',options);
publish('buttons.m',options);
publish('pil.m',options);
publish('sa.m',options);
publish('tempsensor.m',options);
publish('adc.m',options);

%re-add help to path to refresh menu
tgtpath = getpref('stellaris','TargetRoot');
tgtpath = tgtpath(1:end-length('/stellaris'));
rmpath(fullfile(tgtpath,'help'));
addpath(fullfile(tgtpath,'help'));