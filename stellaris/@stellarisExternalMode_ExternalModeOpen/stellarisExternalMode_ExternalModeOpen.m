%stellarisExternalMode_ExternalModeOpen class representing external mode user functions
%   stellarisExternalMode_ExternalModeOpen class representing target dependent
%   functionality implementing external mode user functions

%   Copyright 2007-2011 The MathWorks, Inc.

classdef stellarisExternalMode_ExternalModeOpen < CCPExternalMode_ExternalModeOpen

  methods(Access = 'public')
    function this = stellarisExternalMode_ExternalModeOpen(varargin)
      % Define constructors
      sigs{1} = {'modelName' 'ASAP2File'};

      % Parse arguments
      args = targets_parse_argument_pairs(sigs{end}, varargin);

      n = targets_find_signature(sigs, args);

      switch n
        % Constructor functions
        case 1
          superArgs = {'modelName', args.modelName};
        otherwise
            error(message('stellaris:codegen:ExternalMode_UnknownConstructor'));
      end      
      % call the super class constructor    
      this = this@CCPExternalMode_ExternalModeOpen(superArgs{:});
      this.dataTypeHandler = stellarisComms_DataTypeHandler();
      this.tuneableModelData = TargetsComms_CCPTunableModelData();
      try
        this.asap2 = MemoryMappedInfo_ASAP2('tunableModelData', this.tuneableModelData, 'ASAP2File', args.ASAP2File);
      catch evalException
        err = evalException;
        switch (err.identifier)
          case 'MemoryMappedInfo_ASAP2:Property:ASAP2File:Invalid'
            error(message('stellaris:codegen:ExternalMode_InvalidASAP2File', strrep( err.message, filesep, [ filesep, filesep ] ), this.modelName));
          otherwise
            rethrow(evalException);
        end
      end
      this.ccpComms = stellarisComms_ExternalModeCCP('modelName', this.modelName, 'numEventChannels', this.asap2.getNumEventChannels());
    end % function stellarisExternalMode_ExternalModeOpen
    
  end % methods(Access = 'public')

end % classdef
