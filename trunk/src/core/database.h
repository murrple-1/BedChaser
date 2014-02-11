#ifndef DATABASE_H
#define DATABASE_H

#include "config.h"
//#include <QtGui>
#include <QtSql>
#include "exception.h"

NS_START

class Database
{
public:
    static void startDatabase(const QString dBName, const QString path) throw(Exception);
    static QSqlDatabase getOpenDatabase(const QString dbName = "database");

private:
    Database();
    static void createNewDatabase(const QString dBName, const QString path) throw(Exception); // create a new database
    static void Init(const QString dBName) throw(Exception); // initialize all the tables
    static void InitRegions() throw(Exception);
    static void InitUsers() throw(Exception);
    static void InitLocations() throw(Exception);
};

NS_END

#endif // DATABASE_H
