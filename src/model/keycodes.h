#pragma once

#ifdef Q_OS_WIN

#define UNDEFINED_KEY    0x00 // No valid key
#define SNAPSHOT_KEY     0x2C // VK_SNAPSHOT
#define LEFT_SHIFT_KEY   0xA0 // VK_LSHIFT
#define LEFT_CONTROL_KEY 0xA2 // VK_LCONTROL
#define LEFT_META_KEY    0x5B // VK_LWIN
#define ALT_KEY          0x12 // VK_MENU

#else

// Empty defines for compilation on non-Windows platforms.

#define UNDEFINED_KEY    0x00 // No valid key
#define SNAPSHOT_KEY     UNDEFINED_KEY
#define LEFT_SHIFT_KEY   UNDEFINED_KEY
#define LEFT_CONTROL_KEY UNDEFINED_KEY
#define LEFT_META_KEY    UNDEFINED_KEY
#define ALT_KEY          UNDEFINED_KEY

#endif
