#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include <QPoint>
#include <QColor>

// Representa un trazo completo recuperado desde la base de datos.
struct TrazoDB
{
    QVector<QPoint> puntos;
    QColor color;
    int grosor;
};

// Encapsula la conexion SQLite y las operaciones sobre usuarios, trazos y puntos.
class Database : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;

public:
    explicit Database(QObject *parent = nullptr);

    bool conectar(); // Abre la base de datos local.
    bool validarUsuario(const QString &usuario, const QString &password, int &idUsuario);

    int guardarTrazo(int idUsuario, const QColor &color, int grosor); // Crea el registro padre del trazo.
    bool guardarCoordenada(int idTrazo, const QPoint &punto, int orden); // Guarda cada punto del trazo.

    QVector<TrazoDB> cargarTrazos(int idUsuario);

    bool borrarTrazosUsuario(int idUsuario);
};

#endif
