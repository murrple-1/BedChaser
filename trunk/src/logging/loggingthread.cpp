#include "loggingthread.h"
#include "../core/eventmanager.h"
#include <iostream>

NS_START

        const std::string LoggingThread::name = "LOGGING";

LoggingThread::LoggingThread():
        Subscriber(name)
{
}

void LoggingThread::run() {
    EventManager::getEventManager().subscribe(this);
}

void LoggingThread::handleEvent(const Event & e) {
    std::cout << "GOT AN EVENT" << std::endl;
}

NS_END
