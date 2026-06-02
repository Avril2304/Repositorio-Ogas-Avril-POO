#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>

#include "database.h"

class Pintura;

// Contenedor principal del lienzo de dibujo.
class Ventana : public QWidget
{
private:
    int idUsuario;

    // Lienzo asociado al usuario actual.
    Pintura *lienzo;
    Database db;

public:
    explicit Ventana(int idUser, QWidget *parent = nullptr);
};

#endif
