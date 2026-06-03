#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

// Ventana de login basada en el formulario login.ui de Qt Designer.
class Login : public QWidget
{
    Q_OBJECT

public:
    // Crea la ventana y prepara la interfaz definida en el archivo .ui.
    explicit Login(QWidget *parent = nullptr);

    // Libera la interfaz generada por Qt Designer.
    ~Login() override;

private slots:
    // Comprueba las credenciales ingresadas por el usuario.
    void validarLogin();

private:
    // Puntero a los widgets creados automaticamente desde login.ui.
    Ui::Login *ui;
};
#endif // LOGIN_H
