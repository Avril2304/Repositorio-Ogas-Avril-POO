#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>

class ConfigManager
{
public:
    static QString obtenerValor(const QString &clave, const QString &valorPorDefecto);
};

#endif // CONFIGMANAGER_H