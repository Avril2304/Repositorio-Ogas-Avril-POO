#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Punto de entrada: abre el login del editor multilenguaje.
    Login w;
    w.show();

    return a.exec();
}
