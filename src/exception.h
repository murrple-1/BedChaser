#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>

class Exception : public QException
{
public:
    Exception(const QByteArray &);
#ifdef _GLIBCXX_USE_NOEXCEPT
    virtual ~Exception() _GLIBCXX_USE_NOEXCEPT;
#else
    virtual ~Exception();
#endif

    void raise() const Q_DECL_OVERRIDE;
    Exception *clone() const Q_DECL_OVERRIDE;
 #ifdef _GLIBCXX_USE_NOEXCEPT
    virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;
#else
    virtual const char* what() const;
#endif
private:
    QByteArray message;
};

#endif // EXCEPTION_H
