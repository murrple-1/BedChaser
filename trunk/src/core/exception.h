#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

#include "config.h"

NS_START

class Exception : public std::exception {
public:
        Exception(const std::string &message = "", const std::string &cause = "") throw();
        virtual ~Exception() throw();
        virtual const char * what() const throw();
        const std::string & getMessage() const;
        const std::string & getCause() const;
private:
        std::string message;
        std::string cause;
};

NS_END

#endif /* EXCEPTION_H_ */
