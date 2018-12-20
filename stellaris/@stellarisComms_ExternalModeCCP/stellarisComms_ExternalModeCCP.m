%stellarisCOMMS_EXTERNALMODECCP class used for External Mode CCP communications for stellaris
%   stellarisCOMMS_EXTERNALMODECCP class used for External Mode CCP communications 
%   for stellaris

%   Copyright 1990-2012 The MathWorks, Inc.

classdef stellarisComms_ExternalModeCCP < TargetsComms_ExternalModeCCPWithBlock
  
  methods
    
    function this = stellarisComms_ExternalModeCCP(varargin)
      % Define constructors
      sigs{1} = {'modelName' 'numEventChannels'};

      % Parse arguments
      args = targets_parse_argument_pairs(sigs{end}, varargin);

      n = targets_find_signature(sigs, args);
      
      switch n
        case 1
          superArgs = {'modelName', args.modelName, 'numEventChannels', args.numEventChannels};
        otherwise
            error(message('stellaris:codegen:ExternalMode_UnknownConstructor'));
      end
      % call super class constructor
      this = this@TargetsComms_ExternalModeCCPWithBlock(superArgs{:});
    end % function stellarisComms_ExternalModeCCP

  end % methods		

  methods(Access = 'protected')	
	
    function applicationChannel = getApplicationChannel(this)
      %vector_channel = get_param(this.modelName, 'v_can_channel');
      vector_channel = 'MATLAB 1';
      applicationChannel = TargetsComms_VectorApplicationChannel.getApplicationChannelNumeric(vector_channel);
    end % function get.ApplicationChannel
    
    function targetEndian = getTargetEndian(this)
      targetEndian = stellarisComms_DataTypeHandler.targetEndian;
    end % function get.targetEndian
    
    function blkSearchExpr = getBlkSearchExpr(this)
      % Get user Target Preferences and the chip info
      %tgtPrefs = getTgtPrefInfo(this.modelName);
      % Set the masktype string for the system search the model for a CCP block
      blkSearchExpr = '^Stellaris CAN Calibration Protocol$'; 
    end % function get.blkSearchExpr

  end % methods(Access = 'protected')
  
end % classdef stellarisComms_ExtModeCCPMaster
