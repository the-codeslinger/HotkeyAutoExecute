#pragma once

#include <QSet>

/**
 * This class is a direct representation of the manually selected modifier keys in the 
 * `MainWindow`. The values of the check boxes are stored in booleans that can be 
 * converted into Windows virtual key codes.
 * 
 * https://docs.microsoft.com/de-de/windows/win32/inputdev/virtual-key-codes
 */
struct SpecialModifiers
{
    bool shift;
    bool control;
    bool meta;
    bool alt;
    
    /**
     * Evaluate the class properties and create a `QSet` that contains the Windows
     * virtual key codes of the ones that are set to \c true.
     */
    QSet<quint32> combinedCode() const {
        auto modifiers = QSet<quint32>{};
        if (shift) {
            modifiers.insert(0xA0); // VK_LSHIFT;
        }
        if (control) {
            modifiers.insert(0xA2); // VK_LCONTROL
        }
        if (meta) {
            modifiers.insert(0x5B); // VK_LWIN
        }
        if (alt) {
            modifiers.insert(0x12); // VK_MENU
        }
        return modifiers;
    }
};
