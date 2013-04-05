function stellaris_adc_stepconfig(blk,step_idx)
    values = get_param(blk,'MaskValues');
    %str = inputdlg;

    % See drivelib/adc.h
    config = {
        'None'            '00000000'    'Disable the step'
        'ADC_CTL_TS'      '00000080'    'Temperature sensor select'
        'ADC_CTL_IE'      '00000040'    'Interrupt enable'
        'ADC_CTL_END'     '00000020'    'Sequence end select'
        'ADC_CTL_D'       '00000010'    'Differential select'
        'ADC_CTL_CH0'     '00000000'    'Input channel 0'
        'ADC_CTL_CH1'     '00000001'    'Input channel 1'
        'ADC_CTL_CH2'     '00000002'    'Input channel 2'
        'ADC_CTL_CH3'     '00000003'    'Input channel 3'
        'ADC_CTL_CH4'     '00000004'    'Input channel 4'
        'ADC_CTL_CH5'     '00000005'    'Input channel 5'
        'ADC_CTL_CH6'     '00000006'    'Input channel 6'
        'ADC_CTL_CH7'     '00000007'    'Input channel 7'
        'ADC_CTL_CH8'     '00000008'    'Input channel 8'
        'ADC_CTL_CH9'     '00000009'    'Input channel 9'
        'ADC_CTL_CH10'    '0000000A'    'Input channel 10'
        'ADC_CTL_CH11'    '0000000B'    'Input channel 11'
        };

    % Mangle list to display in list dialog
    config_list = cell(1,length(config));
    for i=1:length(config)
        config_list{i} = sprintf('%s (%s)',config{i,[3,1]});
    end
    
    [Selection, ok] = listdlg('PromptString','Select one or more configuration settings:',...
                'SelectionMode','multiple',...
                'Name','ADC Step Configuration',...
                'ListSize',[300 300],...
                'ListString',config_list);
    
    if (ok == 1)
        % String to display in mask
        str = strjoin(config(Selection),'|');
        % Value to keep in mask and pass to S-function
        vals = hex2dec(config(Selection,2));
        val = 0;
        for i=1:length(Selection)
            val = bitor(val,vals(i));
        end
        % We could keep that in UserData, but i want it directly visible
        % and also to avoid possible desync issues
        % So append to popup display string
        % We will parse it out in Initialization pane
        str = [str,'(',num2str(val),')'];
    else
        % User pressed Cancel button
        str = 'None(0)';
    end
    
    % Revert back to '----'
    values{step_idx} = '----';
    % Display the config to user
    values{step_idx+1} = str;
    set_param(blk,'MaskValues',values);
    %if (ok == 1)
        % User pressed OK
        %msgbox('Configuration is saved and selected for this step. It will appear in popup next time you open the ADC block');
    %end
end