#include "ventana.h"
#include "pintura.h"

#include <QVBoxLayout>
#include <QLabel>

Ventana::Ventana(int idUser, QWidget *parent)
    : QWidget(parent)
{
    idUsuario = idUser;

    db.conectar();

    resize(1000, 700);
    setWindowTitle("Ejercicio 09 - Coordenadas en base de datos");

    QLabel *instrucciones = new QLabel(
        "Mouse: dibujar | R: rojo | G: verde | B: azul | Rueda: grosor | Ctrl+Z: deshacer | Esc: borrar"
        );

    instrucciones->setStyleSheet(
        "background-color: #222;"
        "color: white;"
        "padding: 10px;"
        "font-size: 14px;"
        );

    lienzo = new Pintura(idUsuario, &db);
    lienzo->cargarDesdeBase();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(instrucciones);
    layout->addWidget(lienzo);

    setLayout(layout);
}