#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;

class LoginWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
    QPushButton *btnLogin;
    QLabel *lblStatus;

private slots:
    void handleLogin();

public:
    explicit LoginWidget(QWidget *parent = nullptr);
};

#endif // LOGINWIDGET_H