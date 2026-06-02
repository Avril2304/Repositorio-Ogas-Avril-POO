#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QDir>

Database::Database(QObject *parent)
    : QObject(parent)
{
}

bool Database::conectar()
{
    // La base se guarda en datos/dibujos.db dentro del directorio de ejecucion.
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString ruta = QDir::currentPath() + "/datos/dibujos.db";
    db.setDatabaseName(ruta);

    if (!db.open()) {
        qDebug() << "Error al abrir la base:" << db.lastError().text();
        qDebug() << "Ruta usada:" << ruta;
        return false;
    }

    qDebug() << "Base conectada correctamente:" << ruta;
    return true;
}

bool Database::validarUsuario(const QString &usuario, const QString &password, int &idUsuario)
{
    // Devuelve el id del usuario autenticado para asociar sus dibujos.
    QSqlQuery query;

    query.prepare("SELECT id_usuario FROM usuarios WHERE usuario = :usuario AND password = :password");
    query.bindValue(":usuario", usuario);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Error al validar usuario:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        idUsuario = query.value(0).toInt();
        return true;
    }

    return false;
}

int Database::guardarTrazo(int idUsuario, const QColor &color, int grosor)
{
    // Primero se guarda el trazo y luego sus coordenadas en otra tabla.
    QSqlQuery query;

    query.prepare("INSERT INTO trazos(id_usuario, color, grosor, fecha) "
                  "VALUES(:id_usuario, :color, :grosor, :fecha)");

    query.bindValue(":id_usuario", idUsuario);
    query.bindValue(":color", color.name());
    query.bindValue(":grosor", grosor);
    query.bindValue(":fecha", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()) {
        qDebug() << "Error al guardar trazo:" << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toInt();
}

bool Database::guardarCoordenada(int idTrazo, const QPoint &punto, int orden)
{
    // El orden permite reconstruir la linea con los puntos en la secuencia original.
    QSqlQuery query;

    query.prepare("INSERT INTO coordenadas(id_trazo, x, y, orden_punto) "
                  "VALUES(:id_trazo, :x, :y, :orden)");

    query.bindValue(":id_trazo", idTrazo);
    query.bindValue(":x", punto.x());
    query.bindValue(":y", punto.y());
    query.bindValue(":orden", orden);

    if (!query.exec()) {
        qDebug() << "Error al guardar coordenada:" << query.lastError().text();
        return false;
    }

    return true;
}

QVector<TrazoDB> Database::cargarTrazos(int idUsuario)
{
    // Recupera los trazos del usuario y luego sus coordenadas asociadas.
    QVector<TrazoDB> lista;

    QSqlQuery queryTrazos;

    queryTrazos.prepare(
        "SELECT id_trazo, color, grosor "
        "FROM trazos "
        "WHERE id_usuario = :id_usuario "
        "ORDER BY id_trazo ASC"
        );

    queryTrazos.bindValue(":id_usuario", idUsuario);

    if (!queryTrazos.exec()) {
        qDebug() << "Error al cargar trazos:" << queryTrazos.lastError().text();
        return lista;
    }

    while (queryTrazos.next()) {

        int idTrazo = queryTrazos.value(0).toInt();

        TrazoDB trazo;
        trazo.color = QColor(queryTrazos.value(1).toString());
        trazo.grosor = queryTrazos.value(2).toInt();

        QSqlQuery queryPuntos;

        queryPuntos.prepare(
            "SELECT x, y "
            "FROM coordenadas "
            "WHERE id_trazo = :id_trazo "
            "ORDER BY orden_punto ASC"
            );

        queryPuntos.bindValue(":id_trazo", idTrazo);

        if (queryPuntos.exec()) {
            while (queryPuntos.next()) {
                int x = queryPuntos.value(0).toInt();
                int y = queryPuntos.value(1).toInt();

                trazo.puntos.push_back(QPoint(x, y));
            }
        }

        lista.push_back(trazo);
    }

    return lista;
}

bool Database::borrarTrazosUsuario(int idUsuario)
{
    // Borra primero coordenadas y despues trazos para respetar la relacion entre tablas.
    QSqlQuery buscarTrazos;

    buscarTrazos.prepare(
        "SELECT id_trazo FROM trazos WHERE id_usuario = :id_usuario"
        );

    buscarTrazos.bindValue(":id_usuario", idUsuario);

    if (!buscarTrazos.exec()) {
        qDebug() << "Error al buscar trazos para borrar:"
                 << buscarTrazos.lastError().text();
        return false;
    }

    while (buscarTrazos.next()) {

        int idTrazo = buscarTrazos.value(0).toInt();

        QSqlQuery borrarCoordenadas;

        borrarCoordenadas.prepare(
            "DELETE FROM coordenadas WHERE id_trazo = :id_trazo"
            );

        borrarCoordenadas.bindValue(":id_trazo", idTrazo);

        if (!borrarCoordenadas.exec()) {
            qDebug() << "Error al borrar coordenadas:"
                     << borrarCoordenadas.lastError().text();
            return false;
        }
    }

    QSqlQuery borrarTrazos;

    borrarTrazos.prepare(
        "DELETE FROM trazos WHERE id_usuario = :id_usuario"
        );

    borrarTrazos.bindValue(":id_usuario", idUsuario);

    if (!borrarTrazos.exec()) {
        qDebug() << "Error al borrar trazos:"
                 << borrarTrazos.lastError().text();
        return false;
    }

    return true;
}
