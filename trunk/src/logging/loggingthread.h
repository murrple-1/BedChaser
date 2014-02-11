#ifndef LOGGINGTHREAD_H
#define LOGGINGTHREAD_H

#include <QThread>

#include "../core/config.h"
#include "../core/subscriber.h"

NS_START

class LoggingThread : public QThread, public Subscriber
{
public:
    const static std::string name;
    LoggingThread();
    virtual void handleEvent(const Event &);
protected:
    virtual void run();
};

NS_END

#endif // LOGGINGTHREAD_H
