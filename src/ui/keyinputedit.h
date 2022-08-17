#pragma once

#include <windows.h>

#include <QSet>
#include <QDebug>
#include <QKeyEvent>
#include <QKeySequenceEdit>

#include <hotkeyitem.h>
#include <nativekeysequence.h>

class KeyInputEdit : public QKeySequenceEdit {
    Q_OBJECT
public:
    KeyInputEdit(QWidget* parent = nullptr)
        : QKeySequenceEdit(parent) {
        
    }
    
    NativeKeySequence nativeKeySequence() const {
        return nativeSequence_;
    }
    
protected:
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
