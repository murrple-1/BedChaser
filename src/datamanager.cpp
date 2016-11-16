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
                throw Exception(QString(query.lastError().text()).toLatin1());
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
            throw Exception(query.lastError().text().toLatin1());
        }
    }
    else
    {
        throw Exception(query.lastError().text().toLatin1());
    }

#ifdef QT_DEBUG
    QFile sqlCreateFile("sqlcreate.dev.sql");
#else
    QFile sqlCreateFile("sqlcreate.sql");
#endif
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
                throw Exception(QString(query.lastError().text()).toLatin1());
            }
        }
    }

#ifdef QT_DEBUG
    qsrand(QDateTime::currentMSecsSinceEpoch());

    QList<QSharedPointer<Patient> > patients = getPatients();

    QList<QSharedPointer<Region> > regions = getRegions();

    QDateTime now = QDateTime::currentDateTimeUtc();
    for(int i = 0; i < 30; i++)
    {
        int patientsIndex = qrand() % patients.count();
        int regionsIndex = qrand() % regions.count();

        QSharedPointer<Patient> patient = patients.at(patientsIndex);
        QSharedPointer<Region> region = regions.at(regionsIndex);

        WaitingListEntry waitingListEntry(region->getID(), patient->getID(), now);
        try
        {
            addWaitingListEntry(waitingListEntry);
        }
        catch(Exception &)
        {
            //  do nothing
        }
    }

    QList<QSharedPointer<Facility> > facilities = getFacilities();
    for(int i = 0; i < 15; i++)
    {
        int patientsIndex = qrand() % patients.count();
        int facilitiesIndex = qrand() % facilities.count();

        QSharedPointer<Patient> patient = patients.at(patientsIndex);
        QSharedPointer<Facility> facility = facilities.at(facilitiesIndex);

        CareType requiredCareType = CareTypeNone;
        int _requiredCareType = qrand() % 3;
        switch(_requiredCareType)
        {
        case 0:
            requiredCareType = CareTypeAcuteCare;
            break;
        case 1:
            requiredCareType = CareTypeComplexContinuingCare;
            break;
        case 2:
            requiredCareType = CareTypeLongTermCare;
            break;
        }

        patient->setReceivingCareType(requiredCareType);
        patient->setReceivingCareFacilityId(facility->getID());
        patient->setDateAdmitted(now);

        updatePatient(*patient);
    }
#endif
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

        if(offset >= 0)
        {
            queryString.append(QString("OFFSET %1 ").arg(offset));
        }
    }

    query.prepare(queryString);

    foreach(const QString &whereParamKey, whereParams.keys())
    {
        query.bindValue(whereParamKey, whereParams.value(whereParamKey));
    }
}

QList<QSharedPointer<Region> > DataManager::getRegions(const QString &whereClause, const QMap<QString, QVariant> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `name`, `map_x_offset`, `map_y_offset`, `sub_map_file_path` FROM \"regions\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<Region> > results;
        while(query.next())
        {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            int mapXOffset = query.value(2).toInt();
            int mapYOffset = query.value(3).toInt();
            QString subMapFileInfo = query.value(4).toString();
            results.append(QSharedPointer<Region>(new Region(id, name, QFileInfo(subMapFileInfo), QPoint(mapXOffset, mapYOffset))));
        }
        return results;
    }
    else
    {
        throw Exception(query.lastError().text().toLatin1());
    }
}

QList<QSharedPointer<Facility> > DataManager::getFacilities(const QString &whereClause, const QMap<QString, QVariant> &whereParams, const QString &sortClause, int limit, int offset)
{
    static QString selectClause = "SELECT `id`, `name`, `regions_id`, `map_x_offset`, `map_y_offset`, `number_of_acute_care_beds`, `number_of_complex_continuing_care_beds`, `number_of_long_term_care_beds` FROM \"facilities\"";

    QSqlQuery query(database);
    buildSelectQuery(query, selectClause, whereClause, whereParams, sortClause, limit, offset);

    if(query.exec())
    {
        QList<QSharedPointer<Facility> > results;
        while(query.next())
        {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QVariant regionId = query.value(2);
            int mapXOffset = query.value(3).toInt();\
            int mapYOffset = query.value(4).toInt();
            int numberOfAcuteCareBeds = query.value(5).toInt();
            int numberOfComplexContinuingCareBeds = query.value(6).toInt();
            int numberOfLongTermCareBeds = query.value(7).toInt();
            results.append(QSharedPointer<Facility>(new Facility(id, name, QPoint(mapXOffset, mapYOffset), numberOfAcuteCareBeds, numberOfComplexContinuingCareBeds, numberOfLongTermCareBeds, regionId)));
        }
        return results;
    }
    else
    {
        throw Exception(query.lastError().text().toLatin1());
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
        throw Exception(query.lastError().text().toLatin1());
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
        throw Exception(query.lastError().text().toLatin1());
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
        throw Exception(query.lastError().text().toLatin1());
    }
}

QVariant DataManager::addPatient(const Patient &patient)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO \"patients\" (`health_care_number`, `name`, `required_care_type`, `receiving_care_type`, `receiving_care_facilities_id`, `receiving_care_date_admitted`) VALUES "
                  "(:health_care_number, :name, :required_care_type, :receiving_care_type, :receiving_care_facilities_id, :receiving_care_date_admitted)");
    query.bindValue(":health_care_number", patient.getHealthCareNumber());
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
        return query.lastInsertId();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception(query.lastError().text().toLatin1());
    }
}

QVariant DataManager::addUser(const User &user)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO \"users\" (`login`, `password_hash`, `type`) VALUES "
                  "(:login, :password_hash, :type)");
    query.bindValue(":login", user.getUsername());
    query.bindValue(":password_hash", user.getPasswordHash());
    query.bindValue(":type", user.getType());
    if(query.exec())
    {
        database.commit();
        mutex.unlock();
        return query.lastInsertId();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception(query.lastError().text().toLatin1());
    }
}

QVariant DataManager::addFacility(const Facility &facility)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("INSERT INTO \"facilities\" (`name`, `regions_id`, `map_x_offset`, `map_y_offset`, `number_of_acute_care_beds`, `number_of_complex_continuing_care_beds`, `number_of_long_term_care_beds`) VALUES "
                  "(:name, :regions_id, :map_x_offset, :map_y_offset, :number_of_acute_care_beds, :number_of_complex_continuing_care_beds, :number_of_long_term_care_beds)");
    query.bindValue(":name", facility.getName());
    bool success;
    QVariant regionId = facility.getRegionId(&success);
    if(!success)
    {
        regionId = QVariant();
    }
    query.bindValue(":regions_id", regionId);
    const QPoint &mapOffset = facility.getMapOffset();
    query.bindValue(":map_x_offset", mapOffset.x());
    query.bindValue(":map_y_offset", mapOffset.y());
    query.bindValue(":number_of_acute_care_beds", facility.getNumberOfAcuteCareBeds());
    query.bindValue(":number_of_complex_continuing_care_beds", facility.getNumberOfComplexContinuingCareBeds());
    query.bindValue(":number_of_long_term_care_beds", facility.getNumberOfLongTermCareBeds());

    if(query.exec())
    {
        database.commit();
        mutex.unlock();
        return query.lastInsertId();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception(query.lastError().text().toLatin1());
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
        throw Exception(query.lastError().text().toLatin1());
    }
}

void DataManager::updatePatient(const Patient &patient)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("UPDATE \"patients\" "
                  "SET `name` = :name, `required_care_type` = :required_care_type, `receiving_care_type` = :receiving_care_type, `receiving_care_facilities_id` = :receiving_care_facilities_id, `receiving_care_date_admitted` = :receiving_care_date_admitted "
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
    query.bindValue(":receiving_care_date_admitted", patient.getReceivingCareDateAdmitted().toMSecsSinceEpoch());
    query.bindValue(":id", patient.getID());

    if(query.exec())
    {
        database.commit();
        mutex.unlock();
    }
    else
    {
        database.rollback();
        mutex.unlock();
        throw Exception(query.lastError().text().toLatin1());
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
    query.bindValue(":type", user.getType());
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
        throw Exception(query.lastError().text().toLatin1());
    }
}

void DataManager::updateFacility(const Facility &facility)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("UPDATE \"facilities\" "
                  "SET `name` = :name, `regions_id` = :regions_id, `map_x_offset` = :map_x_offset, `map_y_offset` = :map_y_offset, `number_of_acute_care_beds` = :number_of_acute_care_beds, `number_of_complex_continuing_care_beds` = :number_of_complex_continuing_care_beds, `number_of_long_term_care_beds` = :number_of_long_term_care_beds "
                  "WHERE ID = :id");
    query.bindValue(":name", facility.getName());
    bool success;
    QVariant regionId = facility.getRegionId(&success);
    if(!success)
    {
        regionId = QVariant();
    }
    query.bindValue(":regions_id", regionId);
    const QPoint &mapOffset = facility.getMapOffset();
    query.bindValue(":map_x_offset", mapOffset.x());
    query.bindValue(":map_y_offset", mapOffset.y());
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
        throw Exception(query.lastError().text().toLatin1());
    }
}

void DataManager::deleteWaitingListEntry(const WaitingListEntry &waitingListEntry)
{
    QSqlQuery query(database);

    mutex.lock();

    database.transaction();
    query.prepare("DELETE FROM \"waiting_list_regions_patients_mappings\" "
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
        throw Exception(query.lastError().text().toLatin1());
    }
}
