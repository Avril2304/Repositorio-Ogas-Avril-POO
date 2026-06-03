#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent): QWidget(parent), ui(new Ui::Login)
{
    // Construye los widgets definidos en login.ui y los asocia a esta ventana.
    ui->setupUi(this);

    // Permite validar tanto con el boton como con Enter en el campo clave.
    connect (ui->botonIngreso, SIGNAL(pressed()), this, SLOT(validarLogin()));
    connect (ui->leClave, SIGNAL(returnPressed()),this,SLOT(validarLogin()));
}

Login::~Login()
{
    // Libera la memoria reservada para la interfaz generada por Qt.
    delete ui;
}

void Login::validarLogin()
{
    // Usuario y clave fijos para probar el flujo del login.
    if(ui->leUsuario->text() == "admin" && ui->leClave->text() == "1234") {
        // Si las credenciales son correctas, se cierra la ventana.
        this->close();
    } else {
        // Si la clave es incorrecta, se limpia para que el usuario la reingrese.
        ui->leClave->clear();
    }
}
