#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Objeto principal que administra la aplicacion Qt.
    QApplication a(argc, argv);

    // Se crea y muestra el login disenado en Qt Designer.
    Login login;
    login.show();

    // Inicia el ciclo de eventos de la aplicacion.
    return QCoreApplication::exec();
}
