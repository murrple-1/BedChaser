#ifndef USER_H
#define USER_H

#include <QObject>

enum USERTYPE {
    STAFF,
    ADMIN,
    SYSADMIN
};

class User : public QObject
{
    Q_OBJECT
public:
    User(const QString &name, const QString &password, USERTYPE uT);
    User(const User &);
    const QString & getUserName() const;
    const QString & getPassword() const;
    void setPassword(const QString &);
    USERTYPE getUserType() const;
    void setUserType(USERTYPE);
private:
    QString username;
    QString password;
    USERTYPE uType;
};

#endif // USER_H
