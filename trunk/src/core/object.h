#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>

#include "config.h"
#include "exception.h"

NS_START

        class Object {
        public:
    Object();
    virtual ~Object();
    virtual std::string toString() const = 0;
    virtual std::string toUIString() const = 0;
    virtual void validate() const throw(Exception) = 0;
};

NS_END

#endif /* OBJECT_H_ */
