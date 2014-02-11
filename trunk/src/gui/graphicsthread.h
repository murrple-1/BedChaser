#ifndef GRAPHICSTHREAD_H
#define GRAPHICSTHREAD_H

#include <QThread>

#include "../core/config.h"
#include "../core/subscriber.h"
#include "../core/user.h"
#include "mainwindow.h"

NS_START

class GraphicsThread : public Subscriber
{
public:
    const static std::string name;
    GraphicsThread(int, char **);
    virtual void handleEvent(const Event &);

    static void setCurrentWindowView(QWidget * const);
    static MainWindow * getCurrentWindow();
private:
    static MainWindow * currWindow;
    static void createNewWindow();
};

NS_END

#endif // GRAPHICSTHREAD_H
