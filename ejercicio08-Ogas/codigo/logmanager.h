#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QString>

// Utilidad compartida para registrar eventos del ejercicio.
class LogManager
{
public:
    static void registrar(const QString &descripcion);
};

#endif // LOGMANAGER_H
