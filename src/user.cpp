#include "user.h"

#include "passwordhasher.h"

User::User(const QVariant &id, const QString &username, const QString &passwordHash, const UserType userType, QObject *parent) :
    QObject(parent),
    id(id),
    username(username),
    passwordHash(passwordHash),
    type(userType)
{

}

User::User(const User &source) :
    QObject(), username(source.username), passwordHash(source.passwordHash), type(source.type)
{

}

int User::getId(bool *success) const
{
    return id.toInt(success);
}

void User::setPassword(const QString &password)
{
    this->passwordHash = PasswordHasher::sharedInstance().createHash(password);
}

void User::setPasswordHash(const QString &passwordHash)
{
    this->passwordHash = passwordHash;
}

void User::setType(const UserType type)
{
    this->type = type;
}

const QString & User::getUsername() const
{
    return username;
}

const QString & User::getPasswordHash() const
{
    return passwordHash;
}

UserType User::getType() const
{
    return type;
}
