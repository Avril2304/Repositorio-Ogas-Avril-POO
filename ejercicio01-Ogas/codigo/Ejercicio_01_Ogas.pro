# Módulo de Qt necesario para construir ventanas y controles gráficos.
QT += widgets

# Se compila el proyecto usando C++17.
CONFIG += c++17

# Opción útil para detectar APIs obsoletas de Qt.
# Para activarla, descomentar la siguiente línea.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Archivos fuente que forman parte de la aplicación.
SOURCES += \
    filemanager.cpp \
    historymanager.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwidget.cpp \
    noteswidget.cpp \
    sessionmanager.cpp \
    task.cpp \
    taskformwidget.cpp \
    user.cpp

# Archivos de cabecera con las declaraciones de clases.
HEADERS += \
    filemanager.h \
    historymanager.h \
    loginwidget.h \
    mainwidget.h \
    noteswidget.h \
    sessionmanager.h \
    task.h \
    taskformwidget.h \
    user.h

# Configuración de traducciones generada por Qt Creator.
CONFIG += lrelease
CONFIG += embed_translations

# Reglas de instalación/despliegue generadas por Qt Creator.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
