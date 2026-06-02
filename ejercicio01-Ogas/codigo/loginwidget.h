#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;

/*
 * Clase: LoginWidget
 * ----------------------------
 * Ventana encargada de solicitar usuario y contraseña.
 * Valida las credenciales contra el archivo de usuarios y, si son correctas,
 * guarda la sesión y abre la ventana principal.
 */
class LoginWidget : public QWidget
{
    Q_OBJECT

private:
    // Campos y controles visuales del formulario de inicio de sesión.
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
    QPushButton *btnLogin;
    QLabel *lblStatus;

private slots:
    // Procesa el botón de login y decide si abre la aplicación principal.
    void handleLogin();

public:
    // Construye la ventana de login.
    explicit LoginWidget(QWidget *parent = nullptr);
};

#endif // LOGINWIDGET_H
