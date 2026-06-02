#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

// Guarda eventos importantes en un archivo de log.
class Logger
{
public:
    static void registrar(QString descripcion);
};

#endif
