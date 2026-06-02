#ifndef LOGIN_H
#define LOGIN_H

#include "pantalla.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QFocusEvent>

namespace Ui {
class Login;
}

// Login del editor, con bloqueo temporal despues de tres intentos fallidos.
class Login : public Pantalla
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    bool validarEstado() override;
    void registrarEvento(const QString &descripcion) override;

private slots:
    void validarLogin(); // Comprueba credenciales y decide si abre el editor o bloquea.

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    Ui::Login *ui;

    // Credenciales cargadas desde configuracion y contador de intentos.
    QString usuarioCorrecto;
    QString passwordCorrecta;
    int intentosFallidos;
};

#endif // LOGIN_H
