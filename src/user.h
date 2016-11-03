#ifndef USER_H
#define USER_H

#include <QObject>

#include <QVariant>

typedef enum
{
    UserTypeStaff = 0,
    UserTypeAdmin = 1,
    UserTypeSystemAdmin = 2
} UserType;

class User : public QObject
{
    Q_OBJECT
public:
    User(const QVariant &id, const QString &username, const QString &passwordHash, UserType type, QObject *parent = 0);
    User(const User &);

    int getId(bool *success = 0) const;
    const QString & getUsername() const;
    const QString & getPasswordHash() const;
    UserType getType() const;

    void setPassword(const QString &);
    void setPasswordHash(const QString &);
    void setType(UserType);
private:
    QVariant id;
    QString username;
    QString passwordHash;
    UserType type;
};

#endif // USER_H
