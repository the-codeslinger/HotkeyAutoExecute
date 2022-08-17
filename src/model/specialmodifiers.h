#pragma once

#include <QSet>

struct SpecialModifiers
{
    bool shift;
    bool control;
    bool meta;
    bool alt;
    
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
