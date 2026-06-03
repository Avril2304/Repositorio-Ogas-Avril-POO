#include "login.h"


Login :: Login(QWidget *parent) : QWidget (parent){

    // Titulo que se muestra en la barra superior de la ventana.
    setWindowTitle("Login");

    // Se crean los controles para ingresar el usuario.
    labelUsuario = new QLabel("Usuario: ");
    editUsuario = new QLineEdit();

    labelClave = new QLabel("Contraseña: ");
    editClave = new QLineEdit();
    // Oculta la clave mientras el usuario la escribe.
    editClave -> setEchoMode(QLineEdit :: Password);

    // Boton que permite enviar los datos ingresados.
    botonIngreso = new QPushButton("Ingresar: ");

    // Layout que ubica cada widget en una fila y columna.
    layoutPrincipal = new QGridLayout();

    // Se agregan las etiquetas, campos y boton al layout principal.
    layoutPrincipal -> addWidget(labelUsuario, 0, 0, 1, 1);
    layoutPrincipal -> addWidget(editUsuario, 0, 1, 1, 2);
    layoutPrincipal -> addWidget(labelClave, 1, 0, 1, 1);
    layoutPrincipal -> addWidget(editClave, 1, 1, 1, 2);
    layoutPrincipal -> addWidget(botonIngreso, 2, 1, 1, 1);

    this -> setLayout(layoutPrincipal);

    // Al presionar el boton o Enter en la clave, se validan las credenciales.
    connect(botonIngreso, SIGNAL(pressed()), this, SLOT(validarLogin()));
    connect(editClave, SIGNAL(returnPressed()), this, SLOT(validarLogin()));

}


void Login::validarLogin()
{
    // Credenciales fijas usadas para comprobar el ingreso.
    if(this -> editUsuario->text() == "admin" && this -> editClave->text() == "1234"){
        // Si los datos son correctos, se cierra la ventana.
        this -> close();

    } else {
        // Si los datos son incorrectos, se limpia solo el campo de clave.
        this -> editClave -> clear();
    }
}
