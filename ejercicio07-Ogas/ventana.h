#ifndef VENTANA_H
#define VENTANA_H

#include "pantalla.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ventana;
}
QT_END_NAMESPACE

class ventana : public Pantalla
{
    Q_OBJECT

public:
    explicit ventana(QWidget *parent = nullptr);
    ~ventana();

    void inicializarPantalla() override;
    void limpiarPantalla() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::ventana *ui;
};

#endif // VENTANA_H