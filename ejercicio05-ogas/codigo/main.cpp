#include <QApplication>
#include "login.h"

int main (int argc, char *argv[]){
    // Objeto principal requerido por toda aplicacion Qt.
    QApplication a(argc, argv);

    // Se crea y muestra la ventana de login.
    Login ventana;
    ventana.show();

    // Inicia el ciclo de eventos de la aplicacion.
    return a.exec();

}
