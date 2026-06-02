#include "historymanager.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

HistoryManager::HistoryManager()
{
}

/*
 * Guarda un registro específico para los inicios de sesión.
 *
 * El nombre de usuario se escribe junto con la fecha y hora actual
 * para poder consultar posteriormente cuándo ingresó al sistema.
 */
void HistoryManager::saveLoginHistory(const QString &filePath, const QString &username)
{
    // Se abre en modo Append para conservar los eventos anteriores.
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

/*
 * Guarda una acción general realizada por el usuario.
 *
 * Recibe el texto de la acción ya armado y le antepone la fecha/hora
 * para mantener un historial cronológico.
 */
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

/*
 * Lee el archivo de historial completo.
 *
 * Retorna solamente las líneas con contenido para evitar mostrar
 * entradas vacías en el QListWidget de la ventana principal.
 */
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
