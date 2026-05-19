#ifndef PINTURA_H
#define PINTURA_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QColor>

#include "database.h"

struct Trazo
{
    QVector<QPoint> puntos;
    QColor color;
    int grosor;
};

class Pintura : public QWidget
{
private:
    QVector<Trazo> trazos;
    Trazo trazoActual;

    bool dibujando;
    QColor colorActual;
    int grosorActual;

    int idUsuario;
    Database *db;

    int accionesDeshechas;

public:
    explicit Pintura(int idUser, Database *base, QWidget *parent = nullptr);
    void cargarDesdeBase();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void guardarTrazoActual();
};

#endif