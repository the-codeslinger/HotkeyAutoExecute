#pragma once

#include <windows.h>

#include <Qt>
#include <QVector>

class QKeySequence;
class HotkeyItem;

class HotkeyExecutor
{
public:
    void execute(const HotkeyItem& hotkey) const;

private:
    QVector<INPUT> parseHotkey(const HotkeyItem& hotkey) const;
    
    INPUT createKeyPress(quint32 windowsKeyCode) const;
    INPUT createKeyRelease(quint32 windowsKeyCode) const;
};
