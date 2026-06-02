#ifndef TREX_H
#define TREX_H

#include <QRect>

// Personaje principal controlado por teclado.
class TRex
{
private:
    int x;
    int y;
    int ancho;
    int alto;

    bool saltando;
    bool agachado;

    // Variables simples de fisica para el salto.
    int velocidadVertical;
    int gravedad;
    int suelo;

public:
    TRex();

    void saltar();      // Inicia el salto si esta en el suelo.
    void agacharse();   // Reduce la altura para esquivar obstaculos altos.
    void levantarse();  // Restaura la altura normal.
    void actualizar();  // Aplica gravedad y movimiento vertical.

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
