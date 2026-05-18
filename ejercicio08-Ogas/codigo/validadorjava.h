#ifndef VALIDADORJAVA_H
#define VALIDADORJAVA_H

#include "validadorsintaxis.h"

class ValidadorJava : public ValidadorSintaxis
{
public:
    bool validarLinea(const QString &linea, QString &mensajeError) override;
};

#endif // VALIDADORJAVA_H