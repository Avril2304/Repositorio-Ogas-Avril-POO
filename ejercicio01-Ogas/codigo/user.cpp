#include "user.h"

/*
 * Constructor por defecto.
 * Crea un usuario sin datos iniciales.
 */
User::User()
{
}

/*
 * Constructor parametrizado.
 * Asigna el nombre de usuario y la contraseña recibidos.
 */
User::User(QString username, QString password)
{
    this->username = username;
    this->password = password;
}

//Devuelve el nombre de usuario.
QString User::getUsername() const
{
    return username;
}

//Devuelve la contraseña del usuario.
QString User::getPassword() const
{
    return password;
}

//Modifica el nombre de usuario.
void User::setUsername(QString username)
{
    this->username = username;
}

//Modifica la contraseña del usuario.
void User::setPassword(QString password)
{
    this->password = password;
}