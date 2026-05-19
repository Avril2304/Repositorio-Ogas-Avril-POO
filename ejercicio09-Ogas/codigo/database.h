#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include <QPoint>
#include <QColor>

struct TrazoDB
{
    QVector<QPoint> puntos;
    QColor color;
    int grosor;
};

class Database : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;

public:
    explicit Database(QObject *parent = nullptr);

    bool conectar();
    bool validarUsuario(const QString &usuario, const QString &password, int &idUsuario);

    int guardarTrazo(int idUsuario, const QColor &color, int grosor);
    bool guardarCoordenada(int idTrazo, const QPoint &punto, int orden);

    QVector<TrazoDB> cargarTrazos(int idUsuario);

    bool borrarTrazosUsuario(int idUsuario);
};

#endif