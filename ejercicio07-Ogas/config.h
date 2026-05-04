#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

class Config
{
public:
    static QString obtenerValor(QString clave);
};

#endif