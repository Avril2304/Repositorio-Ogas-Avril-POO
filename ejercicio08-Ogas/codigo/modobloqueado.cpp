#include "modobloqueado.h"
#include "logmanager.h"
#include "configmanager.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

ModoBloqueado::ModoBloqueado(QWidget *parent)
    : Pantalla(parent)
{
    // El tiempo de bloqueo se puede modificar desde la configuracion.
    segundosRestantes = ConfigManager::obtenerValor("tiempo_bloqueo", "10").toInt();

    inicializarUI();
    conectarEventos();
    cargarDatos();
}

ModoBloqueado::~ModoBloqueado()
{
}

void ModoBloqueado::inicializarUI()
{
    setWindowTitle("Modo bloqueado");

    lblTitulo = new QLabel("Acceso bloqueado", this);
    lblTitulo->setAlignment(Qt::AlignCenter);
    lblTitulo->setStyleSheet("font-size: 28px; font-weight: bold; color: red;");

    lblMensaje = new QLabel("Se superaron los 3 intentos fallidos.", this);
    lblMensaje->setAlignment(Qt::AlignCenter);

    lblTiempo = new QLabel("Espere 10 segundos para volver a intentar.", this);
    lblTiempo->setAlignment(Qt::AlignCenter);

    btnSalir = new QPushButton("Salir", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(lblTitulo);
    layout->addWidget(lblMensaje);
    layout->addWidget(lblTiempo);
    layout->addWidget(btnSalir);
    layout->addStretch();

    setLayout(layout);
}

void ModoBloqueado::conectarEventos()
{
    // Un temporizador descuenta un segundo en cada timeout.
    temporizador = new QTimer(this);

    connect(temporizador, SIGNAL(timeout()),
            this, SLOT(actualizarTiempo()));

    connect(btnSalir, &QPushButton::clicked,
            this, &ModoBloqueado::close);

    temporizador->start(1000);

    registrarEvento("Temporizador de bloqueo iniciado");
}

void ModoBloqueado::cargarDatos()
{
    registrarEvento("Datos de bloqueo cargados");
}

bool ModoBloqueado::validarEstado()
{
    return segundosRestantes <= 0;
}

void ModoBloqueado::actualizarTiempo()
{
    // Actualiza el mensaje y cierra la pantalla al terminar la espera.
    segundosRestantes--;

    lblTiempo->setText("Espere "
                       + QString::number(segundosRestantes)
                       + " segundos para volver a intentar.");

    if (segundosRestantes <= 0) {
        temporizador->stop();
        registrarEvento("Bloqueo finalizado");
        emit bloqueoFinalizado();
        close();
    }
}

void ModoBloqueado::registrarEvento(const QString &descripcion)
{
    qDebug() << "LOG:" << descripcion;
    LogManager::registrar("ModoBloqueado: " + descripcion);
}

void ModoBloqueado::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
    }

    QWidget::keyPressEvent(event);
}

void ModoBloqueado::mousePressEvent(QMouseEvent *event)
{
    registrarEvento("Click en pantalla de bloqueo");
    QWidget::mousePressEvent(event);
}

void ModoBloqueado::resizeEvent(QResizeEvent *event)
{
    registrarEvento("Pantalla de bloqueo redimensionada");
    QWidget::resizeEvent(event);
}

void ModoBloqueado::closeEvent(QCloseEvent *event)
{
    registrarEvento("Pantalla de bloqueo cerrada");
    event->accept();
}
