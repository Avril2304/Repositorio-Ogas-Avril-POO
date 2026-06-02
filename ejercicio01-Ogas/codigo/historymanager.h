#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QString>
#include <QStringList>

/*
 * Clase: HistoryManager
 * ----------------------------
 * Administra el historial de uso de la aplicación.
 * Guarda inicios de sesión, acciones importantes y permite recuperar
 * el listado completo para mostrarlo en la ventana principal.
 */
class HistoryManager
{
public:
    // Constructor por defecto.
    HistoryManager();

    // Registra en el historial el inicio de sesión de un usuario.
    static void saveLoginHistory(const QString &filePath, const QString &username);

    // Registra una acción general realizada dentro del sistema.
    static void saveAction(const QString &filePath, const QString &text);

    // Carga todas las líneas no vacías del archivo de historial.
    static QStringList loadHistory(const QString &filePath);
};

#endif // HISTORYMANAGER_H
