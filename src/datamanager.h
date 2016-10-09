#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

#include <QSqlDatabase>
#include <QMutex>

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

    Map * getMap();
    Region * getRegion(int id);
    Location * getLocation(int fID);
    Patient * getPatient(int HCN);
    User * getUser(const QString &userName);
private:
    DataManager();

    QSqlDatabase database;
    QMutex mutex;
};

#endif // DATAMANAGER_H
