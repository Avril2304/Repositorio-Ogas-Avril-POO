#include "ventana.h"
#include "ui_ventana.h"

#include <QPixmap>
#include <QKeyEvent>
#include <QBitmap>
#include <QPainter>
#include <QSizePolicy>
#include <QLayout>
#include <QFile>

ventana::ventana(QWidget *parent)
    : Pantalla(parent)
    , ui(new Ui::ventana)
{
    ui->setupUi(this);

    inicializarPantalla();

    connect(ui->botonSalir, &QPushButton::clicked, this, &ventana::close);
}

ventana::~ventana()
{
    delete ui;
}

void ventana::inicializarPantalla()
{
    this->setStyleSheet(
        "QWidget {"
        "background-color: #1f1f1f;"
        "color: white;"
        "font-family: Segoe UI;"
        "}"

        "QWidget#contenedorCV {"
        "background-color: #2b2b2b;"
        "border-radius: 18px;"
        "padding: 30px;"
        "}"

        "QLabel#lNombre {"
        "font-size: 30px;"
        "font-weight: bold;"
        "}"

        "QLabel#lTitulo {"
        "font-size: 16px;"
        "color: #9e9e9e;"
        "}"

        "QLabel#lDescripcion {"
        "font-size: 14px;"
        "padding: 10px;"
        "}"

        "QLabel#lHabilidades {"
        "font-size: 14px;"
        "color: #7db9ff;"
        "font-weight: bold;"
        "}"

        "QPushButton#btnSalir {"
        "background-color: #3a3a3a;"
        "color: white;"
        "border-radius: 10px;"
        "padding: 12px;"
        "font-size: 15px;"
        "font-weight: bold;"
        "min-height: 35px;"
        "}"
        );

    QPixmap imagenPrincipal("datos/imagen_principal.jpg");

    if (!imagenPrincipal.isNull()) {
        ui->lImagenPrincipal->setPixmap(
            imagenPrincipal.scaled(
                500,
                180,
                Qt::KeepAspectRatioByExpanding,
                Qt::SmoothTransformation
                )
            );
    } else {
        ui->lImagenPrincipal->setText("Imagen principal no disponible");
    }

    ui->lFoto->setFixedSize(130, 130);
    ui->lFoto->setAlignment(Qt::AlignCenter);

    ui->lFoto->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (ui->lFoto->parentWidget()->layout()) {
        ui->lFoto->parentWidget()->layout()->setAlignment(ui->lFoto, Qt::AlignCenter);
    }

    QPixmap foto("recursos/foto.jpg");

    if (!foto.isNull()) {
        QPixmap fotoEscalada = foto.scaled(
            130, 130,
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation
            );

        QPixmap fotoRedonda(130, 130);
        fotoRedonda.fill(Qt::transparent);

        QPainter painter(&fotoRedonda);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(fotoEscalada));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(0, 0, 130, 130);

        ui->lFoto->setPixmap(fotoRedonda);
    } else {
        ui->lFoto->setText("Foto");
    }

    ui->lNombre->setAlignment(Qt::AlignCenter);
    ui->lTitulo->setAlignment(Qt::AlignCenter);
    ui->lDescripcion->setAlignment(Qt::AlignCenter);
    ui->lHabilidades->setAlignment(Qt::AlignCenter);

    ui->lDescripcion->setWordWrap(true);

    ui->botonSalir->setFixedHeight(85);

    ui->lNombre->setText("Avril Ogas");
    ui->lTitulo->setText("Estudiante de Ingeniería en Informática");

    ui->lDescripcion->setText(
        "Estudiante orientada al desarrollo de software, programación en C++, "
        "bases de datos y aplicaciones con interfaz gráfica en Qt."
        );

    ui->lHabilidades->setText("C++ | Qt Creator | POO | MySQL | Git y GitHub");

    connect(ui->botonSalir, SIGNAL(pressed()), this, SLOT(close()));
}

void ventana::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        this->close();
    }
}

void ventana::limpiarPantalla()
{
    // Por ahora no limpiamos nada
}