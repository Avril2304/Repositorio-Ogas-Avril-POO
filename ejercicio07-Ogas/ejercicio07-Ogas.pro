QT += widgets network #network: Permite usar todo lo relacionado a internet


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clima.cpp \
    config.cpp \
    logger.cpp \
    main.cpp \
    login.cpp \
    ventana.cpp

HEADERS += \
    clima.h \
    config.h \
    logger.h \
    login.h \
    pantalla.h \
    ventana.h

FORMS += \
    login.ui \
    ventana.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
