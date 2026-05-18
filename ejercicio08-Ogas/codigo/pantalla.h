#ifndef PANTALLA_H
#define PANTALLA_H

#include <QWidget>
#include <QString>

class Pantalla : public QWidget
{
    Q_OBJECT

public:
    explicit Pantalla(QWidget *parent = nullptr);
    virtual ~Pantalla();

    virtual void inicializarUI() = 0;
    virtual void conectarEventos() = 0;
    virtual void cargarDatos() = 0;
    virtual bool validarEstado() = 0;
    virtual void registrarEvento(const QString &descripcion) = 0;
};

#endif // PANTALLA_H