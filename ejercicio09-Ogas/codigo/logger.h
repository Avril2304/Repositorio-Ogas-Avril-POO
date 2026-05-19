#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

class Logger
{
public:
    static void registrar(const QString &mensaje);
};

#endif