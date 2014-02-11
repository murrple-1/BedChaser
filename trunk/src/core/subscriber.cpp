#include "subscriber.h"

NS_START

        Subscriber::Subscriber(const std::string & anId):
        id(anId)
{
}

std::string Subscriber::getID() const {
    return id;
}

NS_END
