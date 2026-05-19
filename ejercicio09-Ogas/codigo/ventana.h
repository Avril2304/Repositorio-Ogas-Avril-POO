#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>

#include "database.h"

class Pintura;

class Ventana : public QWidget
{
private:
    int idUsuario;

    Pintura *lienzo;
    Database db;

public:
    explicit Ventana(int idUser, QWidget *parent = nullptr);
};

#endif