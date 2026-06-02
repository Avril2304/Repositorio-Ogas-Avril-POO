#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // Punto de entrada: crea y muestra el tablero Kanban.
    MainWindow w;
    w.show();
    return a.exec();
}
