#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    // Permite validar tanto con el boton como con Enter en el campo clave.
    connect (ui->botonIngreso, SIGNAL(pressed()), this, SLOT(validarLogin()));
    connect (ui->leClave, SIGNAL(returnPressed()),this,SLOT(validarLogin()));
}

login::~login()
{
    delete ui;
}

void login::validarLogin()
{
    // Usuario y clave fijos para probar el flujo del login.
    if(ui->leUsuario->text() == "admin" && ui->leClave->text() == "1234") {
        this->close();
    } else {
        ui->leClave->clear();
    }
}
