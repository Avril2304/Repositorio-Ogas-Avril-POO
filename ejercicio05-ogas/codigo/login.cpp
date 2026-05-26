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

    // FILA USUARIO
    QHBoxLayout *filaUsuario = new QHBoxLayout();
    filaUsuario->addWidget(labelUsuario);
    filaUsuario->addWidget(editUsuario);

    // FILA CONTRASEÑA
    QHBoxLayout *filaClave = new QHBoxLayout();
    filaClave->addWidget(labelClave);
    filaClave->addWidget(editClave);

    // AGREGAR TODO AL LAYOUT PRINCIPAL
    layoutPrincipal->addLayout(filaUsuario);
    layoutPrincipal->addLayout(filaClave);
    layoutPrincipal->addWidget(labelMensaje);
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
