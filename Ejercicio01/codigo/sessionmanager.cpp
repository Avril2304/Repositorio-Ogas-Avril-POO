#include "sessionmanager.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

SessionManager::SessionManager()
{
}

void SessionManager::saveSession(const QString &filePath, const QString &username)
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);

    // Guardamos usuario + fecha/hora actual
    out << username << "," << QDateTime::currentDateTime().toString(Qt::ISODate);

    file.close();
}

QString SessionManager::getActiveSession(const QString &filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return "";
    }

    QTextStream in(&file);
    QString line = in.readLine().trimmed();

    file.close();

    if (line.isEmpty())
        return "";

    QStringList parts = line.split(",");

    if (parts.size() != 2)
        return "";

    QString username = parts[0].trimmed();
    QString dateTimeStr = parts[1].trimmed();

    QDateTime savedTime = QDateTime::fromString(dateTimeStr, Qt::ISODate);

    if (!savedTime.isValid())
        return "";

    // 5 minutos = 300 segundos
    int elapsedSeconds = savedTime.secsTo(QDateTime::currentDateTime());

    if (elapsedSeconds <= 300)
    {
        return username;
    }

    // Si venció la sesión, la limpiamos
    clearSession(filePath);
    return "";
}

bool SessionManager::hasActiveSession(const QString &filePath)
{
    return !getActiveSession(filePath).isEmpty();
}

void SessionManager::clearSession(const QString &filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    file.close();
}