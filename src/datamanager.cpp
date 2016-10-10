#include "datamanager.h"

#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "region.h"
#include "location.h"
#include "patient.h"
#include "exception.h"

DataManager & DataManager::sharedInstance()
{
    static DataManager dm;
    return dm;
}

DataManager::DataManager()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("data.db");

    if(!database.open())
    {
        // TODO better messages
        throw Exception("Database failed to open");
    }
}

void DataManager::addPatient(const Patient &patient)
{
    int HCN = patient.getHealthCardNumber();
    QVariant first_name = patient.getFirstName();
    QVariant last_name = patient.getLastName();
    int rec_care = patient.getRecCareType();
    int req_care = patient.getReqCareType();
    const QDateTime &WL_Date = patient.getDateAddedToWaitingList();
    const QDateTime &admit_date = patient.getDateAdmitted();

    bool success;
    QVariant locationId = patient.getCareLocationId(&success);
    if(!success)
    {
        locationId = QVariant();
    }

    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO Patients (HCN, First_Name, Last_Name, Care_Req, Care_Rec, WL_Date, Admit_Date, Location) VALUES (:hcn, :fname, :lname, :reqcare, :reccare, :addDate, :admitDate, :loc)");
    query.bindValue(":hcn", HCN);
    query.bindValue(":fname", first_name);
    query.bindValue(":lname", last_name);
    query.bindValue(":reqcare", req_care);
    query.bindValue(":reccare", rec_care);
    query.bindValue(":addDate", WL_Date);
    query.bindValue(":admitDate", admit_date);
    query.bindValue(":loc", locationId);

    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("SQL query failed");
    }
}

void DataManager::addUser(const User &user)
{
    const QString &username = user.getUserName();
    const QString &password = user.getPassword();
    USERTYPE usertype = user.getUserType();

    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO Users (Username, Password, security_group) VALUES (:uname, :password, :type)");
    query.bindValue(":uname", username);
    query.bindValue(":password", password);
    query.bindValue(":type", usertype);
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("SQL query failed");
    }
}

void DataManager::addLocation(const Location &location)
{
    int id = location.getID();
    const QString &name = location.getName();
    int x = location.getX();
    int y = location.getY();
    int AC = location.getACBeds();
    int CCC = location.getCCCBeds();
    int LTC = location.getLTCBeds();

    bool success;
    QVariant regionId = location.getRegionId(&success);
    if(!success)
    {
        regionId = QVariant();
    }

    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO Location (ID, Name, X, Y, AC, CCC, LTC, Region) VALUES (:id, :name, :x, :y, :ac, :ccc, :ltc, :region)");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":x", x);
    query.bindValue(":y", y);
    query.bindValue(":ac", AC);
    query.bindValue(":ccc", CCC);
    query.bindValue(":ltc", LTC);
    query.bindValue(":region", regionId);
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("SQL query failed");
    }
}

void DataManager::addToWaitingList(const Region &region, const Patient &patient)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO WaitingList (Patient, Region, Timestamp) VALUES (:pat, :reg, :ts)");
    query.bindValue(":pat", patient.getHealthCardNumber());
    query.bindValue(":reg", region.getID());
    query.bindValue(":ts", QDateTime::currentDateTime());
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("SQL query failed");
    }
}

void DataManager::removeFromWaitingList(const Region &region, const Patient &patient)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("DELETE FROM WaitingList WHERE Patient = :pat AND Region = :reg");
    query.bindValue(":pat", patient.getHealthCardNumber());
    query.bindValue(":reg", region.getID());
    if(query.exec())
    {
        database.commit();
        mutex.lock();
    }
    else
    {
        database.rollback();
        mutex.lock();
        throw Exception("SQL query failed");
    }
}

void DataManager::updatePatient(const Patient &patient)
{
    int hcn = patient.getHealthCardNumber();
    const QString &first_name = patient.getFirstName();
    const QString &last_name = patient.getLastName();
    int care_req = patient.getReqCareType();
    int care_rec = patient.getRecCareType();
    const QDateTime &wl_date = patient.getDateAddedToWaitingList();
    const QDateTime &admit_date = patient.getDateAdmitted();

    bool success;
    QVariant locationId = patient.getCareLocationId(&success);
    if(!success)
    {
        locationId = QVariant();
    }

    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("UPDATE Patients SET First_Name = :fname, Last_Name = :lname, Care_Req = :reqcare, Care_Rec = :reccare, WL_Date = :wld, Admit_Date = :ad, Location = :loc WHERE HCN = :hcn");
    query.bindValue(":fname", first_name);
    query.bindValue(":lname", last_name);
    query.bindValue(":reqcare", care_req);
    query.bindValue(":reccare", care_rec);
    query.bindValue(":wld", wl_date);
    query.bindValue(":ad", admit_date);
    query.bindValue(":loc", locationId);
    query.bindValue(":hcn", hcn);
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("updating the patient failed");
    }
}

void DataManager::updateUser(const User &user)
{
    const QString &username = user.getUserName();
    const QString &password = user.getPassword();
    USERTYPE security_group = user.getUserType();

    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("UPDATE Users SET Password = :pword, security_group = :sgroup WHERE Username = :uname");
    query.bindValue(":pword", password);
    query.bindValue(":sgroup", security_group);
    query.bindValue(":uname", username);
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("updating the user failed");
    }
}

void DataManager::updateLocation(const Location &location)
{
    int ID = location.getID();

    const QString &name = location.getName();
    int x = location.getX();
    int y = location.getY();
    int ac = location.getACBeds();
    int ccc = location.getCCCBeds();
    int ltc = location.getLTCBeds();

    bool success;
    QVariant regionId = location.getRegionId(&success);
    if(!success)
    {
        regionId = QVariant();
    }

    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("UPDATE Location SET name = :name, X = :x, Y = :y, AC = :ac, CCC = :ccc, LTC = :ltc, region = :reg WHERE ID = :id");
    query.bindValue(":name", name);
    query.bindValue(":x", x);
    query.bindValue(":y", y);
    query.bindValue(":ac", ac);
    query.bindValue(":ccc", ccc);
    query.bindValue(":ltc", ltc);
    query.bindValue(":reg", regionId);
    query.bindValue(":id", ID);
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("updating the location failed");
    }
}

void DataManager::deletePatient(int HCN)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("DELETE FROM Patients WHERE HCN = :hcn");
    query.bindValue(":hcn", HCN);
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("deleting the patient failed");
    }
}

void DataManager::deleteUser(const QString &username)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("DELETE FROM Users WHERE Username = :user");
    query.bindValue(":user", username);
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("deleting the user failed");
    }
}

void DataManager::deleteLocation(int ID)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("DELETE FROM Location WHERE Username = :id");
    query.bindValue(":id", ID);
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("deleting the location failed");
    }
}

Map * DataManager::getMap()
{
    Map *map = new Map();

    QSqlQuery query(database);

    query.prepare("SELECT ID FROM Region");
    if(query.exec())
    {
        while(query.next())
        {
            int ID = query.value(0).toInt();
            map->addRegionId(ID);
        }
        return map;
    }
    else
    {
        throw Exception("SQL statement error");
    }
}

Region * DataManager::getRegion(int ID)
{
    QSqlQuery query(database);
    query.prepare("SELECT Name FROM Region WHERE ID = :id");
    query.bindValue(":id", ID);
    if(!query.exec())
    {
        throw Exception("SQL statement error");
    }
    if(!query.first())
    {
        return NULL;
    }

    QString name = query.value(0).toString();
    Region *region = new Region(ID, name);

    query.prepare("SELECT ID FROM Location WHERE Region = :reg");
    query.bindValue(":reg", ID);
    if(!query.exec())
    {
        throw Exception("SQL statement error");
    }
    while(query.next())
    {
        region->addLocationId(query.value(0).toInt());
    }

    query.prepare("SELECT Patient FROM WaitingList WHERE Region = :reg");
    query.bindValue(":reg", ID);
    if(!query.exec())
    {
        throw Exception("SQL statement error");
    }
    while(query.next())
    {
        region->addWaitingListPatientId(query.value(0).toInt());
    }

    return region;
}

Location * DataManager::getLocation(int fID)
{
    QSqlQuery query(database);

    query.prepare("SELECT ID, Name, X, Y, AC, CCC, LTC, Region FROM Location WHERE ID = :lid");
    query.bindValue(":lid", fID);
    if(query.exec())
    {
        if(!query.first())
        {
            return NULL;
        }

        QString Name = query.value(1).toString();
        float X = query.value(2).toFloat();
        float Y = query.value(3).toFloat();
        int AC = query.value(4).toInt();
        int CCC = query.value(5).toInt();
        int LTC = query.value(6).toInt();
        Location *location = new Location(fID, Name, X, Y, AC, CCC, LTC);

        if(!query.value(7).isNull())
        {
            QVariant regionId = query.value(7).toInt();
            location->setRegionId(regionId);
        }

        query.prepare("SELECT HCN FROM Patients WHERE Location = :id");
        query.bindValue(":id", fID);
        if(!query.exec())
        {
            throw Exception("SQL statement error");
        }
        while(query.next())
        {
            location->addPatientInCareId(query.value(0).toInt());
        }
        return location;
    }
    else
    {
        throw Exception("SQL statement error:");
    }
}

Patient * DataManager::getPatient(int HCN)
{
    QSqlQuery query(database);
    query.prepare("SELECT HCN, First_Name, Last_Name, Care_Req, Care_Rec, Admit_Date, WL_Date, Location FROM Patients WHERE HCN = :hcn");
    query.bindValue(":hcn", HCN);
    if(!query.exec())
    {
        throw Exception("SQL statement error");
    }
    if(!query.first())
    {
        return NULL;
    }

    QString fname = query.value(1).toString();
    QString lname = query.value(2).toString();
    CareType req_care = CareType(query.value(3).toString().toInt());
    Patient *patient = new Patient(HCN, fname, lname, req_care);

    CareType rec_care = CareType(query.value(4).toString().toInt());
    patient->setReceivedCareType(rec_care);

    if(!query.value(5).isNull())
    {
        QDateTime admitDate = query.value(5).toDateTime();
        patient->setDateAdmitted(admitDate);
    }

    if(!query.value(6).isNull())
    {
        QDateTime wlDate = query.value(6).toDateTime();
        patient->setDateAddedToWaitingList(wlDate);
    }

    if(!query.value(7).isNull())
    {
        int locationId = query.value(7).toInt();
        patient->setCareLocationId(locationId);
    }

    query.prepare("SELECT Region FROM WaitingList WHERE Patient = :pat");
    query.bindValue(":pat", HCN);
    if(query.exec())
    {
        while(query.next())
        {
            patient->addWaitingRegionId(query.value(0).toInt());
        }

        return patient;
    }
    else
    {
        throw Exception("SQL statement error");
    }
}

User * DataManager::getUser(const QString &userName)
{
    QSqlQuery query(database);
    query.prepare("SELECT Username, Password, security_group FROM Users WHERE Username = :user");
    query.bindValue(":user", userName);
    if(query.exec())
    {
        if(query.first())
        {
            QString pass = query.value(1).toString();
            int sec_group = query.value(2).toInt();
            User *user = new User(userName, pass, USERTYPE(sec_group));

            return user;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        throw Exception("SQL statement error:");
    }
}
