#include "eventmanager.h"
#include "exception.h"
#include "QsLog.h"
#include "QsLogDest.h"

NS_START

        EventManager & EventManager::getEventManager() {
    static EventManager em;
    return em;
}

EventManager::EventManager()
{}

void EventManager::receiveEvent(const Event & e, const std::string * const ignoreID) const {
    std::list<Subscriber *>::const_iterator iter;
    for(iter = subList.begin(); iter != subList.end(); iter++) {
        if(ignoreID != NULL && (*iter)->getID() == *ignoreID) {
            continue;
        }
        try {
            (*iter)->handleEvent(e);
        }
        catch(Exception & x) {
            QLOG_ERROR() << "Receiving an event failed " << x.getCause().c_str() << " " << x.getMessage().c_str();
        }
    }
    QLOG_INFO() << "Receiving an event was successful " << e.getDetails().c_str();
}

void EventManager::subscribe(Subscriber * const sub) {
    try {
        subList.push_back(sub);
        QLOG_INFO() << "subscription was successful " << sub->getID().c_str();
    }
    catch(std::exception & e) {
        QLOG_ERROR() << "subscription failed " << sub->getID().c_str() << " " << e.what();
    }
}

NS_END
