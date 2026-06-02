#ifndef PANTALLA_H
#define PANTALLA_H

#include <QWidget>

// Clase base para pantallas del ejercicio 07.
class Pantalla : public QWidget
{
    Q_OBJECT

public:
    explicit Pantalla(QWidget *parent = nullptr)
        : QWidget(parent)
    {
    }

    virtual void inicializarPantalla() = 0; // Prepara controles y datos visibles.
    virtual void limpiarPantalla() = 0;     // Restaura los campos de la pantalla.
};

#endif // PANTALLA_H
