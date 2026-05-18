#ifndef VALIDADORCPP_H
#define VALIDADORCPP_H

#include "validadorsintaxis.h"

class ValidadorCpp : public ValidadorSintaxis
{
public:
    bool validarLinea(const QString &linea, QString &mensajeError) override;
};

#endif // VALIDADORCPP_H