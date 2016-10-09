#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>

class Exception : public QException
{
public:
    Exception(const QByteArray &);
    virtual ~Exception() _GLIBCXX_USE_NOEXCEPT;

    void raise() const Q_DECL_OVERRIDE;
    Exception *clone() const Q_DECL_OVERRIDE;
    virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;
private:
    QByteArray message;
};

#endif // EXCEPTION_H
