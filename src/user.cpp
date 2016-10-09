#include "user.h"

User::User(const QString &name, const QString &pw, const USERTYPE uT) :
    username(name), password(pw), uType(uT)
{

}

User::User(const User &u) :
    QObject(), username(u.username), password(u.password), uType(u.uType)
{

}

void User::setPassword(const QString &password)
{
    this->password = password;
}

void User::setUserType(const USERTYPE uT)
{
    uType = uT;
}

const QString & User::getUserName() const
{
    return username;
}

const QString & User::getPassword() const
{
    return password;
}

USERTYPE User::getUserType() const
{
    return uType;
}
