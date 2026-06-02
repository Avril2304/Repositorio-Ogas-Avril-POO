#ifndef VALIDADORSINTAXIS_H
#define VALIDADORSINTAXIS_H

#include <QString>

// Contrato base para validar lineas segun el lenguaje elegido.
class ValidadorSintaxis
{
public:
    virtual ~ValidadorSintaxis() {}

    virtual bool validarLinea(const QString &linea, QString &mensajeError) = 0; // Devuelve false y mensaje si detecta error.
};

#endif // VALIDADORSINTAXIS_H
