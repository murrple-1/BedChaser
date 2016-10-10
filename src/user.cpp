#include "user.h"

User::User(const QString &name, const QString &password, const USERTYPE uT) :
    uType(uT)
{
    this->username = name;
    this->password = password;
    this->uType = uT;
}

User::User(const User &source) :
    QObject(), username(source.username), password(source.password), uType(source.uType)
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
