#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>

// Lee configuraciones del editor desde datos/config.txt.
class ConfigManager
{
public:
    static QString obtenerValor(const QString &clave, const QString &valorPorDefecto);
};

#endif // CONFIGMANAGER_H
