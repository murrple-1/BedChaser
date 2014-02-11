#include "QsLog.h"
#include "QsLogDest.h"
#include "gui/graphicsthread.h"
#include "logging/loggingthread.h"
#include "core/database.h"
#include "core/datamanager.h"
#include <QFile>

int main(int argc, char * argv[])
{
    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    const QString sLogPath("testlog.txt");
    QsLogging::DestinationPtr fileDestination(
            QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
    QsLogging::DestinationPtr debugDestination(
            QsLogging::DestinationFactory::MakeDebugOutputDestination() );
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    LHIN::Database::startDatabase("database", "database.db");
//    LHIN::DataManager &d = LHIN::DataManager::getDataManager();

    LHIN::LoggingThread l;
    l.start();
    LHIN::GraphicsThread g(argc, argv);
    l.quit();

    return 0;
}
