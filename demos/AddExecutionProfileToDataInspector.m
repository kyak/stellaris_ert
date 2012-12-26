function AddExecutionProfileToDataInspector(executionProfile)

    if nargin < 1
        executionProfile = evalin('base','executionProfile');
    end
    
    ds = Simulink.SimulationData.Dataset;
    
    % Look for first section section with number of times > 1
    nSectionProfiles = executionProfile.getNumSectionProfiles;
    for index = 1:nSectionProfiles
        if length(executionProfile.getSectionProfile(index).getTimes) > 1
            break;
        end
    end
    
    samplePeriod = executionProfile.getSectionProfile(index).getSamplePeriod;
    
    try
        executionTicks = executionProfile.getSectionProfile(index).getTimes;
    catch
        executionTicks = executionProfile.getSectionProfile(index).getTicks;
    end

    sampleTimes = (0:(length(executionTicks)-1)).*samplePeriod;

    element = Simulink.SimulationData.Signal;
    element.Name = 'PIL Execution Time (sec)';
    element.Values = timeseries(executionTicks,sampleTimes(:));
    ds = ds.addElement(element);
    
    Simulink.sdi.createRun('Execution Profile', 'namevalue',...
               {'executionProfile'},{ds});
    
%     if Simulink.sdi.getRunCount == 0
%         runID = Simulink.sdi.createRun;
%     else
%         runID = Simulink.sdi.getRunIDByIndex(Simulink.sdi.getRunCount);
%     end
% 
%     Simulink.sdi.addToRun(runID,'base',{'ds'});
%     Simulink.sdi.addToRun(runID,'namevalue',{signalName},{ds});

end
