#include <QApplication>
#include "graphicsthread.h"
#include "loginframe.h"
#include "mainwindow.h"
#include "../core/eventmanager.h"

NS_START

        const std::string GraphicsThread::name = "GRAPHICS";
MainWindow * GraphicsThread::currWindow = NULL;

GraphicsThread::GraphicsThread(int argc, char ** argv):
        Subscriber(name)
{
    EventManager::getEventManager().subscribe(this);
    QApplication app(argc, argv);
    LoginFrame * lf = new LoginFrame();
    setCurrentWindowView(lf);
    app.exec();
    delete currWindow;
}

void GraphicsThread::handleEvent(const Event & e) {

}

void GraphicsThread::setCurrentWindowView(QWidget * const v) {
    if(currWindow == NULL) {
        createNewWindow();
    }
    currWindow->setCentralWidget(v);
    currWindow->setFixedSize(v->size());
}

MainWindow * GraphicsThread::getCurrentWindow() {
    if(currWindow == NULL) {
        createNewWindow();
    }
    return currWindow;
}

void GraphicsThread::createNewWindow() {
    currWindow = new MainWindow();
    currWindow->show();
}

NS_END
