classdef Timer < coder.profile.Timer
    methods
        function this = Timer
            
            % Configure data type returned by timer reads
            this.setTimerDataType('uint32');
            
            % What returns profileTimerRead() function
            % see BoardInit() in rtiostreamserial.c
            ticksPerSecond = 40e6;
            this.setTicksPerSecond(ticksPerSecond);
            
            % The timer counts downwards
            this.setCountDirection('down');
            
            % Configure source files required to access the timer
            timerSourceFile = fullfile(getpref('stellaris','TargetRoot'),...
                'stellaris_timer.c');
                       
            this.setSourceFile(timerSourceFile);
            
            % Configure the expression used to read the timer
            readTimerExpression = 'profileTimerRead()';
            this.setReadTimerExpression(readTimerExpression);
        end
    end
end
