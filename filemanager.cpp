#include "filemanager.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

FileManager::FileManager()
{
}

QVector<User> FileManager::loadUsers(const QString &filePath)
{
    QVector<User> users;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return users;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.isEmpty())
        {
            continue;
        }

        QStringList parts = line.split(",");

        if (parts.size() == 2)
        {
            users.append(User(parts[0].trimmed(), parts[1].trimmed()));
        }
    }

    file.close();
    return users;
}

bool FileManager::validateUser(const QString &filePath, const QString &username, const QString &password)
{
    QVector<User> users = loadUsers(filePath);

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getUsername() == username && users[i].getPassword() == password)
        {
            return true;
        }
    }

    return false;
}

QVector<Task> FileManager::loadTasks(const QString &filePath)
{
    QVector<Task> tasks;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return tasks;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.isEmpty())
        {
            continue;
        }

        QStringList parts = line.split(",");

        if (parts.size() == 6)
        {
            int id = parts[0].trimmed().toInt();
            QString titulo = parts[1].trimmed();
            QString materia = parts[2].trimmed();
            QString fechaEntrega = parts[3].trimmed();
            QString estado = parts[4].trimmed();
            QString prioridad = parts[5].trimmed();

            tasks.append(Task(id, titulo, materia, fechaEntrega, estado, prioridad));
        }
    }

    file.close();
    return tasks;
}

void FileManager::saveTasks(const QString &filePath, const QVector<Task> &tasks)
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < tasks.size(); i++)
    {
        out << tasks[i].getId() << ","
            << tasks[i].getTitulo() << ","
            << tasks[i].getMateria() << ","
            << tasks[i].getFechaEntrega() << ","
            << tasks[i].getEstado() << ","
            << tasks[i].getPrioridad() << "\n";
    }

    file.close();
}

void FileManager::initializeFiles(const QString &basePath)
{
    QString usersPath = basePath + "/users.csv";
    QString tasksPath = basePath + "/tasks.csv";
    QString sessionPath = basePath + "/session.txt";
    QString historyPath = basePath + "/history.txt";

    if (!QFile::exists(usersPath))
    {
        QFile file(usersPath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << "admin,1234\n";
            out << "avril,abcd\n";
            file.close();
        }
    }

    if (!QFile::exists(tasksPath))
    {
        QFile file(tasksPath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << "1,TP Matemática,Análisis II,2026-03-30,Pendiente,Alta\n";
            out << "2,TP Base de Datos,Laboratorio I,2026-04-05,En progreso,Media\n";
            file.close();
        }
    }

    if (!QFile::exists(sessionPath))
    {
        QFile file(sessionPath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.close();
        }
    }

    if (!QFile::exists(historyPath))
    {
        QFile file(historyPath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.close();
        }
    }
}