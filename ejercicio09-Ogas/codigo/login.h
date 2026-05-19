#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

private:
    Ui::Login *ui;

    Database db;

    int idUsuario;

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void validarLogin();
};

#endif