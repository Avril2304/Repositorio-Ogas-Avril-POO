#include "validadorpython.h"

bool ValidadorPython::validarLinea(const QString &linea, QString &mensajeError)
{
    QString l = linea.trimmed();

    if (l.isEmpty()) return true;
    if (l.startsWith("#")) return true;
    if (l.endsWith(":")) return true;
    if (!l.endsWith(";")) return true;

    mensajeError = "En Python normalmente no se usa punto y coma al final.";
    return false;
}