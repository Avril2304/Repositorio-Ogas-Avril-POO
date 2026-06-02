#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

// Lector simple de valores guardados como clave=valor.
class Config
{
public:
    static QString obtenerValor(QString clave);
};

#endif
