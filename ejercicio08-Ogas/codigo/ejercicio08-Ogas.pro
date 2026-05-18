QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configmanager.cpp \
    editorprincipal.cpp \
    logmanager.cpp \
    main.cpp \
    login.cpp \
    modobloqueado.cpp \
    pantalla.cpp \
    validadorcpp.cpp \
    validadorjava.cpp \
    validadorpython.cpp

HEADERS += \
    configmanager.h \
    editorprincipal.h \
    login.h \
    logmanager.h \
    modobloqueado.h \
    pantalla.h \
    validadorcpp.h \
    validadorjava.h \
    validadorpython.h \
    validadorsintaxis.h

FORMS += \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
