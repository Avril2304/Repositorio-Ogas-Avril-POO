#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QString>

class SessionManager
{
public:
    SessionManager();

    static void saveSession(const QString &filePath, const QString &username);
    static QString getActiveSession(const QString &filePath);
    static bool hasActiveSession(const QString &filePath);
    static void clearSession(const QString &filePath);
};

#endif // SESSIONMANAGER_H