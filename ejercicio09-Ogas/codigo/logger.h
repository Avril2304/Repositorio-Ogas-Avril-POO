#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

// Logger de accesos exitosos y fallidos.
class Logger
{
public:
    static void registrar(const QString &mensaje);
};

#endif
