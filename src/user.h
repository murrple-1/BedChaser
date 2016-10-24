#ifndef USER_H
#define USER_H

#include <QObject>

#include <QVariant>

typedef enum
{
    UserTypeStaff,
    UserTypeAdmin,
    UserTypeSystemAdmin
} UserType;

class User : public QObject
{
    Q_OBJECT
public:
    User(const QVariant &id, const QString &username, const QString &passwordHash, UserType userType);
    User(const User &);

    int getId() const;
    const QString & getUsername() const;
    const QString & getPasswordHash() const;
    UserType getUserType() const;

    void setPassword(const QString &);
    void setPasswordHash(const QString &);
    void setUserType(UserType);
private:
    QVariant id;
    QString username;
    QString passwordHash;
    UserType userType;
};

#endif // USER_H
