#include "login.h"
#include "ui_login.h"
#include "logger.h"

#include <QTimer>

login::login(QWidget *parent)
    : Pantalla(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    // Inicializamos pantalla
    inicializarPantalla();

    // Conectamos botón y Enter
    connect(ui->botonIngresar, SIGNAL(pressed()), this, SLOT(validarLogin()));
    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(validarLogin()));
}

login::~login()
{
    delete ui;
}

void login::inicializarPantalla()
{
    intentos = 0;
    bloqueado = false;

    ui->leUsuario->clear();
    ui->leClave->clear();
    ui->lMensaje->setText("Ingrese sus datos");
}

void login::limpiarPantalla()
{
    ui->leUsuario->clear();
    ui->leClave->clear();
    ui->lMensaje->clear();
}

void login::validarLogin()
{
    QString usuario = ui->leUsuario->text();
    QString clave = ui->leClave->text();

    if (bloqueado) {
        ui->lMensaje->setText("Login bloqueado. Espere unos segundos.");
        return;
    }

    if (usuario == "admin" && clave == "1234") {
        ui->lMensaje->setText("Ingreso correcto");
        // MÁS ADELANTE: abrir la ventana principal
    } else {
        intentos++;

        ui->leClave->clear();
        ui->leUsuario->clear();

        if (intentos >= 3) {
            bloqueado = true;
            ui->lMensaje->setText("Demasiados intentos. Espere 10 segundos.");

            ui->botonIngresar->setEnabled(false);
            ui->leUsuario->setEnabled(false);
            ui->leClave->setEnabled(false);

            QTimer::singleShot(10000, this, [=]() {
                intentos = 0;
                bloqueado = false;

                ui->botonIngresar->setEnabled(true);
                ui->leUsuario->setEnabled(true);
                ui->leClave->setEnabled(true);

                ui->lMensaje->setText("Puede intentar nuevamente.");
            });

        } else {
            ui->lMensaje->setText("Usuario o clave incorrectos.");
        }
    }
}

