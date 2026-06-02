#include "juego.h"

Juego::Juego(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Ejercicio 10 - T-Rex Extremo");
    resize(800, 400);

    setFocusPolicy(Qt::StrongFocus);

    gameOver = false;
    puntaje = 0;
    nivelVelocidad = 1;
    desplazamientoSuelo = 0;
    desplazamientoNubes = 0;
    velocidadExtraPajaros = 0;

    imagenTrex.load(":/recursos/recursos/t-rex.png");
    imagenCactus.load(":/recursos/recursos/cactus.png");

    imagenPajaro.load(":/recursos/recursos/pajaro.png");
    imagenPajaro2.load(":/recursos/recursos/pajaro2.png");
    imagenPajaro3.load(":/recursos/recursos/pajaro3.png");

    timerJuego = new QTimer(this);
    timerCrearPajaro = new QTimer(this);

    connect(timerJuego, SIGNAL(timeout()),
            this, SLOT(actualizarJuego()));

    connect(timerCrearPajaro, SIGNAL(timeout()),
            this, SLOT(crearPajaro()));

    timerJuego->start(30);
    timerCrearPajaro->start(5000);

    QTimer::singleShot(3000, this, SLOT(crearPajaro()));
}

Juego::~Juego()
{
    eliminarPajaros();
}

void Juego::actualizarJuego()
{
    if (gameOver)
        return;

    trex.actualizar();
    cactus.mover();

    desplazamientoSuelo -= nivelVelocidad * 4;
    desplazamientoNubes -= nivelVelocidad;

    if (desplazamientoSuelo <= -40)
    {
        desplazamientoSuelo = 0;
    }

    if (desplazamientoNubes <= -800)
    {
        desplazamientoNubes = 0;
    }

    puntaje += nivelVelocidad;

    if (puntaje % 500 == 0)
    {
        nivelVelocidad++;
        cactus.aumentarVelocidad();
        velocidadExtraPajaros++;

        for (int i = 0; i < pajaros.size(); i++)
        {
            pajaros[i]->aumentarVelocidad();
        }
    }

    verificarColisiones();

    for (int i = pajaros.size() - 1; i >= 0; i--)
    {
        if (pajaros[i]->estaFueraDePantalla())
        {
            delete pajaros[i];
            pajaros.remove(i);
        }
    }

    update();
}

void Juego::crearPajaro()
{
    if (gameOver)
        return;

    Pajaro *nuevoPajaro = new Pajaro(this);

    for (int i = 0; i < velocidadExtraPajaros; i++)
    {
        nuevoPajaro->aumentarVelocidad();
    }

    pajaros.append(nuevoPajaro);
}

void Juego::verificarColisiones()
{
    QRect rectTrex = trex.obtenerRectanguloColision().adjusted(-3, -3, 3, 3);

    if (rectTrex.intersects(cactus.obtenerRectanguloColision()))
    {
        gameOver = true;
        timerJuego->stop();
        timerCrearPajaro->stop();
        update();
        return;
    }

    for (int i = 0; i < pajaros.size(); i++)
    {
        if (rectTrex.intersects(pajaros[i]->obtenerRectanguloColision()))
        {
            gameOver = true;
            timerJuego->stop();
            timerCrearPajaro->stop();
            update();
            return;
        }
    }
}

void Juego::reiniciarJuego()
{
    trex = TRex();
    cactus = Cactus();

    eliminarPajaros();

    gameOver = false;
    puntaje = 0;
    nivelVelocidad = 1;
    velocidadExtraPajaros = 0;

    desplazamientoSuelo = 0;
    desplazamientoNubes = 0;

    timerJuego->start(30);
    timerCrearPajaro->start(5000);

    QTimer::singleShot(3000, this, SLOT(crearPajaro()));

    update();
}

void Juego::eliminarPajaros()
{
    for (int i = 0; i < pajaros.size(); i++)
    {
        delete pajaros[i];
    }

    pajaros.clear();
}

void Juego::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // Fondo
    painter.fillRect(rect(), QColor(245, 245, 245));

    // Nubes simples
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(220, 220, 220));

    for (int i = 0; i < 3; i++)
    {
        int xNube = desplazamientoNubes + i * 350 + 150;

        painter.drawEllipse(xNube, 70, 50, 25);
        painter.drawEllipse(xNube + 30, 60, 60, 35);
        painter.drawEllipse(xNube + 75, 72, 45, 22);
    }

    // Suelo con movimiento
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(0, 300, width(), 300);

    painter.setPen(QPen(Qt::gray, 1));

    for (int x = desplazamientoSuelo; x < width(); x += 40)
    {
        painter.drawLine(x, 310, x + 20, 310);
    }
    // Puntaje
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(650, 40, "Puntaje: " + QString::number(puntaje));
    painter.drawText(650, 65, "Nivel: " + QString::number(nivelVelocidad));

    // Controles
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));

    painter.drawText(20, 30, "ESPACIO: Saltar");
    painter.drawText(20, 50, "ABAJO: Agacharse");
    painter.drawText(20, 70, "DERECHA: Adelantarse");
    painter.drawText(20, 90, "IZQUIERDA: Frenarse");

    // T-Rex
    QRect rectTrex = trex.obtenerRectangulo();

    painter.drawPixmap(rectTrex, imagenTrex);

    // Cactus
    QRect rectCactus = cactus.obtenerRectangulo();

    painter.drawPixmap(rectCactus, imagenCactus);

    // Pájaros
    for (int i = 0; i < pajaros.size(); i++)
    {
        QRect rectPajaro = pajaros[i]->obtenerRectangulo();

        if (pajaros[i]->getTipo() == 0)
        {
            painter.drawPixmap(rectPajaro, imagenPajaro);
        }
        else if (pajaros[i]->getTipo() == 1)
        {
            painter.drawPixmap(rectPajaro, imagenPajaro2);
        }
        else
        {
            painter.drawPixmap(rectPajaro, imagenPajaro3);
        }
    }

    // Game Over
    if (gameOver)
    {
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 28, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");

        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 12));
        painter.drawText(300, 250, "Presione R para reiniciar");
    }
}

void Juego::keyPressEvent(QKeyEvent *event)
{
    if (gameOver)
    {
        if (event->key() == Qt::Key_R)
        {
            reiniciarJuego();
        }

        return;
    }

    if (event->key() == Qt::Key_Space)
    {
        trex.saltar();
    }

    if (event->key() == Qt::Key_Down)
    {
        trex.agacharse();
    }

    if (event->key() == Qt::Key_Right)
    {
        trex.adelantar();
    }

    if (event->key() == Qt::Key_Left)
    {
        trex.frenar();
    }
}

void Juego::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Down)
    {
        trex.levantarse();
    }
}