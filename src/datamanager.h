#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

#include <QSqlDatabase>
#include <QMutex>
#include <QSharedPointer>

#include "map.h"
#include "facility.h"
#include "patient.h"
#include "region.h"
#include "user.h"

class DataManager
{
public:
    static DataManager & sharedInstance();

    void addPatient(const Patient &);
    void addUser(const User &);
    void addFacility(const Facility &);

    void addToWaitingList(const Region &, const Patient &);
    void removeFromWaitingList(const Region &, const Patient &);

    void updatePatient(const Patient &);
    void updateUser(const User &);
    void updateFacility(const Facility &);

    void deletePatient(int HCN);
    void deleteUser(const QString &username);
    void deleteFacility(int fID);

    QSharedPointer<Map> getMap();
    QSharedPointer<Region> getRegion(int id);
    QSharedPointer<Facility> getFacility(int id);
    QSharedPointer<Patient> getPatient(int HCN);
    QSharedPointer<User> getUser(const QString &userName);
private:
    DataManager();
    \
    void setupTables();

    QSqlDatabase database;
    QMutex mutex;
};

#endif // DATAMANAGER_H
