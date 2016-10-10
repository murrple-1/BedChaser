#include "exception.h"

Exception::Exception(const QByteArray &message)
{
    this->message = message;
}

#ifdef _GLIBCXX_USE_NOEXCEPT
Exception::~Exception() _GLIBCXX_USE_NOEXCEPT
#else
Exception::~Exception()
#endif
{
    // do nothing
}

void Exception::raise() const
{
    throw *this;
}

Exception * Exception::clone() const
{
    return new Exception(*this);
}

#ifdef _GLIBCXX_USE_NOEXCEPT
const char * Exception::what() const _GLIBCXX_USE_NOEXCEPT
#else
const char * Exception::what() const
#endif
{
    return message.data();
}
