QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/model/hotkeyitem.cpp \
    src/util/hotkeyconfigreader.cpp \
    src/util/hotkeyconfigwriter.cpp \
    src/util/hotkeyexecutor.cpp \
    src/ui/mainwindow.cpp

HEADERS += \
    src/model/nativekeysequence.h \
    src/model/specialkeys.h \
    src/model/specialmodifiers.h \
    src/system/qtwindowskeymapping.h \
    src/ui/keyinputedit.h \
    src/util/hotkeyconfigreader.h \
    src/util/hotkeyconfigwriter.h \
    src/util/hotkeyexecutor.h \
    src/model/hotkeyitem.h \
    src/ui/mainwindow.h

INCLUDEPATH += \
    src/util \
    src/model \
    src/ui \
    src/system

FORMS += \
    ui/mainwindow.ui

TRANSLATIONS += \
    i18n/en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/icons.qrc
