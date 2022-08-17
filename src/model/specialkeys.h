#pragma once

#include <Qt>

/**
 * This class is a direct representation of the manually selected special keys in the 
 * `MainWindow`. The values of the radio boxes are stored in booleans that can be 
 * converted into Windows virtual key codes.
 * 
 * https://docs.microsoft.com/de-de/windows/win32/inputdev/virtual-key-codes
 */
struct SpecialKeys
{
    bool print;
    
    /**
     * Only one key can be active for a hotkey, so only one active key is returned.
     * If multiple keys are marked active, the first one found will be returned.
     */
    int code() const {
        if (print) {
            return 0x2C; // VK_SNAPSHOT
        }
        return 0x00;
    }
};
