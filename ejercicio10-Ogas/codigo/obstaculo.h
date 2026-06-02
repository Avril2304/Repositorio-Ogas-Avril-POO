#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QRect>

// Clase base para elementos que se mueven hacia el jugador.
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

    virtual void mover() = 0; // Cada obstaculo define su propia forma de avanzar.

    QRect obtenerRectangulo() const;
    virtual QRect obtenerRectanguloColision() const; // Rectangulo ajustado para colisiones.

    int getX() const;
    int getY() const;
    int getAncho() const;
    int getAlto() const;
};

#endif
