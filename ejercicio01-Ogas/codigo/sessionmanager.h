#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QString>

/*
 * Clase: SessionManager
 * ----------------------------
 * Gestiona la persistencia de la sesión del usuario.
 * Permite guardar, verificar y eliminar la sesión para evitar solicitar login repetidamente.
 */
class SessionManager
{
public:
    // Constructor por defecto
    SessionManager();

    // Guarda la sesión del usuario en un archivo local
    static void saveSession(const QString &filePath, const QString &username);

    // Devuelve el usuario de la sesión activa
    static QString getActiveSession(const QString &filePath);

    // Verifica si existe una sesión activa y válida
    static bool hasActiveSession(const QString &filePath);

    // Elimina la sesión guardada
    static void clearSession(const QString &filePath);
};

#endif // SESSIONMANAGER_H