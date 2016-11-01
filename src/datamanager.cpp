#include "datamanager.h"

#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QSqlError>

#include "region.h"
#include "facility.h"
#include "patient.h"
#include "exception.h"
#include "passwordhasher.h"

static const QString DEFAULT_ROOT_PASSWORD = "password";

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

    setupTables();
}

void DataManager::setupTables()
{
    QSqlQuery query(database);

    if(query.exec("SELECT `id` FROM \"users\" LIMIT 1"))
    {
        return;
    }

    QFile sqlSchemaFile("sqlschema.sql");
    if(!sqlSchemaFile.open(QFile::ReadOnly | QFile::Text))
    {
        throw Exception("SQL Schema file failed to open");
    }
    QString sqlSchema = sqlSchemaFile.readAll();
    sqlSchemaFile.close();
    foreach(const QString &statement, sqlSchema.split(';'))
    {
        QString _statement = statement.trimmed();
        if(!_statement.isEmpty())
        {
            if(!query.exec(_statement))
            {
                throw Exception(QString("SQL Schema execution failed: %1").arg(query.lastError().text()).toLatin1());
            }
        }
    }

    QString sqlCreateUser = "INSERT INTO \"users\" (`login`, `password_hash`, `type`) VALUES "
            "('root', :password_hash, 2);";

    if(query.prepare(sqlCreateUser))
    {
        QString passwordHash = PasswordHasher::sharedInstance().createHash(DEFAULT_ROOT_PASSWORD);
        query.bindValue(":password_hash", passwordHash);
        if(!query.exec())
        {
            throw Exception("SQL Create User failed");
        }
    }
    else
    {
        throw Exception("SQL Create User failed to prepare");
    }

    QFile sqlCreateFile("sqlcreate.sql");
    if(!sqlCreateFile.open(QFile::ReadOnly | QFile::Text))
    {
        throw Exception("SQL Create file failed to open");
    }
    QString sqlCreate = sqlCreateFile.readAll();
    sqlCreateFile.close();
    foreach(const QString &statement, sqlCreate.split(';'))
    {
        QString _statement = statement.trimmed();
        if(!_statement.isEmpty())
        {
            if(!query.exec(statement))
            {
                throw Exception(QString("SQL Create execution failed: %1").arg(query.lastError().text()).toLatin1());
            }
        }
    }
}

void DataManager::buildSelectQuery(QSqlQuery &query, const QString &selectClause, const QString &whereClause, const QMap<QString, QVariant> &whereParams, const QString &sortClause, int limit, int offset)
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

QList<QSharedPointer<Region> > DataManager::getRegions(const QString &whereClause, const QMap<QString, QVariant> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `name` FROM \"regions\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<Region> > results;
        while(query.next())
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

QList<QSharedPointer<Facility> > DataManager::getFacilities(const QString &whereClause, const QMap<QString, QVariant> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `name`, `regions_id`, `x`, `y`, `number_of_acute_care_beds`, `number_of_complex_continuing_care_beds`, `number_of_long_term_care_beds` FROM \"facilities\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<Facility> > results;
        while(query.next())
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

QList<QSharedPointer<Patient> > DataManager::getPatients(const QString &whereClause, const QMap<QString, QVariant> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `health_care_number`, `name`, `required_care_type`, `receiving_care_type`, `receiving_care_facilities_id`, `receiving_care_date_admitted` FROM \"patients\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<Patient> > results;
        while(query.next())
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

QList<QSharedPointer<User> > DataManager::getUsers(const QString &whereClause, const QMap<QString, QVariant> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `login`, `password_hash`, `type` FROM \"users\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<User> > results;
        while(query.next())
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

QList<QSharedPointer<WaitingListEntry> > DataManager::getWaitingListEntries(const QString &whereClause, const QMap<QString, QVariant> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `regions_id`, `patients_id`, `date_added` FROM \"waiting_list_regions_patients_mappings\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<WaitingListEntry> > results;
        while(query.next())
        {
            int regionId = query.value(0).toInt();
            int patientId = query.value(1).toInt();
            QDateTime dateAdded = query.value(2).toDateTime();
            results.append(QSharedPointer<WaitingListEntry>(new WaitingListEntry(regionId, patientId, dateAdded)));
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
    query.prepare("INSERT INTO \"patients\" (`health_care_number`, `name`, `required_care_type`, `receiving_care_type`, `receiving_care_facilities_id`, `receiving_care_date_admitted`) VALUES "
                  "(:health_care_number, :name, :required_care_type, :receiving_care_type, :receiving_care_facilities_id, :receiving_care_date_admitted)");
    query.bindValue(":health_care_number", patient.getHealthCardNumber());
    query.bindValue(":name", patient.getName());
    query.bindValue(":required_care_type", patient.getRequiredCareType());
    query.bindValue(":receiving_care_type", patient.getReceivingCareType());bool success;
    QVariant facilityId = patient.getReceivingCareFacilityId(&success);
    if(!success)
    {
        facilityId = QVariant();
    }
    query.bindValue(":receiving_care_facilities_id", facilityId);
    query.bindValue(":receiving_care_date_admitted", patient.getReceivingCareDateAdmitted());

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
    query.prepare("INSERT INTO \"users\" (`login`, `password_hash`, `type`) VALUES "
                  "(:login, :password_hash, :type)");
    query.bindValue(":login", user.getUsername());
    query.bindValue(":password_hash", user.getPasswordHash());
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
    query.prepare("INSERT INTO \"facilities\" (`name`, `regions_id`, `x`, `y`, `number_of_acute_care_beds`, `number_of_complex_continuing_care_beds`, `number_of_long_term_care_beds`) VALUES "
                  "(:name, :regions_id, :x, :y, :number_of_acute_care_beds, :number_of_complex_continuing_care_beds, :number_of_long_term_care_beds)");
    query.bindValue(":name", facility.getName());
    bool success;
    QVariant regionId = facility.getRegionId(&success);
    if(!success)
    {
        regionId = QVariant();
    }
    query.bindValue(":regions_id", regionId);
    query.bindValue(":x", facility.getX());
    query.bindValue(":y", facility.getY());
    query.bindValue(":number_of_acute_care_beds", facility.getNumberOfAcuteCareBeds());
    query.bindValue(":number_of_complex_continuing_care_beds", facility.getNumberOfComplexContinuingCareBeds());
    query.bindValue(":number_of_long_term_care_beds", facility.getNumberOfLongTermCareBeds());

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

void DataManager::addWaitingListEntry(const WaitingListEntry &waitingListEntry)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO \"waiting_list_regions_patients_mappings\" (`regions_id`, `patients_id`, `date_added`) VALUES "
                  "(:regions_id, :patients_id, :date_added)");
    query.bindValue(":regions_id", waitingListEntry.getRegionId());
    query.bindValue(":patients_id", waitingListEntry.getPatientId());
    query.bindValue(":date_added", waitingListEntry.getDateAdded());
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
    query.prepare("UPDATE \"patients\" "
                  "SET `name` = :name, `required_care_type` = :required_care_type, `receiving_care_type` = :receiving_care_type, `receiving_care_facilities_id` = :receiving_care_facilities_id, `receiving_care_date_admitted` = :receiving_care_date_admitted"
                  "WHERE `id` = :id");
    query.bindValue(":name", patient.getName());
    query.bindValue(":required_care_type", patient.getRequiredCareType());
    query.bindValue(":receiving_care_type", patient.getReceivingCareType());
    bool success;
    QVariant facilityId = patient.getReceivingCareFacilityId(&success);
    if(!success)
    {
        facilityId = QVariant();
    }
    query.bindValue(":receiving_care_facilities_id", facilityId);
    query.bindValue(":receiving_care_date_admitted", patient.getReceivingCareDateAdmitted());


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
    query.prepare("UPDATE \"users\" "
                  "SET `password_hash` = :password_hash, `type` = :type "
                  "WHERE `id` = :id");
    query.bindValue(":password_hash", user.getPasswordHash());
    query.bindValue(":type", user.getUserType());
    query.bindValue(":id", user.getId(NULL));

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
    query.prepare("UPDATE \"facilities\" "
                  "SET `name` = :name, `regions_id` = :regions_id, `x` = :x, `y` = :y, `number_of_acute_care_beds` = :number_of_acute_care_beds, `number_of_complex_continuing_care_beds` = :number_of_complex_continuing_care_beds, `number_of_long_term_care_beds` = :number_of_long_term_care_beds "
                  "WHERE ID = :id");
    query.bindValue(":name", facility.getName());
    bool success;
    QVariant regionId = facility.getRegionId(&success);
    if(!success)
    {
        regionId = QVariant();
    }
    query.bindValue(":regions_id", regionId);
    query.bindValue(":x", facility.getX());
    query.bindValue(":y", facility.getY());
    query.bindValue(":number_of_acute_care_beds", facility.getNumberOfAcuteCareBeds());
    query.bindValue(":number_of_complex_continuing_care_beds", facility.getNumberOfComplexContinuingCareBeds());
    query.bindValue(":number_of_long_term_care_beds", facility.getNumberOfLongTermCareBeds());
    query.bindValue(":id", facility.getID());

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

void DataManager::deleteWaitingListEntry(const WaitingListEntry &waitingListEntry)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("DELETE FROM \"users\" "
                  "WHERE `regions_id` = :regions_id AND `patients_id` = :patients_id");
    query.bindValue(":regions_id", waitingListEntry.getRegionId());
    query.bindValue(":patients_id", waitingListEntry.getPatientId());

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
