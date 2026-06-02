#include "logger.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>

void Logger::registrar(const QString &mensaje)
{
    // Guarda cada acceso con fecha y hora en logs/accesos.log.
    QDir().mkpath("logs");

    QFile archivo("logs/accesos.log");

    if (archivo.open(QIODevice::Append | QIODevice::Text)) {

        QTextStream out(&archivo);

        QString fecha = QDateTime::currentDateTime()
                            .toString("yyyy-MM-dd HH:mm:ss");

        out << "[" << fecha << "] "
            << mensaje << "\n";

        archivo.close();
    }
}
