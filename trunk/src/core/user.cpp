#include "user.h"
#include "../utils/stringbuilder.h"

NS_START

        User::User(const std::string & name, const std::string & pw, const USERTYPE uT):
        username(name)
{
    setPassword(pw);
    setUserType(uT);
}

User::User(const User & u):
        username(u.getUserName()), password(u.getPassword()), uType(u.getUserType()){}

User::~User()
{}

std::string User::toString() const
{
    StringBuilder sb;
    sb.append(std::string("User: "));
    sb.append(std::string("username=")).append(username).append(' ');
    sb.append(std::string("password=")).append(password).append(' ');
    sb.append(std::string("uType=")).append(uType);
    return sb.toString();
}

std::string User::toUIString() const
{
    return getUserName();
}

void User::validate() const throw(Exception)
{

}

void User::setPassword(const std::string & pw) {
    password = pw;
}

void User::setUserType(const USERTYPE uT) {
    uType = uT;
}

std::string User::getUserName() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

USERTYPE User::getUserType() const {
    return uType;
}

NS_END
