#include "logger.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>

void Logger::registrar(QString descripcion)
{
    // Crea la carpeta de datos si no existe y agrega el evento al final del log.
    QDir().mkpath("datos");

    QFile archivo("datos/eventos.log");

    if (archivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream salida(&archivo);

        salida << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss")
               << " - "
               << descripcion
               << "\n";

        archivo.close();
    }
}
