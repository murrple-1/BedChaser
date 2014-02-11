#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <QDateTime>

#include "config.h"
#include "object.h"
#include "map.h"
#include "location.h"
#include "patient.h"
#include "region.h"
#include "memento.h"
#include "user.h"
#include "database.h"
#include <QPixmap>
#include <list>

NS_START

class DataManager
{
public:

    static DataManager & getDataManager();

    void addObject(const Object & o) throw(Exception);
    void addPatient(const Patient & p) throw(Exception);
    void addUser(const User & u) throw(Exception);
    void addMemento(const Memento & m, const User & u) throw(Exception);
    void addLocation(const Location & l) throw(Exception);

    void addToWaitingList(const Region &, const Patient &) throw(Exception);
    void removeFromWaitingList(const Region &, const Patient &) throw(Exception);

    void updateObject(const Object & o) throw(Exception);
    void updatePatient(const Patient & p) throw(Exception);
    void updateUser(const User & u) throw(Exception);
    void updateLocation(const Location & l) throw(Exception);

    void deleteObject(const Object & o) throw(Exception);
    void deletePatient(const int HCN) throw(Exception);
    void deleteUser(const QString & username) throw(Exception);
    void deleteMemento(const QDateTime &) throw(Exception);
    void deleteLocation(const int fID) throw(Exception);

    Map * getMap() throw(Exception);
    Region * getRegion(const int ID) throw(Exception);
    QPixmap * getRegionImage(const int) throw(Exception);
    Location * getLocation(const int fID) throw(Exception);
    Patient * getPatient(const int HCN) throw(Exception);
    User * getUser(const QString & userName) throw(Exception);
    Memento  * getMemento(const QDateTime &) throw(Exception);

    enum OBJECTS {
        REGION,
        LOCATION,
        PATIENT,
        USER,
        MEMENTO
    };
    std::list<Object *> * getObjectList(const std::list<OBJECTS> &);
private:
    DataManager();
    ~DataManager();
};

NS_END

#endif // DATAMANAGER_H
