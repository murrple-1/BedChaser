#include "passwordhasher.h"

#include <QString>

#include <sodium.h>

#include "exception.h"

unsigned long long PasswordHasher::DEFAULT_OPSLIMIT = crypto_pwhash_OPSLIMIT_MODERATE;
size_t PasswordHasher::DEFAULT_MEMLIMIT = crypto_pwhash_MEMLIMIT_MODERATE;

const PasswordHasher & PasswordHasher::sharedInstance()
{
    static PasswordHasher _sharedInstance;
    return _sharedInstance;
}

PasswordHasher::PasswordHasher(QObject *parent) :
    QObject(parent)
{
    if (sodium_init() != 0)
    {
        throw Exception("LibSodium could not initialize");
    }
}

QString PasswordHasher::createHash(const QString &password, unsigned long long opslimit, size_t memlimit) const
{
    char out[crypto_pwhash_STRBYTES];
    QByteArray passwordBytes = password.toUtf8();
    char *_passwordBytes = passwordBytes.data();
    unsigned long long passwordLength = passwordBytes.length();
    int retVal = crypto_pwhash_str(out, _passwordBytes, passwordLength, opslimit, memlimit);
    if(retVal == 0)
    {
        QByteArray outBytes(out, crypto_pwhash_STRBYTES);
        QString outString(outBytes);
        return outString;
    }
    else
    {
        throw Exception("createHash failed");
    }
}

bool PasswordHasher::validatePassword(const QString &password, const QString &correctHash) const
{
    QByteArray passwordBytes = password.toUtf8();
    char *_passwordBytes = passwordBytes.data();
    unsigned long long passwordLength = passwordBytes.length();

    QByteArray correctHashBytes = correctHash.toUtf8();
    char *_correctHashBytes = correctHashBytes.data();

    int retVal = crypto_pwhash_str_verify(_correctHashBytes, _passwordBytes, passwordLength);

    return retVal == 0;
}
