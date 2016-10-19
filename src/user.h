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
    User(const QVariant &id, const QString &name, const QString &password, UserType userType);
    User(const User &);

    int getId() const;
    const QString & getUserName() const;
    const QString & getPassword() const;
    UserType getUserType() const;

    void setPassword(const QString &);
    void setUserType(UserType);
private:
    QVariant id;
    QString username;
    QString password;
    UserType userType;
};

#endif // USER_H
