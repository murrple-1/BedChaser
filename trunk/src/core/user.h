#ifndef USER_H
#define USER_H

#include "object.h"

NS_START

enum USERTYPE {
    STAFF,      //0
    ADMIN,      //1
    SYSADMIN    //2
};

class User : public Object
{
public:
    User(const std::string & name, const std::string & pw, const USERTYPE uT);
    User(const User &);
    virtual ~User();
    virtual std::string toString() const;
    virtual std::string toUIString() const;
    virtual void validate() const throw(Exception);
    std::string getUserName() const;
    std::string getPassword() const;
    void setPassword(const std::string &);
    USERTYPE getUserType() const;
    void setUserType(const USERTYPE);
private:
    std::string username;
    std::string password;
    USERTYPE uType;
};

NS_END

#endif // USER_H
