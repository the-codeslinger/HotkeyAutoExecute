#pragma once

struct HotkeyItem;

class HotkeyExecutor
{
public:
    /**
     * Call the Windows `SendInput()` function to emulate the key presses for the hotkey.
     * 
     * @param hotkey Contains the native Windows key codes for the key itself and optional
     *               modifiers.
     */
    virtual void execute(const HotkeyItem& hotkey) const = 0;
    
    virtual ~HotkeyExecutor(){}
};
