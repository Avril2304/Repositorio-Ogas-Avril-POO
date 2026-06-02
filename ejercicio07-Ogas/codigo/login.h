#ifndef LOGIN_H
#define LOGIN_H

#include "pantalla.h"
#include "clima.h"
#include "ventana.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

// Pantalla de login con clima, hora, bloqueo por intentos y descarga de imagenes.
class login : public Pantalla
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    void inicializarPantalla() override;
    void limpiarPantalla() override;

private slots:
    void validarLogin(); // Comprueba credenciales y controla los intentos fallidos.

    void mostrarClima(QString temperatura, QString descripcion);
    void errorClima(QString mensaje);

    void descargarFondo(); // Descarga o reutiliza el fondo local.
    void procesarFondo(QNetworkReply *reply);

    void descargarImagenPrincipal();
    void procesarImagenPrincipal(QNetworkReply *reply);
    void actualizarHora();

private:
    Ui::login *ui;

    // Estado del login y dependencias de red.
    int intentos;
    bool bloqueado;

    Clima *clima;
    QNetworkAccessManager *managerFondo;
    QNetworkAccessManager *managerImagenPrincipal;
    QTimer *timerHora;

    ventana *ventanaPrincipal;
};

#endif // LOGIN_H
