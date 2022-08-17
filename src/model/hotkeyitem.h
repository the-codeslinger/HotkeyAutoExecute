#pragma once

#include <QSet>
#include <QString>
#include <QMetaType>
#include <QKeySequence>
#include <QSetIterator>

#include <specialmodifiers.h>
#include <specialkeys.h>
#include <nativekeysequence.h>

/**
 * Copy-constructor and destructor are required for compatibility with QVariant.
 * 
 * https://doc.qt.io/qt-6/qtcore-tools-customtype-example.html
 */
struct HotkeyItem
{
    /**
     * A user-provided unique name of the hotkey, e.g., Xbox Game Bar Screenshots.
     */
    QString name;
    
    /**
     * A combination of the user's input into the edit field and the special key 
     * selections. Only used for display.
     */
    QString sequenceText;
    
    /**
     * The native key code.
     */
    NativeKeySequence nativeSequence;
    
    HotkeyItem(
            const QString& hotkeyName,
            const QString& hotkeySequence,
            NativeKeySequence nativeHotkeySequence,
            const SpecialModifiers& modifiers,
            const SpecialKeys& keys);
    
    HotkeyItem(
            const QString& hotkeyName, 
            const QString& hotkeySequence,
            NativeKeySequence nativeHotkeySequence);
    
    // Both constructors are required for QVariant. Use the "big" one for initialization.
    HotkeyItem() = default;
    HotkeyItem(const HotkeyItem& other) = default;
    
    ~HotkeyItem();
   
    HotkeyItem& operator=(const HotkeyItem&) = default;
    
private:
    void mergeNativeSequenceAndSpecials(
            const SpecialModifiers& modifiers,
            const SpecialKeys& keys);
};
 
Q_DECLARE_METATYPE(HotkeyItem);
