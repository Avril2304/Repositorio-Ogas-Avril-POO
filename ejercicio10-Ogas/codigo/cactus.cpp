#include "cactus.h"

Cactus::Cactus()
{
    // Posicion inicial del cactus sobre el suelo.
    ancho = 35;
    alto = 60;

    x = 800;
    y = 300 - alto;

    velocidad = 8;
}

void Cactus::mover()
{
    // Avanza hacia la izquierda y vuelve al inicio cuando sale de pantalla.
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
    // La velocidad aumenta con el nivel del juego.
    velocidad++;
}

int Cactus::getVelocidad() const
{
    return velocidad;
}
