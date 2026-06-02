#include "logmanager.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>

void LogManager::registrar(const QString &descripcion)
{
    // Crea la carpeta si falta y agrega una linea con fecha y descripcion.
    QDir().mkpath("datos");

    QFile archivo("datos/eventos.log");

    if (archivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream salida(&archivo);

        QString fecha = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        salida << fecha << " - " << descripcion << "\n";

        archivo.close();
    }
}
