#include "sessionmanager.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

/*
 * Constructor por defecto.
 */
SessionManager::SessionManager()
{
}

/*
 * Guarda los datos de la sesión actual en un archivo local para permitir recordar el usuario autenticado.
 *
 * Parámetros:
 * filePath : ruta del archivo de sesión.
 * username : nombre del usuario autenticado.
 */
void SessionManager::saveSession(const QString &filePath, const QString &username)
{
    // Crear objeto asociado al archivo de sesión
    QFile file(filePath);

    // Intentar abrir el archivo en modo escritura
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);

    // Guardar usuario y fecha/hora actual
    out << username << "," << QDateTime::currentDateTime().toString(Qt::ISODate);

    // Cerrar archivo
    file.close();
}

/*
 * Obtiene el usuario almacenado en la sesión activa.
 *
 * Además verifica que la sesión no haya expirado.
 *
 * Retorna:
 * - Nombre de usuario si la sesión es válida.
 * - Cadena vacía si la sesión no existe o expiró.
 */
QString SessionManager::getActiveSession(const QString &filePath)
{
    // Crear objeto asociado al archivo de sesión
    QFile file(filePath);

    // Intentar abrir el archivo en modo lectura
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return "";
    }

    QTextStream in(&file);

    // Leer la línea almacenada en el archivo
    QString line = in.readLine().trimmed();

    // Cerrar archivo
    file.close();

    // Verificar que exista información
    if (line.isEmpty())
        return "";

    // Separar usuario y fecha guardada
    QStringList parts = line.split(",");

    // Validar formato esperado
    if (parts.size() != 2)
        return "";

    // Recuperar usuario y fecha de inicio de sesión
    QString username = parts[0].trimmed();
    QString dateTimeStr = parts[1].trimmed();

    // Convertir la fecha almacenada a QDateTime
    QDateTime savedTime = QDateTime::fromString(dateTimeStr, Qt::ISODate);

    // Verificar que la fecha sea válida
    if (!savedTime.isValid())
        return "";

    // Calcular tiempo transcurrido desde el inicio de sesión
    int elapsedSeconds = savedTime.secsTo(QDateTime::currentDateTime());

    // 5 minutos = 300 segundos
    if (elapsedSeconds <= 300)
    {
        return username;
    }

    // Si la sesión venció, eliminarla
    clearSession(filePath);

    return "";
}

/*
 * Verifica si existe una sesión activa y válida.
 *
 * Retorna:
 * true  -> existe una sesión activa.
 * false -> no existe sesión o ya expiró.
 */
bool SessionManager::hasActiveSession(const QString &filePath)
{
    return !getActiveSession(filePath).isEmpty();
}

/*
 * Elimina la información almacenada en el archivo de sesión.
 *
 * Se utiliza al cerrar sesión o cuando la sesión expira por tiempo.
 */
void SessionManager::clearSession(const QString &filePath)
{
    // Crear objeto asociado al archivo de sesión
    QFile file(filePath);

    // Abrir archivo en modo escritura para vaciarlo
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    // Cerrar archivo vacío
    file.close();
}