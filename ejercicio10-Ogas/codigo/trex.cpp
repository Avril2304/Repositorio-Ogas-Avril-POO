#include "trex.h"

TRex::TRex()
{
    // Estado inicial del personaje sobre el suelo.
    x = 80;
    suelo = 300;

    ancho = 50;
    alto = 70;

    y = suelo - alto;

    saltando = false;
    agachado = false;

    velocidadVertical = 0;
    gravedad = 2;
}

void TRex::saltar()
{
    // Solo puede saltar si no esta ya en el aire.
    if (!saltando)
    {
        saltando = true;
        velocidadVertical = -22;
    }
}

void TRex::agacharse()
{
    // Agacharse cambia la altura y reposiciona el sprite sobre el suelo.
    if (!saltando)
    {
        agachado = true;
        alto = 40;
        y = suelo - alto;
    }
}

void TRex::levantarse()
{
    if (!saltando)
    {
        agachado = false;
        alto = 70;
        y = suelo - alto;
    }
}

void TRex::actualizar()
{
    // Aplica velocidad vertical y gravedad hasta volver al suelo.
    if (saltando)
    {
        y += velocidadVertical;
        velocidadVertical += gravedad;

        if (y >= suelo - alto)
        {
            y = suelo - alto;
            saltando = false;
            velocidadVertical = 0;
        }
    }
}

void TRex::adelantar()
{
    // Limita el avance para que el jugador no salga demasiado hacia adelante.
    x += 15;

    if (x > 250)
    {
        x = 250;
    }
}

void TRex::frenar()
{
    // Limita el retroceso para mantener al jugador dentro de la pantalla.
    x -= 15;

    if (x < 20)
    {
        x = 20;
    }
}

QRect TRex::obtenerRectangulo() const
{
    return QRect(x, y, ancho, alto);
}

int TRex::getX() const
{
    return x;
}

int TRex::getY() const
{
    return y;
}

int TRex::getAncho() const
{
    return ancho;
}

int TRex::getAlto() const
{
    return alto;
}

bool TRex::estaAgachado() const
{
    return agachado;
}

QRect TRex::obtenerRectanguloColision() const
{
    // Caja de colision un poco menor que el sprite.
    int margenIzquierdo = 5;
    int margenDerecho = 5;
    int margenArriba = 5;
    int margenAbajo = 5;

    return QRect(
        x + margenIzquierdo,
        y + margenArriba,
        ancho - margenIzquierdo - margenDerecho,
        alto - margenArriba - margenAbajo
        );
}
