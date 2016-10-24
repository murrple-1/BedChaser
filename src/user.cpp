#include "user.h"

User::User(const QVariant &id, const QString &name, const QString &password, const UserType userType)
{
    this->id = id;
    this->username = name;
    this->passwordHash = password;
    this->userType = userType;
}

User::User(const User &source) :
    QObject(), username(source.username), passwordHash(source.passwordHash), userType(source.userType)
{

}

void User::setPassword(const QString &password)
{
    // TODO hash the password first
    this->passwordHash = password;
}

void User::setPasswordHash(const QString &passwordHash)
{
    this->passwordHash = passwordHash;
}

void User::setUserType(const UserType uT)
{
    userType = uT;
}

const QString & User::getUserName() const
{
    return username;
}

const QString & User::getPasswordHash() const
{
    return passwordHash;
}

UserType User::getUserType() const
{
    return userType;
}
