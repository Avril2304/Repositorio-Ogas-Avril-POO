#ifndef VALIDADORPYTHON_H
#define VALIDADORPYTHON_H

#include "validadorsintaxis.h"

// Validador basico de reglas frecuentes de Python.
class ValidadorPython : public ValidadorSintaxis
{
public:
    bool validarLinea(const QString &linea, QString &mensajeError) override;
};

#endif // VALIDADORPYTHON_H
