QT += core gui widgets sql

CONFIG += c++17

SOURCES += \
    database.cpp \
    logger.cpp \
    main.cpp \
    login.cpp \
    pintura.cpp \
    ventana.cpp \

HEADERS += \
    database.h \
    logger.h \
    login.h \
    pintura.h \
    ventana.h \

FORMS += \
    login.ui