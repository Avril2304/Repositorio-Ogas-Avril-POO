#include <QApplication>
#include "juego.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Juego ventana;
    ventana.show();

    return a.exec();
}