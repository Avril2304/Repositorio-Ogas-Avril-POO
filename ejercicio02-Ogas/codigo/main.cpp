#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // QApplication administra el ciclo de vida de la aplicacion Qt.
    QApplication a(argc, argv);

    // Se crea y muestra la ventana principal del panel de monitoreo.
    MainWindow w;
    w.show();

    // exec() inicia el loop de eventos: clicks, timers, respuestas de red, etc.
    return a.exec();
}
