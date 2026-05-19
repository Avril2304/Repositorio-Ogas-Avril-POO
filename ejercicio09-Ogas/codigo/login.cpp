#include "login.h"
#include "ui_login.h"

#include "ventana.h"
#include "logger.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    idUsuario = -1;

    db.conectar();

    connect(ui->btnIngresar,
            SIGNAL(clicked()),
            this,
            SLOT(validarLogin()));
}

Login::~Login()
{
    delete ui;
}

void Login::validarLogin()
{
    QString usuario = ui->leUsuario->text();
    QString password = ui->leClave->text();

    bool valido = db.validarUsuario(usuario,
                                    password,
                                    idUsuario);

    if (valido) {

        Logger::registrar(
            "ACCESO EXITOSO - usuario: " + usuario
            );

        Ventana *v = new Ventana(idUsuario);

        v->show();

        this->close();
    }
    else {

        Logger::registrar(
            "INTENTO FALLIDO - usuario: " + usuario
            );

        ui->lblMensaje->setText(
            "Usuario o contraseña incorrectos"
            );
    }
}