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

// Widget principal del juego T-Rex: actualiza estado, dibuja y procesa controles.
class Juego : public QWidget
{
    Q_OBJECT

private:
    // Entidades principales del juego.
    TRex trex;
    Cactus cactus;

    QPixmap imagenTrex;
    QPixmap imagenCactus;
    QPixmap imagenPajaro;
    QPixmap imagenPajaro2;
    QPixmap imagenPajaro3;

    // Obstaculos aereos creados dinamicamente.
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
    void verificarColisiones(); // Detecta choques con cactus y pajaros.
    void reiniciarJuego();      // Restaura puntaje, velocidad y entidades.
    void eliminarPajaros();     // Libera memoria de pajaros creados.

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void actualizarJuego();
    void crearPajaro();
};

#endif
