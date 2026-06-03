#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>

// Clase que representa la ventana de login del ejercicio.
class Login : public QWidget{

    Q_OBJECT

public :
    // Constructor de la ventana. El parent permite integrarla dentro de otra ventana si hiciera falta.
    explicit Login(QWidget *parent = nullptr);

private slots :
    // Slot que se ejecuta cuando el usuario intenta ingresar.
    void validarLogin();

private :
    // Etiquetas que identifican cada campo del formulario.
    QLabel *labelUsuario, *labelClave;

    // Campos donde el usuario escribe su nombre y su clave.
    QLineEdit *editUsuario, *editClave;

    // Boton que dispara la validacion del formulario.
    QPushButton *botonIngreso;

    // Layout principal que ordena los widgets en forma de grilla.
    QGridLayout *layoutPrincipal;
};

#endif // LOGIN_H
