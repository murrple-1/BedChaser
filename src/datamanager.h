#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

#include <QSqlDatabase>
#include <QMutex>
#include <QSharedPointer>

#include "map.h"
#include "location.h"
#include "patient.h"
#include "region.h"
#include "user.h"

class DataManager
{
public:
    static DataManager & sharedInstance();

    void addPatient(const Patient &);
    void addUser(const User &);
    void addLocation(const Location &);

    void addToWaitingList(const Region &, const Patient &);
    void removeFromWaitingList(const Region &, const Patient &);

    void updatePatient(const Patient &);
    void updateUser(const User &);
    void updateLocation(const Location &);

    void deletePatient(int HCN);
    void deleteUser(const QString &username);
    void deleteLocation(int fID);

    QSharedPointer<Map> getMap();
    QSharedPointer<Region> getRegion(int id);
    QSharedPointer<Location> getLocation(int id);
    QSharedPointer<Patient> getPatient(int HCN);
    QSharedPointer<User> getUser(const QString &userName);
private:
    DataManager();

    QSqlDatabase database;
    QMutex mutex;
};

#endif // DATAMANAGER_H
