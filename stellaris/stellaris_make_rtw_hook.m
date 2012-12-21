function stellaris_make_rtw_hook(hookMethod,modelName,~,~,~,~)
switch hookMethod
    case 'before_make'
        stellarisBeforeMakeHook(modelName);
    case 'after_make'
        stellarisAfterMakeHook(modelName);
end