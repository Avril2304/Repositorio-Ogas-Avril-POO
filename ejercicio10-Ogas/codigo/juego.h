#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QVector>
#include <QPixmap>

#include "trex.h"
#include "cactus.h"
#include "pajaro.h"

class Juego : public QWidget
{
    Q_OBJECT

private:
    TRex trex;
    Cactus cactus;

    QPixmap imagenTrex;
    QPixmap imagenCactus;
    QPixmap imagenPajaro;
    QPixmap imagenPajaro2;
    QPixmap imagenPajaro3;

    QVector<Pajaro*> pajaros;

    QTimer *timerJuego;
    QTimer *timerCrearPajaro;

    bool gameOver;
    int puntaje;
    int nivelVelocidad;

    int desplazamientoSuelo;
    int desplazamientoNubes;

    int velocidadExtraPajaros;

public:
    explicit Juego(QWidget *parent = nullptr);
    ~Juego();

private:
    void verificarColisiones();
    void reiniciarJuego();
    void eliminarPajaros();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void actualizarJuego();
    void crearPajaro();
};

#endif