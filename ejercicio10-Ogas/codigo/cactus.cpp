#include "cactus.h"

Cactus::Cactus()
{
    ancho = 35;
    alto = 60;

    x = 800;
    y = 300 - alto;

    velocidad = 8;
}

void Cactus::mover()
{
    x -= velocidad;

    if (x + ancho < 0)
    {
        reiniciar();
    }
}

void Cactus::reiniciar()
{
    x = 800;
}

void Cactus::aumentarVelocidad()
{
    velocidad++;
}

int Cactus::getVelocidad() const
{
    return velocidad;
}