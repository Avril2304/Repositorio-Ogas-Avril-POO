#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;

class Login : public QWidget{

    Q_OBJECT

public :
    explicit Login(QWidget *parent = nullptr);

private slots :
    void validarLogin();

private :
    QLabel *labelUsuario;
    QLabel *labelClave;
    QLabel *labelMensaje;

    QLineEdit *editUsuario;
    QLineEdit *editClave;

    QPushButton *botonIngreso;
};

#endif // LOGIN_H
