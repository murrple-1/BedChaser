#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <string>

#include "config.h"
#include "event.h"

NS_START

class Subscriber
{
public:
    Subscriber(const std::string &);
    virtual void handleEvent(const Event &) = 0;
    std::string getID() const;
private:
    std::string id;
};

NS_END

#endif // SUBSCRIBER_H
