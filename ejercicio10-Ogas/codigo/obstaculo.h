#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QRect>

class Obstaculo
{
protected:
    int x;
    int y;
    int ancho;
    int alto;
    int velocidad;

public:
    virtual ~Obstaculo() {}

    virtual void mover() = 0;

    QRect obtenerRectangulo() const;
    virtual QRect obtenerRectanguloColision() const;

    int getX() const;
    int getY() const;
    int getAncho() const;
    int getAlto() const;
};

#endif
