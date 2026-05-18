#ifndef VALIDADORSINTAXIS_H
#define VALIDADORSINTAXIS_H

#include <QString>

class ValidadorSintaxis
{
public:
    virtual ~ValidadorSintaxis() {}

    virtual bool validarLinea(const QString &linea, QString &mensajeError) = 0;
};

#endif // VALIDADORSINTAXIS_H
