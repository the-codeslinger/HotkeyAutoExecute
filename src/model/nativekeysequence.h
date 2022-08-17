#pragma once

#include <Qt>
#include <QSet>

struct NativeKeySequence
{
    /**
     * The native key code.
     */
    quint32 key;
    
    /**
     * A list of the native modifier keys.
     */
    QSet<quint32> modifiers;
    
    NativeKeySequence() 
        : key(0)
    {}
    
    NativeKeySequence(quint32 k, QSet<quint32> m) 
        : key(k)
        , modifiers(m)
    {}
};
