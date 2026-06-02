#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Punto de entrada: inicia el login con clima, hora y descarga de recursos.
    login w;
    w.show();
    return QCoreApplication::exec();
}
