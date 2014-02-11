#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>

#include "config.h"
#include "event.h"
#include "subscriber.h"

class Event;
class Subscriber;

NS_START

class EventManager
{
public:
    static EventManager & getEventManager();
    void receiveEvent(const Event &, const std::string * const ignoreID) const;
    void subscribe(Subscriber * const);
private:
    EventManager();

    std::list<Subscriber *> subList;
};

NS_END

#endif // EVENTMANAGER_H
