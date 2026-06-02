#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Punto de entrada: muestra el login conectado a SQLite.
    Login w;
    w.show();

    return a.exec();
}
