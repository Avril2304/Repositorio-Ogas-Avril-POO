#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Punto de entrada: abre el login creado con Qt Designer.
    login w;
    w.show();
    return QCoreApplication::exec();
}
