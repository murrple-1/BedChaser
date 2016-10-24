#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

#include <QSqlDatabase>
#include <QMutex>
#include <QSharedPointer>
#include <QList>

#include "facility.h"
#include "patient.h"
#include "region.h"
#include "user.h"

class DataManager
{
public:
    static DataManager & sharedInstance();

    QList<QSharedPointer<User> > getUsers(const QString &whereClause = QString(), const QMap<QString, QString> &whereParams = QMap<QString, QString>(), const QString &sortClause = QString(), int limit = -1, int offset = 0);
    QList<QSharedPointer<Region> > getRegions(const QString &whereClause = QString(), const QMap<QString, QString> &whereParams = QMap<QString, QString>(), const QString &sortClause = QString(), int limit = -1, int offset = 0);
    QList<QSharedPointer<Facility> > getFacilities(const QString &whereClause = QString(), const QMap<QString, QString> &whereParams = QMap<QString, QString>(), const QString &sortClause = QString(), int limit = -1, int offset = 0);
    QList<QSharedPointer<Patient> > getPatients(const QString &whereClause = QString(), const QMap<QString, QString> &whereParams = QMap<QString, QString>(), const QString &sortClause = QString(), int limit = -1, int offset = 0);

    void addPatient(const Patient &);
    void addUser(const User &);
    void addFacility(const Facility &);

    void updatePatient(const Patient &);
    void updateUser(const User &);
    void updateFacility(const Facility &);
private:
    DataManager();

    static void buildSelectQuery(QSqlQuery &query, const QString &selectClause, const QString &whereClause, const QMap<QString, QString> &whereParams, const QString &sortClause, int limit, int offset);
    \
    void setupTables();

    QSqlDatabase database;
    QMutex mutex;
};

#endif // DATAMANAGER_H
