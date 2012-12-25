classdef TargetApplicationFramework < rtw.pil.RtIOStreamApplicationFramework
%TARGETAPPLICATIONFRAMEWORK is TI LaunchPad application framework for PIL
  
    methods
        % constructor
        function this = TargetApplicationFramework(componentArgs)
            error(nargchk(1, 1, nargin, 'struct'));
            % call super class constructor
            this@rtw.pil.RtIOStreamApplicationFramework(componentArgs);
            
            this.addPILMain('target');

            % Additional source and library files to include in the build
            % must be added to the BuildInfo property

            % Get the BuildInfo object to update
            buildInfo = this.getBuildInfo;

            % Add device driver files to implement the target-side of the
            % host-target rtIOStream communications channel
            buildInfo.addSourceFiles([getpref('stellaris','TargetRoot'),...
				'/rtiostreamserial.c']);
        end
    end
end
