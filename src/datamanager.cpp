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

void DataManager::buildSelectQuery(QSqlQuery &query, const QString &selectClause, const QString &whereClause, const QMap<QString, QString> &whereParams, const QString &sortClause, int limit, int offset)
{
    QString queryString = QString("%1 ").arg(selectClause);

    if(!whereClause.isEmpty())
    {
        queryString.append(QString("WHERE %1 ").arg(whereClause));
    }

    if(!sortClause.isEmpty())
    {
        queryString.append(QString("ORDER BY %1 ").arg(sortClause));
    }

    if(limit >= 0)
    {
        queryString.append(QString("LIMIT %1 ").arg(limit));
    }

    if(offset >= 0)
    {
        queryString.append(QString("OFFSET %1 ").arg(offset));
    }

    query.prepare(queryString);

    foreach(const QString &whereParamKey, whereParams.keys())
    {
        query.bindValue(whereParamKey, whereParams.value(whereParamKey));
    }
}

QList<QSharedPointer<Region> > DataManager::getRegions(const QString &whereClause, const QMap<QString, QString> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `name` FROM \"regions\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<Region> > results;
        while(!query.next())
        {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            results.append(QSharedPointer<Region>(new Region(id, name)));
        }
        return results;
    }
    else
    {
        throw Exception("SQL statement error");
    }
}

QList<QSharedPointer<Facility> > DataManager::getFacilities(const QString &whereClause, const QMap<QString, QString> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `name`, `regions_id`, `x`, `y`, `number_of_acute_care_beds`, `number_of_complex_continuing_care_beds`, `number_of_long_term_care_beds` FROM \"facilities\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<Facility> > results;
        while(!query.next())
        {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            int x = query.value(2).toInt();\
            int y = query.value(3).toInt();
            int numberOfAcuteCareBeds = query.value(4).toInt();
            int numberOfComplexContinuingCareBeds = query.value(5).toInt();
            int numberOfLongTermCareBeds = query.value(6).toInt();
            QVariant regionId = query.value(7);
            results.append(QSharedPointer<Facility>(new Facility(id, name, x, y, numberOfAcuteCareBeds, numberOfComplexContinuingCareBeds, numberOfLongTermCareBeds, regionId)));
        }
        return results;
    }
    else
    {
        throw Exception("SQL statement error");
    }
}

QList<QSharedPointer<Patient> > DataManager::getPatients(const QString &whereClause, const QMap<QString, QString> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `health_care_number`, `name`, `required_care_type`, `receiving_care_type`, `receiving_care_facilities_id`, `receiving_care_date_admitted` FROM \"patients\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<Patient> > results;
        while(!query.next())
        {
            int id = query.value(0).toInt();
            int healthCareNumber = query.value(1).toInt();
            QString name = query.value(2).toString();
            CareType requiredCareType = (CareType) query.value(3).toInt();
            CareType receivingCareType = (CareType) query.value(4).toInt();
            QVariant receivingCareFacilityId = query.value(5);
            QDateTime receivingCareDateAdmitted;
            bool success;
            qlonglong _receivingCareDateAdmitted = query.value(6).toLongLong(&success);
            if(success)
            {
                receivingCareDateAdmitted.setMSecsSinceEpoch(_receivingCareDateAdmitted);
            }

            // Patient(const QVariant &careFacilityId, const QDateTime &dateAdmitted);
            results.append(QSharedPointer<Patient>(new Patient(id, healthCareNumber, name, requiredCareType, receivingCareType, receivingCareFacilityId, receivingCareDateAdmitted)));
        }
        return results;
    }
    else
    {
        throw Exception("SQL statement error");
    }
}

QList<QSharedPointer<User> > DataManager::getUsers(const QString &whereClause, const QMap<QString, QString> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `login`, `password_hash`, `type` FROM \"users\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<User> > results;
        while(!query.next())
        {
            int id = query.value(0).toInt();
            QString login = query.value(1).toString();
            QString passwordHash = query.value(2).toString();
            UserType userType = (UserType) query.value(3).toInt();
            results.append(QSharedPointer<User>(new User(id, login, passwordHash, userType)));
        }
        return results;
    }
    else
    {
        throw Exception("SQL statement error");
    }
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
    query.bindValue(":password", user.getPasswordHash());
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
    query.bindValue(":pword", user.getPasswordHash());
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
