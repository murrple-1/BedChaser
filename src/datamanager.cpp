#include "datamanager.h"

#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "region.h"
#include "facility.h"
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

void DataManager::setupTables()
{

}

void DataManager::addPatient(const Patient &patient)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO Patients (HCN, Name, Care_Req, Care_Rec, WL_Date, Admit_Date, Facility) VALUES (:hcn, :name, :reqcare, :reccare, :admitDate, :loc)");
    query.bindValue(":hcn", patient.getHealthCardNumber());
    query.bindValue(":name", patient.getName());
    query.bindValue(":reqcare", patient.getRequiredCareType());
    query.bindValue(":reccare", patient.getReceivingCareType());
    query.bindValue(":admitDate", patient.getReceivingCareDateAdmitted());
    bool success;
    QVariant facilityId = patient.getReceivingCareFacilityId(&success);
    if(!success)
    {
        facilityId = QVariant();
    }
    query.bindValue(":loc", facilityId);

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
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO Users (Username, Password, security_group) VALUES (:uname, :password, :type)");
    query.bindValue(":uname", user.getUserName());
    query.bindValue(":password", user.getPassword());
    query.bindValue(":type", user.getUserType());
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

void DataManager::addFacility(const Facility &facility)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO Facility (ID, Name, X, Y, AC, CCC, LTC, Region) VALUES (:id, :name, :x, :y, :ac, :ccc, :ltc, :region)");
    query.bindValue(":id", facility.getID());
    query.bindValue(":name", facility.getName());
    query.bindValue(":x", facility.getX());
    query.bindValue(":y", facility.getY());
    query.bindValue(":ac", facility.getNumberOfAcuteCareBeds());
    query.bindValue(":ccc", facility.getNumberOfComplexContinuingCareBeds());
    query.bindValue(":ltc", facility.getNumberOfLongTermCareBeds());
    bool success;
    QVariant regionId = facility.getRegionId(&success);
    if(!success)
    {
        regionId = QVariant();
    }
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

void DataManager::updatePatient(const Patient &patient)
{


    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("UPDATE Patients SET Name = :name, Care_Req = :reqcare, Care_Rec = :reccare, Admit_Date = :ad, Facility = :loc WHERE HCN = :hcn");
    query.bindValue(":hcn", patient.getHealthCardNumber());
    query.bindValue(":name", patient.getName());
    query.bindValue(":reqcare", patient.getRequiredCareType());
    query.bindValue(":reccare", patient.getReceivingCareType());
    query.bindValue(":ad", patient.getReceivingCareDateAdmitted());
    bool success;
    QVariant facilityId = patient.getReceivingCareFacilityId(&success);
    if(!success)
    {
        facilityId = QVariant();
    }
    query.bindValue(":loc", facilityId);

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
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("UPDATE Users SET Password = :pword, security_group = :sgroup WHERE Username = :uname");
    query.bindValue(":uname", user.getUserName());
    query.bindValue(":pword", user.getPassword());
    query.bindValue(":sgroup", user.getUserType());

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

void DataManager::updateFacility(const Facility &facility)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("UPDATE Facility SET name = :name, X = :x, Y = :y, AC = :ac, CCC = :ccc, LTC = :ltc, region = :reg WHERE ID = :id");
    query.bindValue(":id", facility.getID());
    query.bindValue(":name", facility.getName());
    query.bindValue(":x", facility.getX());
    query.bindValue(":y", facility.getY());
    query.bindValue(":ac", facility.getNumberOfAcuteCareBeds());
    query.bindValue(":ccc", facility.getNumberOfComplexContinuingCareBeds());
    query.bindValue(":ltc", facility.getNumberOfLongTermCareBeds());
    bool success;
    QVariant regionId = facility.getRegionId(&success);
    if(!success)
    {
        regionId = QVariant();
    }
    query.bindValue(":reg", regionId);

    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception("updating the facility failed");
    }
}

QSharedPointer<Region> DataManager::getRegion(int ID)
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
        return QSharedPointer<Region>();
    }

    QString name = query.value(0).toString();
    Region *region = new Region(ID, name);

    return QSharedPointer<Region>(region);
}

QSharedPointer<Facility> DataManager::getFacility(int fID)
{
    QSqlQuery query(database);

    query.prepare("SELECT ID, Name, X, Y, AC, CCC, LTC, Region FROM Facility WHERE ID = :lid");
    query.bindValue(":lid", fID);
    if(query.exec())
    {
        if(!query.first())
        {
            return QSharedPointer<Facility>();
        }

        QString Name = query.value(1).toString();
        float X = query.value(2).toFloat();
        float Y = query.value(3).toFloat();
        int AC = query.value(4).toInt();
        int CCC = query.value(5).toInt();
        int LTC = query.value(6).toInt();
        QVariant regionId = query.value(7);
        Facility *facility = new Facility(fID, Name, X, Y, AC, CCC, LTC, regionId);

        return QSharedPointer<Facility>(facility);
    }
    else
    {
        throw Exception("SQL statement error:");
    }
}

QSharedPointer<Patient> DataManager::getPatient(int healthCareNumber)
{
    QSqlQuery query(database);
    query.prepare("SELECT HCN, Name, Care_Req, Care_Rec, Admit_Date, Facility FROM Patients WHERE HCN = :hcn");
    query.bindValue(":hcn", healthCareNumber);
    if(!query.exec())
    {
        throw Exception("SQL statement error");
    }
    if(!query.first())
    {
        return QSharedPointer<Patient>();
    }

    QString name = query.value(1).toString();
    CareType requiredCareType = CareType(query.value(2).toString().toInt());
    CareType receivedCareType = CareType(query.value(4).toString().toInt());
    QVariant facilityId = query.value(7);
    QDateTime admitDate = query.value(5).toDateTime();
    Patient *patient = new Patient(QVariant(), healthCareNumber, name, requiredCareType, receivedCareType, facilityId, admitDate);

    return QSharedPointer<Patient>(patient);
}

QSharedPointer<User> DataManager::getUser(const QString &userName)
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
            User *user = new User(QVariant(), userName, pass, UserType(sec_group));

            return QSharedPointer<User>(user);
        }
        else
        {
            return QSharedPointer<User>();
        }
    }
    else
    {
        throw Exception("SQL statement error:");
    }
}
