#pragma once

#include <QSet>

#include <keycodes.h>

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
    QSet<quint32> codes() const {
        auto modifiers = QSet<quint32>{};
        if (shift) {
            modifiers.insert(LEFT_SHIFT_KEY);
        }
        if (control) {
            modifiers.insert(LEFT_CONTROL_KEY);
        }
        if (meta) {
            modifiers.insert(LEFT_META_KEY);
        }
        if (alt) {
            modifiers.insert(ALT_KEY);
        }
        return modifiers;
    }
};
