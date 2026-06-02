#include "filemanager.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

/*
 * Constructor por defecto.
 */
FileManager::FileManager()
{
}

/*
 * Carga los usuarios registrados desde un archivo CSV.
 *
 * Cada línea del archivo debe tener el formato:
 * usuario,contraseña
 *
 * Retorna:
 * un QVector<User> con todos los usuarios cargados.
 */
QVector<User> FileManager::loadUsers(const QString &filePath)
{
    // Vector donde se almacenarán los usuarios cargados
    QVector<User> users;

    // Crear objeto asociado al archivo de usuarios
    QFile file(filePath);

    // Intentar abrir el archivo en modo lectura
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return users;
    }

    QTextStream in(&file);

    // Leer el archivo línea por línea
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        // Ignorar líneas vacías
        if (line.isEmpty())
        {
            continue;
        }

        // Separar usuario y contraseña
        QStringList parts = line.split(",");

        // Validar que la línea tenga el formato correcto
        if (parts.size() == 2)
        {
            // Crear usuario y agregarlo al vector
            users.append(User(parts[0].trimmed(), parts[1].trimmed()));
        }
    }

    // Cerrar archivo
    file.close();

    // Retornar usuarios cargados
    return users;
}

/*
 * Verifica si las credenciales ingresadas coinciden con algún usuario registrado.
 *
 * Retorna:
 * true  -> usuario y contraseña correctos.
 * false -> usuario inexistente o contraseña incorrecta.
 */
bool FileManager::validateUser(const QString &filePath, const QString &username, const QString &password)
{
    // Cargar usuarios registrados
    QVector<User> users = loadUsers(filePath);

    // Recorrer todos los usuarios cargados
    for (int i = 0; i < users.size(); i++)
    {
        // Comparar usuario y contraseña
        if (users[i].getUsername() == username && users[i].getPassword() == password)
        {
            return true;
        }
    }

    // No se encontró coincidencia
    return false;
}

/*
 * Carga todas las tareas almacenadas desde un archivo CSV.
 *
 * Cada línea del archivo debe tener el formato:
 * id,titulo,materia,fechaEntrega,estado,prioridad
 *
 * Retorna: un QVector<Task> con todas las tareas cargadas.
 */
QVector<Task> FileManager::loadTasks(const QString &filePath)
{
    // Vector donde se almacenarán las tareas cargadas
    QVector<Task> tasks;

    // Crear objeto asociado al archivo de tareas
    QFile file(filePath);

    // Intentar abrir el archivo en modo lectura
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return tasks;
    }

    QTextStream in(&file);

    // Leer el archivo línea por línea
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        // Ignorar líneas vacías
        if (line.isEmpty())
        {
            continue;
        }

        // Separar los campos de la tarea
        QStringList parts = line.split(",");

        // Validar que la línea tenga todos los campos esperados
        if (parts.size() == 6)
        {
            // Obtener datos individuales de la tarea
            int id = parts[0].trimmed().toInt();
            QString titulo = parts[1].trimmed();
            QString materia = parts[2].trimmed();
            QString fechaEntrega = parts[3].trimmed();
            QString estado = parts[4].trimmed();
            QString prioridad = parts[5].trimmed();

            // Crear objeto Task y agregarlo al vector
            tasks.append(Task(id, titulo, materia, fechaEntrega, estado, prioridad));
        }
    }

    // Cerrar archivo
    file.close();

    // Retornar tareas cargadas
    return tasks;
}

/*
 * Guarda todas las tareas en un archivo CSV.
 *
 * Sobrescribe el contenido anterior del archivo
 * para dejar registrada la lista actualizada.
 */
void FileManager::saveTasks(const QString &filePath, const QVector<Task> &tasks)
{
    // Crear objeto asociado al archivo de tareas
    QFile file(filePath);

    // Intentar abrir el archivo en modo escritura
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);

    // Recorrer todas las tareas
    for (int i = 0; i < tasks.size(); i++)
    {
        // Escribir datos de la tarea en formato CSV
        out << tasks[i].getId() << ","
            << tasks[i].getTitulo() << ","
            << tasks[i].getMateria() << ","
            << tasks[i].getFechaEntrega() << ","
            << tasks[i].getEstado() << ","
            << tasks[i].getPrioridad() << "\n";
    }

    // Cerrar archivo
    file.close();
}

/*
 * Inicializa los archivos necesarios para el sistema.
 *
 * Si los archivos no existen, los crea automáticamente con datos iniciales o vacíos según corresponda.
 */
void FileManager::initializeFiles(const QString &basePath)
{
    // Construir rutas de archivos del sistema
    QString usersPath = basePath + "/users.csv";
    QString tasksPath = basePath + "/tasks.csv";
    QString sessionPath = basePath + "/session.txt";
    QString historyPath = basePath + "/history.txt";

    // Crear archivo de usuarios por defecto si no existe
    if (!QFile::exists(usersPath))
    {
        QFile file(usersPath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);

            // Usuarios iniciales de prueba
            out << "admin,1234\n";
            out << "avril,abcd\n";

            file.close();
        }
    }

    // Crear archivo de tareas iniciales si no existe
    if (!QFile::exists(tasksPath))
    {
        QFile file(tasksPath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);

            // Tareas de ejemplo para iniciar el sistema
            out << "1,TP Matemática,Análisis II,2026-03-30,Pendiente,Alta\n";
            out << "2,TP Base de Datos,Laboratorio I,2026-04-05,En progreso,Media\n";

            file.close();
        }
    }

    // Crear archivo de sesión vacío si no existe
    if (!QFile::exists(sessionPath))
    {
        QFile file(sessionPath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.close();
        }
    }

    // Crear archivo de historial vacío si no existe
    if (!QFile::exists(historyPath))
    {
        QFile file(historyPath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.close();
        }
    }
}