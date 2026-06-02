#include "loginwidget.h"
#include "filemanager.h"
#include "sessionmanager.h"
#include "historymanager.h"
#include "mainwidget.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QCoreApplication>

/*
 * Constructor de la ventana de login.
 *
 * Define la apariencia de la pantalla, crea los campos de usuario y
 * contraseña, y conecta el botón con el método que valida el ingreso.
 */
LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Login");
    resize(420, 280);

    setStyleSheet(
        "QWidget {"
        "   background-color: #1e1e1e;"
        "   color: #f5f5f5;"
        "   font-size: 14px;"
        "}"
        "QLabel {"
        "   color: #f5f5f5;"
        "}"
        "QLineEdit {"
        "   background-color: #2d2d30;"
        "   border: 1px solid #3f3f46;"
        "   border-radius: 8px;"
        "   padding: 8px;"
        "   color: white;"
        "}"
        "QPushButton {"
        "   background-color: #0e639c;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 12px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #1177bb;"
        "}"
        );

    QLabel *titleLabel = new QLabel("Iniciar sesión");
    titleLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "   margin-bottom: 8px;"
        "}"
        );

    QLabel *subtitleLabel = new QLabel("Ingrese sus credenciales");
    subtitleLabel->setStyleSheet(
        "QLabel {"
        "   color: #cfcfcf;"
        "   margin-bottom: 8px;"
        "}"
        );

    txtUsername = new QLineEdit(this);
    txtUsername->setPlaceholderText("Usuario");

    txtPassword = new QLineEdit(this);
    txtPassword->setPlaceholderText("Contraseña");
    txtPassword->setEchoMode(QLineEdit::Password);

    btnLogin = new QPushButton("Iniciar sesión", this);

    lblStatus = new QLabel("", this);
    lblStatus->setStyleSheet("color: #9cdcfe;");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(12);

    layout->addWidget(titleLabel);
    layout->addWidget(subtitleLabel);
    layout->addWidget(txtUsername);
    layout->addWidget(txtPassword);
    layout->addWidget(btnLogin);
    layout->addWidget(lblStatus);

    setLayout(layout);

    connect(btnLogin, &QPushButton::clicked, this, &LoginWidget::handleLogin);
}

/*
 * Valida el formulario de inicio de sesión.
 *
 * Si las credenciales son correctas, guarda la sesión, registra el evento
 * en el historial y abre la ventana principal del planificador.
 */
void LoginWidget::handleLogin()
{
    // trim elimina espacios escritos accidentalmente antes o después del texto.
    QString username = txtUsername->text().trimmed();
    QString password = txtPassword->text().trimmed();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Complete usuario y contraseña.");
        return;
    }

    QString basePath = QCoreApplication::applicationDirPath();
    QString usersPath = basePath + "/users.csv";
    QString sessionPath = basePath + "/session.txt";
    QString historyPath = basePath + "/history.txt";

    // La validación se delega a FileManager para centralizar el acceso a archivos.
    bool valid = FileManager::validateUser(usersPath, username, password);

    if (valid)
    {
        SessionManager::saveSession(sessionPath, username);
        HistoryManager::saveLoginHistory(historyPath, username);

        lblStatus->setText("Sesión iniciada como: " + username);

        MainWidget *window = new MainWidget();
        window->show();

        this->close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Usuario o contraseña incorrectos.");
    }
}
