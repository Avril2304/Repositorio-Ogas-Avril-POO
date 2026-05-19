#ifndef TREX_H
#define TREX_H

#include <QRect>

class TRex
{
private:
    int x;
    int y;
    int ancho;
    int alto;

    bool saltando;
    bool agachado;

    int velocidadVertical;
    int gravedad;
    int suelo;

public:
    TRex();

    void saltar();
    void agacharse();
    void levantarse();
    void actualizar();

    void adelantar();
    void frenar();

    QRect obtenerRectangulo() const;
    QRect obtenerRectanguloColision() const;

    int getX() const;
    int getY() const;
    int getAncho() const;
    int getAlto() const;

    bool estaAgachado() const;
};

#endif