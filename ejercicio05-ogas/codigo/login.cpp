#include "login.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

Login :: Login(QWidget *parent) : QWidget (parent){

    setWindowTitle("Login");

    labelUsuario = new QLabel("Usuario: ");
    editUsuario = new QLineEdit();

    labelClave = new QLabel("Contraseña: ");
    editClave = new QLineEdit();
    editClave -> setEchoMode(QLineEdit :: Password);

    botonIngreso = new QPushButton("Ingresar: ");

    labelMensaje = new QLabel("");


    QVBoxLayout *layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addWidget(labelUsuario);
    layoutPrincipal->addWidget(labelClave);
    layoutPrincipal->addWidget(labelMensaje);
    layoutPrincipal->addWidget(editUsuario);
    layoutPrincipal->addWidget(editClave);
    layoutPrincipal->addWidget(botonIngreso);

    setLayout(layoutPrincipal);

    connect(botonIngreso, &QPushButton::clicked,
            this, &Login::validarLogin);

}


void Login::validarLogin()
{
    QString usuario =editUsuario->text();
    QString clave =editClave->text();

    if(usuario == "admin" && clave == "1234"){
        labelMensaje->setText("Login correcto");

    } else {
        labelMensaje->setText("Login incorrecto");

    }
}
