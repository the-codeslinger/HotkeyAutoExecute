#include <QDebug>
#include <QKeyEvent>
#include <QKeySequence>

#include <hotkeyexecutor_win.h>
#include <hotkeyitem.h>

void
HotkeyExecutor_Win::execute(const HotkeyItem& hotkey) const
{    
    auto keys = parseHotkey(hotkey);
    auto result = SendInput(keys.count(), keys.data(), sizeof(INPUT));
    if (keys.count() != result) {
        qWarning() << "Could not send all key presses; only " << result 
                   << " out of " << keys.count() << " succeeded";
    }
}

QVector<INPUT>
HotkeyExecutor_Win::parseHotkey(const HotkeyItem& hotkey) const
{
    auto windowsKey = hotkey.nativeSequence.key;
    auto windowsModifiers = hotkey.nativeSequence.modifiers;
    
    auto inputs = QVector<INPUT>{};
    
    // Modifiers must come first!
    for (auto modifierKey : windowsModifiers) {
        inputs.append(createKeyPress(modifierKey));
    }    
    inputs.append(createKeyPress(windowsKey));
    
    for (auto modifierKey : windowsModifiers) {
        inputs.append(createKeyRelease(modifierKey));
    }    
    inputs.append(createKeyRelease(windowsKey));
    
    return inputs;
}

INPUT 
HotkeyExecutor_Win::createKeyPress(quint32 windowsKeyCode) const
{
    auto keyPress = INPUT{};
    keyPress.type = INPUT_KEYBOARD;
    keyPress.ki.wVk = windowsKeyCode;
    return keyPress;
}

INPUT 
HotkeyExecutor_Win::createKeyRelease(quint32 windowsKeyCode) const
{        
    auto keyRelease = INPUT{};
    keyRelease.type = INPUT_KEYBOARD;
    keyRelease.ki.wVk = windowsKeyCode;
    keyRelease.ki.dwFlags = KEYEVENTF_KEYUP;
    return keyRelease;
}
