#include "event.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "datamanager.h"
#include "location.h"
#include "patient.h"
#include <QDateTime>

NS_START

        Event::Event(const ActionType aT, const std::string & det):
        details(det), aType(aT)
{
}

std::string Event::getDetails() const {
    return details;
}

ActionType Event::getActionType() const {
    return aType;
}

NS_END
