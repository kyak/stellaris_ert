%stellarisCOMMS_DATATYPEHANDLER class representing stellaris communications data type handler
%   stellarisCOMMS_DATATYPEHANDLER class representing stellaris communications data 
%   type handler. The data type handler converts to and from host and target 
%   data representations

%   Copyright 1990-2009 The MathWorks, Inc.

classdef stellarisComms_DataTypeHandler < TargetsComms_DataTypeHandler
      
  properties(Constant = true)
    % BIG ENDIAN = 1, LITTLE ENDIAN = 0
    targetEndian = 0;    
  end %propeties(Static = true)
  
  methods
    
    function this = stellarisComms_DataTypeHandler()
      this.memoryUnits = 'uint8';
      % Initialise the conversionInfo structure
      dataType.name = 'uint8';
      dataType.map = 1;
      dataType.numMemoryUnits =  1;
      this.conversionInfo.dataTypes(end + 1) = { dataType };
      this.conversionInfo.hash(end + 1) = { dataType.name };
      
      dataType.name = 'int8';
      dataType.map = 1;
      dataType.numMemoryUnits = 1;
      this.conversionInfo.dataTypes(end + 1) = { dataType };
      this.conversionInfo.hash(end + 1) = { dataType.name };
      
      dataType.name = 'uint16';
      dataType.map = [1 2];
      dataType.numMemoryUnits = 2;
      this.conversionInfo.dataTypes(end + 1) = { dataType };
      this.conversionInfo.hash(end + 1) = { dataType.name };
      
      dataType.name = 'int16';
      dataType.map = [1 2];
      dataType.numMemoryUnits = 2;
      this.conversionInfo.dataTypes(end + 1) = { dataType };
      this.conversionInfo.hash(end + 1) = { dataType.name };
      
      dataType.name = 'uint32';
      dataType.map = [1 2 3 4];
      dataType.numMemoryUnits = 4;
      this.conversionInfo.dataTypes(end + 1) = { dataType };
      this.conversionInfo.hash(end + 1) = { dataType.name };

      dataType.name = 'int32';
      dataType.map = [1 2 3 4];      
      dataType.numMemoryUnits = 4;
      this.conversionInfo.dataTypes(end + 1) = { dataType };
      this.conversionInfo.hash(end + 1) = { dataType.name };

      dataType.name = 'single';
      dataType.map = [1 2 3 4];
      dataType.numMemoryUnits = 4;      
      this.conversionInfo.dataTypes(end + 1) = { dataType };
      this.conversionInfo.hash(end + 1) = { dataType.name };      
    end % function stellarisComms_DataTypeHandler
    
  end % methods
      
end % classdef
