#ifndef VALIDADORCPP_H
#define VALIDADORCPP_H

#include "validadorsintaxis.h"

// Validador basico de reglas frecuentes de C++.
class ValidadorCpp : public ValidadorSintaxis
{
public:
    bool validarLinea(const QString &linea, QString &mensajeError) override;
};

#endif // VALIDADORCPP_H
