#include "exception.h"

NS_START

Exception::Exception(const std::string & aMessage,
                const std::string & aCause) throw():
        message(aMessage), cause(aCause){}

Exception::~Exception() throw() {}

const char * Exception::what() const throw() {
        return "Exception";
}

const std::string & Exception::getMessage() const {
        return message;
}

const std::string & Exception::getCause() const {
        return cause;
}

NS_END
