#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

// Login que valida usuarios contra la base SQLite.
class Login : public QWidget
{
    Q_OBJECT

private:
    Ui::Login *ui;

    // Base usada para autenticar y obtener el id del usuario.
    Database db;

    int idUsuario;

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void validarLogin(); // Abre la ventana de dibujo si las credenciales son validas.
};

#endif
