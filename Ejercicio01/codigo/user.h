#ifndef USER_H
#define USER_H

#include <QString>

class User
{
private:
    QString username;
    QString password;

public:
    User();
    User(QString username, QString password);

    QString getUsername() const;
    QString getPassword() const;

    void setUsername(QString username);
    void setPassword(QString password);
};

#endif // USER_H
