#pragma once

#include <windows.h>

#include <Qt>
#include <QVector>

#include <hotkeyexecutor.h>

class QKeySequence;
class HotkeyItem;

/**
 * Interfaces with the Windows API to execute a `SendInput()` function call.
 * 
 * This class sends key presses and the required corresponding key releases in a single
 * call to `SendInput()`.
 */
class HotkeyExecutor_Win : public HotkeyExecutor
{
public:
    /**
     * Call the Windows `SendInput()` function to emulate the key presses for the hotkey.
     * 
     * @param hotkey Contains the native Windows key codes for the key itself and optional
     *               modifiers.
     */
    void execute(const HotkeyItem& hotkey) const override;

private:
    /**
     * Dissects the contents of `HotkeyItem` to create the Windows `INPUT` structures
     * required for the `SendInput()` function.
     * 
     * @param hotkey Contains the native Windows key codes for the key itself and optional
     *               modifiers.
     * 
     * @return QVector<INPUT> An array-like managed Qt class that can return a pointer 
     *                        to the inner array for use in the WinAPI call.
     */
    QVector<INPUT> parseHotkey(const HotkeyItem& hotkey) const;
    
    /**
     * Helper to create an `INPUT` structure for a single key press.
     */
    INPUT createKeyPress(quint32 windowsKeyCode) const;

    /**
     * Helper to create an `INPUT` structure for a single key release.
     */
    INPUT createKeyRelease(quint32 windowsKeyCode) const;
};
