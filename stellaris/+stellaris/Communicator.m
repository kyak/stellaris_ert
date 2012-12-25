classdef Communicator < rtw.connectivity.RtIOStreamHostCommunicator
    %COMMUNICATOR implements a host-side communicator for TI Stellaris LaunchPad
    
    methods
        function this = Communicator(componentArgs, ...
                launcher, rtiostreamLib)
            % This method simply passes all the arguments to the
            % superclass constructor
            
            this@rtw.connectivity.RtIOStreamHostCommunicator...
                (componentArgs, launcher, rtiostreamLib);
        end
    end
end
