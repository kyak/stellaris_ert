function stellaris_adc_ssena(blk,SSX_param_ena,param)

    act = get_param(blk,param);
    ena = get_param(blk,'MaskEnables');

    if strcmp(act,'enable')
        [ena{SSX_param_ena}] = deal('on');
    else
        [ena{SSX_param_ena}] = deal('off');
    end

    set_param(blk,'MaskEnables',ena);
end