#ifndef USER_H
#define USER_H

#include <QString>

/*
 * Clase: User
 * ----------------------------
 * Representa un usuario del sistema.
 * Guarda el nombre de usuario y la contraseña
 * utilizados para validar el inicio de sesión.
 */
class User
{
private:
    // Nombre de usuario
    QString username;

    // Contraseña del usuario
    QString password;

public:
    // Constructor por defecto
    User();

    // Constructor con usuario y contraseña
    User(QString username, QString password);

    // Métodos get: permiten consultar los datos del usuario
    QString getUsername() const;
    QString getPassword() const;

    // Métodos set: permiten modificar los datos del usuario
    void setUsername(QString username);
    void setPassword(QString password);
};

#endif // USER_H
