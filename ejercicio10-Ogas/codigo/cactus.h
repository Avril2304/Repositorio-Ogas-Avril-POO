#ifndef CACTUS_H
#define CACTUS_H

#include "obstaculo.h"

class Cactus : public Obstaculo
{
public:
    Cactus();

    void mover() override;
    void reiniciar();
    void aumentarVelocidad();

    int getVelocidad() const;
};

#endif