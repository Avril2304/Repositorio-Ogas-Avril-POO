#include "logger.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>

void Logger::registrar(QString descripcion)
{
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