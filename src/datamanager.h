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
#include "waitinglistentry.h"

class DataManager
{
public:
    static DataManager & sharedInstance();

    QList<QSharedPointer<User> > getUsers(const QString &whereClause = QString(), const QMap<QString, QVariant> &whereParams = QMap<QString, QVariant>(), const QString &sortClause = QString(), int limit = -1, int offset = 0);
    QList<QSharedPointer<Region> > getRegions(const QString &whereClause = QString(), const QMap<QString, QVariant> &whereParams = QMap<QString, QVariant>(), const QString &sortClause = QString(), int limit = -1, int offset = 0);
    QList<QSharedPointer<Facility> > getFacilities(const QString &whereClause = QString(), const QMap<QString, QVariant> &whereParams = QMap<QString, QVariant>(), const QString &sortClause = QString(), int limit = -1, int offset = 0);
    QList<QSharedPointer<Patient> > getPatients(const QString &whereClause = QString(), const QMap<QString, QVariant> &whereParams = QMap<QString, QVariant>(), const QString &sortClause = QString(), int limit = -1, int offset = 0);
    QList<QSharedPointer<WaitingListEntry> > getWaitingListEntries(const QString &whereClause = QString(), const QMap<QString, QVariant> &whereParams = QMap<QString, QVariant>(), const QString &sortClause = QString(), int limit = -1, int offset = 0);

    void addPatient(const Patient &);
    void addUser(const User &);
    void addFacility(const Facility &);
    void addWaitingListEntry(const WaitingListEntry &);

    void updatePatient(const Patient &);
    void updateUser(const User &);
    void updateFacility(const Facility &);

    void deleteWaitingListEntry(const WaitingListEntry &);
private:
    DataManager();

    static void buildSelectQuery(QSqlQuery &query, const QString &selectClause, const QString &whereClause, const QMap<QString, QVariant> &whereParams, const QString &sortClause, int limit, int offset);
    \
    void setupTables();

    QSqlDatabase database;
    QMutex mutex;
};

#endif // DATAMANAGER_H
