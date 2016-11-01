#ifndef PASSWORDHASHER_H
#define PASSWORDHASHER_H

#include <QObject>

class PasswordHasher : public QObject
{
public:
    static const PasswordHasher & sharedInstance();

    static unsigned long long DEFAULT_OPSLIMIT;
    static size_t DEFAULT_MEMLIMIT;

    QString createHash(const QString &password, unsigned long long opslimit = DEFAULT_OPSLIMIT, size_t memlimit = DEFAULT_MEMLIMIT) const;
    bool validatePassword(const QString &password, const QString &correctHash) const;
private:
    PasswordHasher(QObject *parent = 0);
};

#endif // PASSWORDHASHER_H
