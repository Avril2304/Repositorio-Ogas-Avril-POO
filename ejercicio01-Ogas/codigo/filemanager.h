#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>
#include <QString>
#include "user.h"
#include "task.h"

/*
 * Clase: FileManager
 * ----------------------------
 * Gestiona la lectura y escritura de archivos utilizados por la aplicación.
 *
 * Permite cargar usuarios, validar credenciales, guardar tareas y crear los archivos necesarios
 * para el funcionamiento del sistema.
 */
class FileManager
{
public:

    //Constructor por defecto.
    FileManager();

    //Carga todos los usuarios almacenados en el archivo indicado.
    static QVector<User> loadUsers(const QString &filePath);

    // Verifica si las credenciales ingresadas corresponden a un usuario válido.
    static bool validateUser(const QString &filePath,
                             const QString &username,
                             const QString &password);

    //Carga todas las tareas almacenadas en el archivo de persistencia.
    static QVector<Task> loadTasks(const QString &filePath);

    //Guarda todas las tareas en el archivo de persistencia.
    static void saveTasks(const QString &filePath,
                          const QVector<Task> &tasks);

    //Crea los archivos iniciales del sistema en caso de que no existan.
    static void initializeFiles(const QString &basePath);
};

#endif // FILEMANAGER_H