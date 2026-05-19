#ifndef PAJARO_H
#define PAJARO_H

#include <QObject>
#include <QTimer>

#include "obstaculo.h"

class Pajaro : public QObject, public Obstaculo
{
    Q_OBJECT

private:
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