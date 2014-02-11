#include "database.h"
#include "exception.h"
#include <QFile>
#include "QsLog.h"
#include "QsLogDest.h"

NS_START

void readSQLScript(QFile) throw(Exception);

Database::Database()
{}

void Database::startDatabase(const QString m_dBName, const QString path) throw(Exception)
{
    if(!QFile(path).exists())
    {
        createNewDatabase(m_dBName, path);
        Init(m_dBName);
    }
    else
    {
        createNewDatabase(m_dBName, path);
    }
}

void Database::createNewDatabase(const QString m_dBName, const QString path) throw(Exception)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", m_dBName);
    db.setHostName("localhost");
    db.setDatabaseName(path);

    if (!db.open())
    {
        QLOG_ERROR() << "Database connection to " << path << " failed";
        throw Exception("Connection to database failed", "Database::createNewDatabase");
    }

    QLOG_INFO() << "Database connection to " << path << " established";
}

void Database::Init(const QString m_dBName) throw(Exception)
{
    QSqlDatabase db = getOpenDatabase(m_dBName);
    QSqlQuery Query(db);
    // Create Region table first, since it is a standalone table
    // protocol sends only ID. Name and Image blob need to be created by us

    db.transaction();
    Query.exec("DROP TABLE IF EXISTS Region;");
    Query.exec("CREATE TABLE Region("
               "ID INTEGER primary key NOT NULL, "
               "Name VARCHAR(30) NOT NULL, "
               "ImageFile TEXT NOT NULL);");
    if(!db.commit()) {
        QLOG_ERROR() << "Region table failed " << db.lastError().text();
        throw Exception("Region table failed", "Database::Init");
    }
    InitRegions();
    QLOG_INFO() << "Region table created successfully";

    // Create User table as a standalone table
    // nothing to do with protocol, this is all local stuff to our session
    db.transaction();
    Query.exec("DROP TABLE IF EXISTS Users;");
    Query.exec("CREATE TABLE Users("
               "Username VARCHAR(20) primary key NOT NULL, "
               "Password VARCHAR(20), "
               "security_group INTEGER NOT NULL);");
    if(!db.commit()) {
        throw Exception("User table failed", "Database::Init");
    }
    InitUsers();
    QLOG_INFO() << "User table created successfully";

    // Create Memento table to dependencies on Users table being created successfully
    // nothing to do with protocol, this is our persistent binary storage mechanism
    db.transaction();
    Query.exec("DROP TABLE IF EXISTS Memento;");
    Query.exec("CREATE TABLE Memento("
               "Timestamp TEXT primary key NOT NULL, "
               "Created_By_User TEXT NOT NULL, "
               "Data TEXT NOT NULL, "
               "foreign key (Created_By_User) references Users (Username));");
    if(!db.commit()) {
        QLOG_ERROR() << "Memento table failed " <<  db.lastError().text();
        throw Exception("Memento table failed", "Database::Init");
    }
    QLOG_INFO() << "Memento table created successfully";

    // Create Location table with dependency on Region table being created successfully
    // confirmed to be same fields as protocol receive
    db.transaction();
    Query.exec("DROP TABLE IF EXISTS Location;");
    Query.exec("CREATE TABLE Location("
               "ID INTEGER NOT NULL, "
               "Name VARCHAR(25) NOT NULL, "
               "X INTEGER NOT NULL, "
               "Y INTEGER NOT NULL, "
               "AC INTEGER NOT NULL, "
               "CCC INTEGER NOT NULL, "
               "LTC INTEGER NOT NULL, "
               "Region INTEGER NOT NULL, "
               "primary key (ID, Region), "
               "foreign key (Region) references Region (ID));");
    if(!db.commit()) {
        QLOG_ERROR() << "Location table failed " <<  db.lastError().text();
        throw Exception("Location table failed", "Database::Init");
    }
    InitLocations();
    QLOG_INFO() << "Location table created successfully";

    // Create Patients table with dependency on Location table being created successfully
    db.transaction();
    Query.exec("DROP TABLE IF EXISTS Patients;");
    Query.exec("CREATE TABLE Patients("
               "HCN INTEGER primary key NOT NULL, "
               "First_Name VARCHAR(15) NOT NULL, "
               "Last_Name VARCHAR(25) NOT NULL, "
               "Care_Req VARCHAR(3) NOT NULL, "
               "Care_Rec VARCHAR(3), "
               "Admit_Date DATE, "
               "WL_Date DATE, "
               "Location INTEGER, "
               "foreign key (Location) references Location (ID));");
    if(!db.commit()) {
        QLOG_ERROR() << "Patients' table failed " <<  db.lastError().text();
        throw Exception("Patients' table failed", "Database::Init");
    }
    InitPatients();
    QLOG_INFO() << "Patients' table created successfully";

    // Create WaitingList table with dependencies on Location and Patient tables being created successfully
    // confirmed to be same as protocol schema
    db.transaction();
    Query.exec("DROP TABLE IF EXISTS WaitingList;");
    Query.exec("CREATE TABLE WaitingList("
               "Patient INTEGER NOT NULL, "
               "Region INTEGER NOT NULL, "
               "Timestamp TEXT NOT NULL, "
               "CONSTRAINT pk primary key (Patient, Region), "
               "CONSTRAINT fk1 foreign key (Patient) references Patients (HCN), "
               "CONSTRAINT fk2 foreign key (Region) references Region (ID));");
    if(!db.commit()) {
        QLOG_ERROR() << "waitingList table failed " <<  db.lastError().text();
        throw Exception("waitingList table failed", "Database::Init");
    }
    QLOG_INFO() << "waitingList table created successfully";
}

void Database::InitRegions() throw(Exception)
{
    QLOG_INFO() << "Populating the Region table with default static data";

    QFile file("../deplib/region_gen.sql");
    readSQLScript(file);

}

void Database::InitUsers() throw(Exception)
{
    QLOG_INFO() << "Populating the Users table with initial user data";

    QFile file("../deplib/user_gen.sql");
    readSQLScript(file);
}

void Database::InitLocations() throw(Exception)
{
    QLOG_INFO() << "Populating the Location table with initial data...";

    QFile file("../deplib/location_gen.sql");
    readSQLScript(file);
}

void readSQLScript(QFile file) throw(Exception)
{
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        throw Exception("Could not open file " + file.fileName().toStdString(), "readSqlScript");
    }
    else
    {
        QSqlDatabase db = getOpenDatabase();
        QSqlQuery query(db);

        while(!file.atEnd())
        {
            if(!query.exec(file.readLine()))
            {
                throw Exception("Could not execute SQL script", "readSQLScript");
            }
        }
        file.close();
    }
}

QSqlDatabase Database::getOpenDatabase(const QString dbName)
{
    return QSqlDatabase::database(dbName);
}

NS_END
