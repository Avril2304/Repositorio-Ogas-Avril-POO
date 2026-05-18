#include "validadorjava.h"

bool ValidadorJava::validarLinea(const QString &linea, QString &mensajeError)
{
    QString l = linea.trimmed();

    if (l.isEmpty()) return true;
    if (l.startsWith("import")) return true;
    if (l.startsWith("//")) return true;
    if (l.endsWith(";")) return true;
    if (l.endsWith("{")) return true;
    if (l.endsWith("}")) return true;

    mensajeError = "En Java las instrucciones suelen finalizar con punto y coma.";
    return false;
}