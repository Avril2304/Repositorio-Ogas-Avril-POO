#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    connect (ui->botonIngreso, SIGNAL(pressed()), this, SLOT(validarLogin()));
    connect (ui->leClave, SIGNAL(returnPressed()),this,SLOT(validarLogin()));
}

login::~login()
{
    delete ui;
}

void login::validarLogin()
{
    if(ui->leUsuario->text() == "admin" && ui->leClave->text() == "1234") {
        this->close();
    } else {
        ui->leClave->clear();
    }
}
