#include "user.h"

User::User(const QVariant &id, const QString &name, const QString &password, const UserType userType)
{
    this->id = id;
    this->username = name;
    this->password = password;
    this->userType = userType;
}

User::User(const User &source) :
    QObject(), username(source.username), password(source.password), userType(source.userType)
{

}

void User::setPassword(const QString &password)
{
    this->password = password;
}

void User::setUserType(const UserType uT)
{
    userType = uT;
}

const QString & User::getUserName() const
{
    return username;
}

const QString & User::getPassword() const
{
    return password;
}

UserType User::getUserType() const
{
    return userType;
}
