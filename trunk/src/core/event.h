#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "config.h"

NS_START



enum ActionType {
    CREATE,
    DELETE,
    UPDATE
};

class Event
{
public:
    Event(const ActionType, const std::string & );
    std::string getDetails() const;
    ActionType getActionType() const;
private:
    std::string details;
    ActionType aType;
};

NS_END

#endif // EVENT_H
