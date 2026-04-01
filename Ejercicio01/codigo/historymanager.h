#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QString>
#include <QStringList>

class HistoryManager
{
public:
    HistoryManager();

    static void saveLoginHistory(const QString &filePath, const QString &username);
    static void saveAction(const QString &filePath, const QString &text);
    static QStringList loadHistory(const QString &filePath);
};

#endif // HISTORYMANAGER_H