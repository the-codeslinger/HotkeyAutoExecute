#include <hotkeyitem.h>

HotkeyItem::HotkeyItem(
        const QString& hotkeyName,
        const QString& hotkeySequence,
        NativeKeySequence nativeHotkeySequence,
        const SpecialModifiers& modifiers,
        const SpecialKeys& keys)
    : name(hotkeyName)
    , sequenceText(hotkeySequence)
    , nativeSequence(nativeHotkeySequence)
{
    mergeNativeSequenceAndSpecials(modifiers, keys);
}

HotkeyItem::HotkeyItem(
        const QString& hotkeyName, 
        const QString& hotkeySequence,
        NativeKeySequence nativeHotkeySequence)
    : name(hotkeyName)
    , sequenceText(hotkeySequence)
    , nativeSequence(nativeHotkeySequence)
{}

HotkeyItem::~HotkeyItem()
{}

void
HotkeyItem::mergeNativeSequenceAndSpecials(
        const SpecialModifiers& modifiers,
        const SpecialKeys& keys) 
{
    // Duplicates will be filtered by the QSet.
    nativeSequence.modifiers.unite(modifiers.combinedCode());
    // Only one key can be active. This is enforced by the UI. OR-ing both
    // values delivers either the "normal" key or the "special" one.
    nativeSequence.key |= keys.code();
}
