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
    nativeSequence.modifiers.unite(modifiers.combinedCode());
    nativeSequence.key |= keys.code();
}
