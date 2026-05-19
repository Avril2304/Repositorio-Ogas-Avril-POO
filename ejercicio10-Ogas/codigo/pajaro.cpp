#include "pajaro.h"
#include <QRandomGenerator>

Pajaro::Pajaro(QObject *parent)
    : QObject(parent)
{
    tipo = QRandomGenerator::global()->bounded(3);

    if (tipo == 0)
    {
        ancho = 45;
        alto = 35;
    }
    else if (tipo == 1)
    {
        ancho = 55;
        alto = 30;
    }
    else
    {
        ancho = 40;
        alto = 45;
    }

    x = 800;

    int alturaAleatoria = QRandomGenerator::global()->bounded(3);

    if (alturaAleatoria == 0)
    {
        y = 180;
    }
    else if (alturaAleatoria == 1)
    {
        y = 220;
    }
    else
    {
        y = 250;
    }

    velocidad = QRandomGenerator::global()->bounded(6, 11);

    timerMovimiento = new QTimer(this);

    connect(timerMovimiento, SIGNAL(timeout()),
            this, SLOT(mover()));

    timerMovimiento->start(30);
}

Pajaro::~Pajaro()
{
    timerMovimiento->stop();
}

void Pajaro::mover()
{
    x -= velocidad;
}

void Pajaro::aumentarVelocidad()
{
    velocidad++;
}

bool Pajaro::estaFueraDePantalla() const
{
    return x + ancho < 0;
}

QRect Pajaro::obtenerRectanguloColision() const
{
    int margenX = 4;
    int margenY = 4;

    return QRect(
        x + margenX,
        y + margenY,
        ancho - margenX * 2,
        alto - margenY * 2
        );
}

int Pajaro::getTipo() const
{
    return tipo;
}