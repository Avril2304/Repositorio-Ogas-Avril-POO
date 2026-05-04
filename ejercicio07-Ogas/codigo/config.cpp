#include "config.h"

#include <QFile>
#include <QTextStream>

QString Config::obtenerValor(QString clave)
{
    QFile archivo("datos/config.txt");

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }

    QTextStream entrada(&archivo);

    while (!entrada.atEnd()) {
        QString linea = entrada.readLine();

        QStringList partes = linea.split("=");

        if (partes.size() == 2) {
            QString claveArchivo = partes[0].trimmed();
            QString valorArchivo = partes[1].trimmed();

            if (claveArchivo == clave) {
                archivo.close();
                return valorArchivo;
            }
        }
    }

    archivo.close();
    return "";
}