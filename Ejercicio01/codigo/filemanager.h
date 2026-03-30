#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>
#include <QString>
#include "user.h"
#include "task.h"

class FileManager
{
public:
    FileManager();

    static QVector<User> loadUsers(const QString &filePath);
    static bool validateUser(const QString &filePath, const QString &username, const QString &password);
    static QVector<Task> loadTasks(const QString &filePath);
    static void saveTasks(const QString &filePath, const QVector<Task> &tasks);
    static void initializeFiles(const QString &basePath);
};

#endif // FILEMANAGER_H