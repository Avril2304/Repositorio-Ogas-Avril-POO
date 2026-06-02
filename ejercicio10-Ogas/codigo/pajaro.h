#ifndef PAJARO_H
#define PAJARO_H

#include <QObject>
#include <QTimer>

#include "obstaculo.h"

// Obstaculo aereo con tipo, altura y velocidad aleatorios.
class Pajaro : public QObject, public Obstaculo
{
    Q_OBJECT

private:
    // Timer propio para mover el pajaro sin depender directamente del cactus.
    QTimer *timerMovimiento;
    int tipo;

public:
    explicit Pajaro(QObject *parent = nullptr);
    ~Pajaro();

    void aumentarVelocidad();
    bool estaFueraDePantalla() const;
    QRect obtenerRectanguloColision() const override;
    int getTipo() const;

public slots:
    void mover() override;
};

#endif
