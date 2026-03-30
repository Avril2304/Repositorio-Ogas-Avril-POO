#include "user.h"

User::User()
{
}

User::User(QString username, QString password)
{
    this->username = username;
    this->password = password;
}

QString User::getUsername() const
{
    return username;
}

QString User::getPassword() const
{
    return password;
}

void User::setUsername(QString username)
{
    this->username = username;
}

void User::setPassword(QString password)
{
    this->password = password;
}