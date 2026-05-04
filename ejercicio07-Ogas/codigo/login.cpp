#include "login.h"
#include "ui_login.h"
#include "logger.h"
#include "config.h"

#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include <QNetworkProxy>

login::login(QWidget *parent)
    : Pantalla(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    intentos = 0;
    bloqueado = false;
    ventanaPrincipal = nullptr;

    ui->leUsuario->clear();
    ui->leClave->clear();
    ui->lMensaje->setText("Ingrese sus datos");
    ui->lClima->setText("Cargando clima...");

    timerHora = new QTimer(this);

    connect(timerHora, SIGNAL(timeout()), this, SLOT(actualizarHora()));

    timerHora->start(1000);

    actualizarHora();

    // 1. Configurar proxy ANTES de cualquier conexión a internet
    QString proxyHost = Config::obtenerValor("PROXY_HOST");
    QString proxyPort = Config::obtenerValor("PROXY_PORT");

    if (!proxyHost.isEmpty() && !proxyPort.isEmpty()) {
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(proxyHost);
        proxy.setPort(proxyPort.toInt());

        QNetworkProxy::setApplicationProxy(proxy);

        qDebug() << "Proxy configurado:" << proxyHost << proxyPort;
        Logger::registrar("Proxy configurado: " + proxyHost + ":" + proxyPort);
    } else {
        qDebug() << "Sin proxy configurado";
        Logger::registrar("Sin proxy configurado");
    }

    // 2. Crear objetos de red
    clima = new Clima(this);

    managerFondo = new QNetworkAccessManager(this);
    managerImagenPrincipal = new QNetworkAccessManager(this);

    // 3. Conectar señales
    connect(managerFondo, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(procesarFondo(QNetworkReply*)));

    connect(managerImagenPrincipal, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(procesarImagenPrincipal(QNetworkReply*)));

    connect(clima, SIGNAL(climaActualizado(QString,QString)),
            this, SLOT(mostrarClima(QString,QString)));

    connect(clima, SIGNAL(errorClima(QString)),
            this, SLOT(errorClima(QString)));

    // 4. Leer configuración de clima
    QString ciudad = Config::obtenerValor("CIUDAD");
    QString apiKey = Config::obtenerValor("API_KEY");

    if (ciudad.isEmpty() || apiKey.isEmpty()) {
        ui->lClima->setText("No se pudo leer la configuración del clima.");
        Logger::registrar("Error al leer configuración del clima");
    } else {
        clima->consultarClima(ciudad, apiKey);
        Logger::registrar("Consulta de clima iniciada para " + ciudad);
    }

    // 5. Descargar fondo después de configurar proxy
    descargarFondo();

    // 6. Conectar login
    connect(ui->botonIngresar, SIGNAL(pressed()), this, SLOT(validarLogin()));
    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(validarLogin()));
}

login::~login()
{
    delete ui;
}

void login::inicializarPantalla()
{
    intentos = 0;
    bloqueado = false;

    ui->leUsuario->clear();
    ui->leClave->clear();
    ui->lMensaje->setText("Ingrese sus datos");
}

void login::limpiarPantalla()
{
    ui->leUsuario->clear();
    ui->leClave->clear();
    ui->lMensaje->clear();
}

void login::validarLogin()
{
    QString usuario = ui->leUsuario->text();
    QString clave = ui->leClave->text();

    if (bloqueado) {
        ui->lMensaje->setText("Login bloqueado. Espere unos segundos.");
        return;
    }

    if (usuario == "admin" && clave == "1234") {
        ui->lMensaje->setText("Descargando imagen principal...");
        Logger::registrar("Login correcto");

        descargarImagenPrincipal();

    } else {
        intentos++;

        ui->leClave->clear();
        ui->leUsuario->clear();

        Logger::registrar("Intento fallido de login");

        if (intentos >= 3) {
            bloqueado = true;
            ui->lMensaje->setText("Demasiados intentos. Espere 10 segundos.");

            Logger::registrar("Login bloqueado por 3 intentos");

            ui->botonIngresar->setEnabled(false);
            ui->leUsuario->setEnabled(false);
            ui->leClave->setEnabled(false);

            QTimer::singleShot(10000, this, [=]() {
                intentos = 0;
                bloqueado = false;

                ui->botonIngresar->setEnabled(true);
                ui->leUsuario->setEnabled(true);
                ui->leClave->setEnabled(true);

                ui->lMensaje->setText("Puede intentar nuevamente.");
            });

        } else {
            ui->lMensaje->setText("Usuario o clave incorrectos.");
        }
    }
}

void login::mostrarClima(QString temperatura, QString descripcion)
{
    ui->lClima->setText(temperatura + " - " + descripcion);
}

void login::errorClima(QString mensaje)
{
    ui->lClima->setText(mensaje);
}

void login::descargarFondo()
{
    QString ruta = "datos/fondo.jpg";

    QFile archivo(ruta);

    if (archivo.exists()) {
        QPixmap pixmap(ruta);

        this->setAutoFillBackground(true);

        QPalette palette;
        palette.setBrush(
            QPalette::Window,
            pixmap.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)
            );

        this->setPalette(palette);

        return;
    }

    QString url = "https://images.unsplash.com/photo-1500530855697-b586d89ba3ee";

    QNetworkRequest request((QUrl(url)));
    managerFondo->get(request);
}

void login::procesarFondo(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error al descargar fondo:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();

    QDir().mkpath("datos");

    QFile archivo("datos/fondo.jpg");

    if (archivo.open(QIODevice::WriteOnly)) {
        archivo.write(data);
        archivo.close();
    }

    QPixmap pixmap;
    pixmap.loadFromData(data);

    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(
        QPalette::Window,
        pixmap.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)
        );

    this->setPalette(palette);

    reply->deleteLater();
}

void login::descargarImagenPrincipal()
{
    QString url = "https://picsum.photos/1200/800.jpg";

    qDebug() << "Iniciando descarga de imagen principal...";

    QNetworkRequest request((QUrl(url)));
    managerImagenPrincipal->get(request);

    Logger::registrar("Descarga de imagen principal iniciada");
}

void login::procesarImagenPrincipal(QNetworkReply *reply)
{
    qDebug() << "Entro a procesarImagenPrincipal";

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "ERROR en descarga:" << reply->errorString();

        ui->lMensaje->setText("Error al descargar imagen. Abriendo modo offline.");
        Logger::registrar("Error al descargar imagen principal");

        ventanaPrincipal = new ventana();
        ventanaPrincipal->showFullScreen();

        this->close();

        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();

    if (data.isEmpty()) {
        qDebug() << "Imagen descargada pero VACÍA";
        Logger::registrar("Imagen principal descargada vacía");
    } else {
        qDebug() << "Imagen descargada correctamente, tamaño:" << data.size();
        Logger::registrar("Imagen principal descargada correctamente");
    }

    QDir().mkpath("datos");

    QFile archivo("datos/imagen_principal.jpg");

    if (archivo.open(QIODevice::WriteOnly)) {
        archivo.write(data);
        archivo.close();

        qDebug() << "Imagen guardada en datos/imagen_principal.jpg";
    }

    ui->lMensaje->setText("Imagen descargada OK");

    QTimer::singleShot(1500, this, [=]() {
        ventanaPrincipal = new ventana();
        ventanaPrincipal->showFullScreen();
        this->close();
    });

    reply->deleteLater();
}

void login::actualizarHora()
{
    QString hora = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    ui->lHora->setText("Hora local: " + hora);
}