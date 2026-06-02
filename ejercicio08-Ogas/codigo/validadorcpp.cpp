#include "validadorcpp.h"

bool ValidadorCpp::validarLinea(const QString &linea, QString &mensajeError)
{
    // Se validan reglas simples: lineas vacias, includes, comentarios y cierres validos.
    QString l = linea.trimmed();

    if (l.isEmpty()) return true;
    if (l.startsWith("#include")) return true;
    if (l.startsWith("//")) return true;
    if (l.endsWith(";")) return true;
    if (l.endsWith("{")) return true;
    if (l.endsWith("}")) return true;

    mensajeError = "En C++ muchas instrucciones deben terminar con punto y coma.";
    return false;
}
