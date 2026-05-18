#include "login.h"
#include "ui_login.h"
#include "editorprincipal.h"
#include "modobloqueado.h"
#include "logmanager.h"
#include "configmanager.h"

#include <QDebug>
#include <QMessageBox>

Login::Login(QWidget *parent)
    : Pantalla(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    intentosFallidos = 0;

    inicializarUI();
    conectarEventos();
    cargarDatos();
}

Login::~Login()
{
    delete ui;
}

void Login::inicializarUI()
{
    setWindowTitle("Ejercicio 08 - Login");

    ui->leClave->setEchoMode(QLineEdit::Password);

    registrarEvento("Interfaz de Login inicializada");
}

void Login::conectarEventos()
{
    connect(ui->btnIngresar, SIGNAL(pressed()), this, SLOT(validarLogin()));

    registrarEvento("Eventos de Login conectados");
}

void Login::cargarDatos()
{
    usuarioCorrecto = ConfigManager::obtenerValor("usuario", "admin");
    passwordCorrecta = ConfigManager::obtenerValor("password", "1234");

    registrarEvento("Datos de Login cargados desde archivo de configuración");
}

bool Login::validarEstado()
{
    QString usuarioIngresado = ui->leUsuario->text();
    QString passwordIngresada = ui->leClave->text();

    return usuarioIngresado == usuarioCorrecto &&
           passwordIngresada == passwordCorrecta;
}

void Login::validarLogin()
{
    if (validarEstado()) {

        registrarEvento("Login correcto");

        Pantalla *editor = new EditorPrincipal();
        editor->showFullScreen();

        this->close();

    } else {

        intentosFallidos++;

        QMessageBox::warning(this,
                             "Login incorrecto",
                             "Usuario o contraseña incorrectos. Intento "
                                 + QString::number(intentosFallidos)
                                 + " de 3.");

        registrarEvento("Intento fallido de login");

        if (intentosFallidos >= 3) {

            registrarEvento("Usuario bloqueado temporalmente");

            Pantalla *bloqueado = new ModoBloqueado();

            ModoBloqueado *modo = dynamic_cast<ModoBloqueado*>(bloqueado);

            if (modo != nullptr) {

                connect(modo, &ModoBloqueado::bloqueoFinalizado,
                        this, [this]() {

                            intentosFallidos = 0;
                            this->show();
                        });
            }

            bloqueado->show();
            this->hide();
        }
    }
}

void Login::registrarEvento(const QString &descripcion)
{
    qDebug() << "LOG:" << descripcion;
    LogManager::registrar("Login: " + descripcion);
}

void Login::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        registrarEvento("Login enviado con tecla Enter");
        validarLogin();
    }

    QWidget::keyPressEvent(event);
}

void Login::mousePressEvent(QMouseEvent *event)
{
    registrarEvento("Click en pantalla de login");

    QWidget::mousePressEvent(event);
}

void Login::resizeEvent(QResizeEvent *event)
{
    registrarEvento("Login redimensionado");

    QWidget::resizeEvent(event);
}

void Login::closeEvent(QCloseEvent *event)
{
    registrarEvento("Login cerrado");

    event->accept();
}

void Login::focusInEvent(QFocusEvent *event)
{
    registrarEvento("Login recibió foco");

    QWidget::focusInEvent(event);
}

void Login::focusOutEvent(QFocusEvent *event)
{
    registrarEvento("Login perdió foco");

    QWidget::focusOutEvent(event);
}