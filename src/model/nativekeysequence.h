#pragma once

#include <Qt>
#include <QSet>

/**
 * Contains the native Windows virtual key codes for the individual key and modifiers.
 */
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
    
    /**
     * Construct a new NativeKeySequence object with all values set to zero.
     * 
     */
    NativeKeySequence() 
        : key(0)
    {}
    
    /**
     * Construct a new NativeKeySequence object with specific values. One or the other
     * can be zero or an empty set.
     */
    NativeKeySequence(quint32 k, QSet<quint32> m) 
        : key(k)
        , modifiers(m)
    {}
};
