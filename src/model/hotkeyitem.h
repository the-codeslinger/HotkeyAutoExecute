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
 * This class is a data transfer object created in the UI for use in the `HotkeyExecutor`
 * class. It contains plain string for display in the UI and also identification in the
 * JSON configuration as well as the native Windows virtual key codes that are required
 * for emulating the hotkey sequnce.
 * 
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
     * The native key codes.
     */
    NativeKeySequence nativeSequence;
    
    /**
     * Construct a new HotkeyItem object. This is used when the user creates a new hotkey.
     * 
     * The native virtual key codes from `KeyInputEdit` will be merged with the user's
     * manuall selection of additional modifiers or keys and stored in
     * `HotkeyItem::nativeSequence`.
     * 
     * @param hotkeyName The user's name for the hotey sequence.
     * @param hotkeySequence Unused. Will be used to store the hotkey sequence in human
     *                       readable form
     * @param nativeHotkeySequence The native virtual key codes from `KeyInputEdit`.
     * @param modifiers The manually user-selected modifiers.
     * @param keys The manually user-selected additional keys.
     */
    HotkeyItem(
            const QString& hotkeyName,
            const QString& hotkeySequence,
            NativeKeySequence nativeHotkeySequence,
            const SpecialModifiers& modifiers,
            const SpecialKeys& keys);
    
    /**
     * Construct a new HotkeyItem object. this is used when reading from the JSON file.
     * 
     * @param hotkeyName The user's name for the hotey sequence.
     * @param hotkeySequence Unused. Will be used to store the hotkey sequence in human
     *                       readable form
     * @param nativeHotkeySequence The native virtual key codes from.
     */
    HotkeyItem(
            const QString& hotkeyName, 
            const QString& hotkeySequence,
            NativeKeySequence nativeHotkeySequence);
    
    // The following constructors and methods are required for QVariant.
    HotkeyItem() = default;
    HotkeyItem(const HotkeyItem& other) = default;
    ~HotkeyItem();
    HotkeyItem& operator=(const HotkeyItem&) = default;
    
private:
    /**
     * Combines the values of `HotkeyItem::nativeSequence` with the user selection and
     * stores the result in `HotkeyItem::nativeSequence`.
     */
    void mergeNativeSequenceAndSpecials(
            const SpecialModifiers& modifiers,
            const SpecialKeys& keys);
};
 
Q_DECLARE_METATYPE(HotkeyItem);
