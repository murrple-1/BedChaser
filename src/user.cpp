#include "user.h"

User::User(const QVariant &id, const QString &username, const QString &passwordHash, const UserType userType) :
    id(id),
    username(username),
    passwordHash(passwordHash),
    userType(userType)
{

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

const QString & User::getUsername() const
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
