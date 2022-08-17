#pragma once

#include <windows.h>

#include <QSet>
#include <QDebug>
#include <QKeyEvent>
#include <QKeySequenceEdit>

#include <hotkeyitem.h>
#include <nativekeysequence.h>

/**
 * A custom implementation of `QKeySequenceEdit` for two reasons:
 * 
 * \li Restrict the input to only one hotkey sequence.
 * \li Intercept the `QWidget::keyPressEvent(QKeyEvent*)` to gain access to the 
 *     platform-native key and modifier codes.
 * 
 * Other than that, the base implementation is used.
 */
class KeyInputEdit : public QKeySequenceEdit {
    Q_OBJECT
public:
    /**
     * Construct a new KeyInputEdit object. This construcor only forwards to the base
     * class.
     */
    KeyInputEdit(QWidget* parent = nullptr)
        : QKeySequenceEdit(parent)
    {}
    
    /**
     * Access the native key codes of the hotkey keq sequence.
     */
    NativeKeySequence nativeKeySequence() const {
        return nativeSequence_;
    }
    
protected:
    /**
     * Overrides the base class version to access the `QKeyEvent` that contains 
     * platform-specific key codes.
     * 
     * This method also sets the only available key sequence to limit the total number
     * of key sequence from four to only one.
     */
    void keyPressEvent(QKeyEvent* event) {
        
        auto key = event->nativeVirtualKey();
        auto mod = event->nativeModifiers();
        nativeSequence_ = NativeKeySequence{key, convertToWinModifier(mod)};
        
        QKeySequenceEdit::keyPressEvent(event);
        
        // Enforce only a single sequence.
        auto seq = keySequence();
        if (0 != seq.count()) {
            setKeySequence(seq[0]);
        }
    }
    
private:
    NativeKeySequence nativeSequence_;
    
    /**
     * The QKeyEvent::nativeModifiers() aren't really native. They are internal enums
     * of the Qt Windows wrappers.
     * 
     * https://code.qt.io/cgit/qt/qtbase.git/tree/src/plugins/platforms/windows/qwindowskeymapper.h?h=6.1.0#n117
     */
    QSet<quint32> convertToWinModifier(int qtNativeModifier) const {
        auto winModifier = QSet<quint32>{};
        
        // ShiftAny
        if (0x00000011 & qtNativeModifier) {
            winModifier.insert(0xA0); // VK_LSHIFT;
        }
        // ControlAny
        if (0x00000022 & qtNativeModifier) {
            winModifier.insert(0xA2); // VK_LCONTROL
        }
        // AltAny
        if (0x00000088 & qtNativeModifier) {
            winModifier.insert(0x5B); // VK_LWIN
        }
        // MetaAny
        if (0x00000044 & qtNativeModifier) {
            winModifier.insert(0x12); // VK_MENU
        }
        
        return winModifier;
    }
};
