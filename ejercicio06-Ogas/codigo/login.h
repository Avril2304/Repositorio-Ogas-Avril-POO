#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

// Login basado en archivo .ui generado con Qt Designer.
class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login() override;

private slots:
    void validarLogin(); // Valida usuario y clave; si son correctos cierra la ventana.

private:
    Ui::login *ui;
};
#endif // LOGIN_H
