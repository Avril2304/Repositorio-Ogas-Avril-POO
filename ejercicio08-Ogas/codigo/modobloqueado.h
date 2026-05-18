#ifndef MODOBLOQUEADO_H
#define MODOBLOQUEADO_H

#include "pantalla.h"

#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QCloseEvent>

class ModoBloqueado : public Pantalla
{
    Q_OBJECT

public:
    explicit ModoBloqueado(QWidget *parent = nullptr);
    ~ModoBloqueado();

    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    bool validarEstado() override;
    void registrarEvento(const QString &descripcion) override;

signals:
    void bloqueoFinalizado();

private slots:
    void actualizarTiempo();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    QLabel *lblTitulo;
    QLabel *lblMensaje;
    QLabel *lblTiempo;
    QPushButton *btnSalir;

    QTimer *temporizador;
    int segundosRestantes;
};

#endif // MODOBLOQUEADO_H