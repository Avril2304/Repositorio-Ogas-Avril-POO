#include "obstaculo.h"

QRect Obstaculo::obtenerRectangulo() const
{
    return QRect(x, y, ancho, alto);
}

int Obstaculo::getX() const
{
    return x;
}

int Obstaculo::getY() const
{
    return y;
}

int Obstaculo::getAncho() const
{
    return ancho;
}

int Obstaculo::getAlto() const
{
    return alto;
}

QRect Obstaculo::obtenerRectanguloColision() const
{
    int margenX = 2;
    int margenY = 2;

    return QRect(
        x + margenX,
        y + margenY,
        ancho - margenX * 2,
        alto - margenY * 2
        );
}