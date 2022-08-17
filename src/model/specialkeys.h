#pragma once

#include <Qt>

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
