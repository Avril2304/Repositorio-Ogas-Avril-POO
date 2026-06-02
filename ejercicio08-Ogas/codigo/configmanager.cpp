#include "configmanager.h"

#include <QFile>
#include <QTextStream>
#include <QDir>

QString ConfigManager::obtenerValor(const QString &clave, const QString &valorPorDefecto)
{
    // Asegura que exista el archivo con valores iniciales antes de leerlo.
    QDir().mkpath("datos");

    QFile archivo("datos/config.txt");

    if (!archivo.exists()) {
        if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream salida(&archivo);

            salida << "usuario=admin\n";
            salida << "password=1234\n";
            salida << "tiempo_bloqueo=10\n";
            salida << "lenguaje_defecto=C++\n";
            salida << "ruta_exportacion=codigo_exportado.jpg\n";

            archivo.close();
        }
    }

    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream entrada(&archivo);

        while (!entrada.atEnd()) {
            // Ignora comentarios y lineas vacias para permitir configuraciones simples.
            QString linea = entrada.readLine().trimmed();

            if (linea.startsWith("#") || linea.isEmpty()) {
                continue;
            }

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
    }

    return valorPorDefecto;
}
