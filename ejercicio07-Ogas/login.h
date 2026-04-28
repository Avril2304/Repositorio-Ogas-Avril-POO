#ifndef LOGIN_H
#define LOGIN_H

#include "pantalla.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public Pantalla
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    void inicializarPantalla() override;
    void limpiarPantalla() override;

private slots:
    void validarLogin();

private:
    Ui::login *ui;

    int intentos;
    bool bloqueado;
};
#endif // LOGIN_H
