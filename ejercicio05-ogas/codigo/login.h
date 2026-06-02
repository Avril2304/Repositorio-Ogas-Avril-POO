#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;

// Widget simple de login con usuario y clave fijos.
class Login : public QWidget{

    Q_OBJECT

public :
    explicit Login(QWidget *parent = nullptr);

private slots :
    void validarLogin(); // Comprueba las credenciales y muestra el resultado en pantalla.

private :
    // Controles de la interfaz creados desde codigo.
    QLabel *labelUsuario;
    QLabel *labelClave;
    QLabel *labelMensaje;

    QLineEdit *editUsuario;
    QLineEdit *editClave;

    QPushButton *botonIngreso;
};

#endif // LOGIN_H
