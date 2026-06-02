#ifndef PANTALLA_H
#define PANTALLA_H

#include <QWidget>
#include <QString>

// Interfaz comun para las pantallas del ejercicio 08.
class Pantalla : public QWidget
{
    Q_OBJECT

public:
    explicit Pantalla(QWidget *parent = nullptr);
    virtual ~Pantalla();

    virtual void inicializarUI() = 0;      // Crea o prepara controles visuales.
    virtual void conectarEventos() = 0;    // Conecta senales y slots.
    virtual void cargarDatos() = 0;        // Lee datos iniciales o configuracion.
    virtual bool validarEstado() = 0;      // Revisa si la pantalla esta en estado valido.
    virtual void registrarEvento(const QString &descripcion) = 0; // Envia eventos al log.
};

#endif // PANTALLA_H
