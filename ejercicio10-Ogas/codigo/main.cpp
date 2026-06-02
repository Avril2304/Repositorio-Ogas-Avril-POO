#include <QApplication>
#include "juego.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Punto de entrada: crea la ventana del juego.
    Juego ventana;
    ventana.show();

    return a.exec();
}
