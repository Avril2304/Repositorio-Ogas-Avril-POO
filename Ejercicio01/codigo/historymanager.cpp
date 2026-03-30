#include "historymanager.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

HistoryManager::HistoryManager()
{
}

void HistoryManager::saveLoginHistory(const QString &filePath, const QString &username)
{
    QFile file(filePath);

    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    out << username << " - " << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss")
        << " - Inicio de sesión\n";

    file.close();
}

void HistoryManager::saveAction(const QString &filePath, const QString &text)
{
    QFile file(filePath);

    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss")
        << " - " << text << "\n";

    file.close();
}

QStringList HistoryManager::loadHistory(const QString &filePath)
{
    QStringList lines;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return lines;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
        {
            lines.append(line);
        }
    }

    file.close();
    return lines;
}