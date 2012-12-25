classdef Launcher < rtw.connectivity.Launcher
%LAUNCHER is TI Stellaris LaunchPad class for launching a PIL application
 
    methods
        % constructor
        function this = Launcher(componentArgs, builder)
            narginchk(2, 2);
            % call super class constructor
            this@rtw.connectivity.Launcher(componentArgs, builder);
        end

        % destructor
        function delete(this) %#ok
        end

        % Start the application
        function startApplication(this)
            % get name of the executable file
            exe = this.getBuilder.getApplicationExecutable; 
            % allow a back door for tests to skip download to hardware
            downloadToLaunchPad = 1;
            if evalin('base','exist(''downloadToLaunchPad'')')
                downloadToLaunchPad = evalin('base', 'downloadToLaunchPad' );
            end
            if downloadToLaunchPad
                stellaris_download(exe,'PIL');
            end
			disp('### Starting PIL execution on TI Stellaris LaunchPad');
        end
        
        % Stop the application
        function stopApplication(~)
            disp('### Stopping PIL execution on TI Stellaris LaunchPad')
        end
    end
end
