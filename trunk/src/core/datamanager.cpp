#include "datamanager.h"
#include "QsLog.h"
#include "QsLogDest.h"
#include "../utils/stringbuilder.h"
#include <iostream>

#include "regionproxy.h"
#include "regionobject.h"
#include "locationproxy.h"
#include "locationobject.h"
#include "patientproxy.h"
#include "patientobject.h"

NS_START

        DataManager & DataManager::getDataManager()
{
    static DataManager dm;
    return dm;
}

DataManager::DataManager()
{}

DataManager::~DataManager()
{}

void DataManager::addObject(const Object & o) throw(Exception)
{
    const Patient * p = dynamic_cast<const Patient *>(&o);
    if(p != NULL)
    {
        addPatient(*p);
        return;
    }

    const Location * l = dynamic_cast<const Location *>(&o);
    if(l != NULL)
    {
        addLocation(*l);
        return;
    }

    const User * u = dynamic_cast<const User *>(&o);
    if(u != NULL)
    {
        addUser(*u);
        return;
    }

    // didn't match to object type
    QLOG_ERROR() << "Object type not recognized";
    throw Exception("Object type not recognized", "DataManager::addObject");
}

void DataManager::updateObject(const Object &o) throw(Exception)
{
    const Patient * p = dynamic_cast<const Patient *>(&o);
    if(p != NULL)
    {
        updatePatient(*p);
        return;
    }

    const Location * l = dynamic_cast<const Location *>(&o);
    if(l != NULL)
    {
        updateLocation(*l);
        return;
    }

    const User * u = dynamic_cast<const User *>(&o);
    if(u != NULL)
    {
        updateUser(*u);
        return;
    }

    // didn't match to object type
    QLOG_ERROR() << "Object type not recognized";
    throw Exception("Object type not recognized", "DataManager::updateObject");
}

void DataManager::deleteObject(const Object &o) throw(Exception)
{
    const Patient * p = dynamic_cast<const Patient *>(&o);
    if(p != NULL)
    {
        deletePatient(p->getHealthCardNumber());
        return;
    }

    const Location * l = dynamic_cast<const Location *>(&o);
    if(l != NULL)
    {
        deleteLocation(l->getID());
        return;
    }

    const User * u = dynamic_cast<const User *>(&o);
    if(u != NULL)
    {
        deleteUser(QString(u->getUserName().c_str()));
        return;
    }

    const Memento * m = dynamic_cast<const Memento *>(&o);
    if(m != NULL)
    {
        deleteMemento(m->getTimeStamp());
        return;
    }

    // didn't match to object type
    QLOG_ERROR() << "Object type not recognized";
}

void DataManager::addPatient(const Patient &p) throw(Exception)
{
    try
    {
        p.validate();
        QLOG_INFO() << "validating the object was successful " << p.toString().c_str();
    }
    catch(Exception & e) {
        QLOG_ERROR() << "validating the object failed " << p.toString().c_str()  << "\n"
                << "Message: " << e.getMessage().c_str();
        throw e;
    }

    int HCN = p.getHealthCardNumber();
    QVariant first_name = QString(p.getFirstName().c_str());
    QVariant last_name = QString(p.getLastName().c_str());
    int rec_care = p.getRecCareType();
    int req_care = p.getReqCareType();
    QVariant WL_Date;
    if(p.getDateAddedToWaitingList() == NULL) {
        WL_Date = QVariant(QVariant::String);
    } else {
        WL_Date = p.getDateAddedToWaitingList()->toString();
    }
    QVariant admit_date;
    if(p.getDateAdmitted() == NULL) {
        admit_date = QVariant(QVariant::String);
    } else {
        admit_date = p.getDateAdmitted()->toString();
    }
    QVariant location;
    if(p.getCareLocation() == NULL) {
        location = QVariant(QVariant::Int);
    } else {
        location = p.getCareLocation()->getID();
    }

    //SQL PORTION START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);

    db.transaction();
    query.prepare("INSERT INTO Patients (HCN, First_Name, Last_Name, Care_Req, Care_Rec, WL_Date, Admit_Date, Location) "
                  "VALUES (:hcn, :fname, :lname, :reqcare, :reccare, :addDate, :admitDate, :loc);");
    query.bindValue(":hcn", HCN);
    query.bindValue(":fname", first_name);
    query.bindValue(":lname", last_name);
    query.bindValue(":reqcare", req_care);
    query.bindValue(":reccare", rec_care);
    query.bindValue(":addDate", WL_Date);
    query.bindValue(":admitDate", admit_date);
    query.bindValue(":loc", location);
    if(!query.exec()) {
        QLOG_DEBUG() << "addPatient's SQL query failed " << query.lastError().text() << p.toString().c_str();
        db.rollback();
        throw Exception("SQL query failed", "DataManager::addPatient");
    }
    else
        db.commit();

    QLOG_INFO() << "addPatient's SQL query was successful " << p.toString().c_str();
    // SQL STATEMENTS END
}

void DataManager::addUser(const User & u) throw(Exception)
{
    try
    {
        u.validate();
        QLOG_INFO() << "validating the object was successful " << u.toString().c_str();
    }
    catch(Exception & e) {
        QLOG_ERROR() << "validating the object failed " << u.toString().c_str()  << "\n"
                << "Message: " << e.getMessage().c_str();
        throw e;
    }

    QVariant username = QString(u.getUserName().c_str());
    QVariant password = QString(u.getPassword().c_str());
    int usertype = u.getUserType();

    //SQL PORTION START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);

    db.transaction();
    query.prepare("INSERT INTO Users (Username, Password, security_group) "
                  "VALUES (:uname, :password, :type);");
    query.bindValue(":uname", username);
    query.bindValue(":password", password);
    query.bindValue(":type", usertype);
    if(!query.exec()) {
        QLOG_ERROR() << "addUser's SQL query failed " << query.lastError().text() << u.toString().c_str();
        db.rollback();
        throw Exception("SQL query failed", "DataManager::addUser");
    }
    else
        db.commit();

    QLOG_INFO() << "addUser's SQL query was successful " << u.toString().c_str();
    //SQL STATEMENTS END
}

void DataManager::addMemento(const Memento & m, const User & u) throw(Exception)
{
    try
    {
        m.validate();
        QLOG_INFO() << "validating the object was successful " << m.toString().c_str();
    }
    catch(Exception & e) {
        QLOG_ERROR() << "validating the object failed " << m.toString().c_str()  << "\n"
                << "\n" << "Message: " << e.getMessage().c_str();
        throw e;
    }

    QVariant timestamp = m.getTimeStamp().toString();
    QVariant created_by_user = QString(u.getUserName().c_str());
    QVariant data = QString(m.getData().c_str());

    //SQL PORTION START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);

    db.transaction();
    query.prepare("INSERT INTO Memento (Timestamp, Created_By_User, Data) "
                  "VALUES (:ts, :byuser, :data);");
    query.bindValue(":ts", timestamp);
    query.bindValue(":byuser", created_by_user);
    query.bindValue(":data", data);
    if(!query.exec()) {
        QLOG_ERROR() << "addMemento's SQL query failed " << query.lastError().text() << m.toString().c_str();
        db.rollback();
        throw Exception("SQL query failed", "DataManager::addMemento");
    }
    else
        db.commit();

    QLOG_INFO() << "addMemento's SQL query was successful " << m.toString().c_str();
    //SQL STATEMENTS END
}

void DataManager::addLocation(const Location & l) throw(Exception)
{
    try
    {
        l.validate();
        QLOG_INFO() << "validating the object was successful " << l.toString().c_str();
    }
    catch(Exception & e) {
        QLOG_ERROR() << "validating the object failed " << l.toString().c_str()  << "\n"
                << "Message: " << e.getMessage().c_str();
        throw e;
    }

    int id = l.getID();
    QString name = QString(l.getName().c_str());
    int x = l.getX();
    int y = l.getY();
    int AC = l.getACBeds();
    int CCC = l.getCCCBeds();
    int LTC = l.getLTCBeds();
    int region = l.getRegion()->getID();

    //SQL PORTION START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);

    db.transaction();
    query.prepare("INSERT INTO Location (ID, Name, X, Y, AC, CCC, LTC, Region) "
                  "VALUES (:id, :name, :x, :y, :ac, :ccc, :ltc, :region);");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":x", x);
    query.bindValue(":y", y);
    query.bindValue(":ac", AC);
    query.bindValue(":ccc", CCC);
    query.bindValue(":ltc", LTC);
    query.bindValue(":region", region);
    if(!query.exec()) {
        QLOG_ERROR() << "addLocation's SQL query failed " << query.lastError().text() << l.toString().c_str();
        db.rollback();
        throw Exception("SQL query failed", "DataManager::addLocation");
    }
    else
        db.commit();

    QLOG_INFO() << "addLocation's SQL query was successful " << l.toString().c_str();
    //SQL STATEMENTS END
}

void DataManager::addToWaitingList(const Region & r, const Patient & p) throw(Exception) {
    //SQL PORTION START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);

    db.transaction();
    query.prepare("INSERT INTO WaitingList (Patient, Region, Timestamp) "
                  "VALUES (:pat, :reg, :ts);");
    query.bindValue(":pat", p.getHealthCardNumber());
    query.bindValue(":reg", r.getID());
    query.bindValue(":ts", QDateTime::currentDateTime());
    if(!query.exec()) {
        QLOG_ERROR() << "addToWaitingList's SQL query failed: " << r.getID() << " " << p.getHealthCardNumber() << " " << query.lastError().text();
        db.rollback();
        throw Exception("SQL query failed", "DataManager::addToWaitingList");
    }
    else
        db.commit();

    QLOG_INFO() << "addToWaitingList's SQL query was successful: " << r.getID() << " " << p.getHealthCardNumber();
    //SQL STATEMENTS END
}

void DataManager::removeFromWaitingList(const Region & r, const Patient & p) throw(Exception) {
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);

    db.transaction();
    query.prepare("DELETE FROM WaitingList "
                  "WHERE Patient = :pat AND Region = :reg;");
    query.bindValue(":pat", p.getHealthCardNumber());
    query.bindValue(":reg", r.getID());
    if(!query.exec()) {
        QLOG_ERROR() << "removeFromWaitingList's SQL query failed: " << r.getID() << " " << p.getHealthCardNumber() << " " << query.lastError().text();
        db.rollback();
        throw Exception("SQL query failed", "DataManager::removeFromWaitingList");
    }
    else
        db.commit();

    QLOG_INFO() << "removeFromWaitingList's SQL query was successful: " << r.getID() << " " << p.getHealthCardNumber();
}

void DataManager::updatePatient(const Patient &p) throw(Exception)
{
    try
    {
        p.validate();
        QLOG_INFO() << "validating the object was successful " << p.toString().c_str();
    }
    catch(Exception & e) {
        QLOG_ERROR() << "validating the object failed " << p.toString().c_str()  << "\n"
                << "Message: " << e.getMessage().c_str();
        throw e;
    }

    int hcn = p.getHealthCardNumber();

    QVariant first_name = QString(p.getFirstName().c_str());
    QVariant last_name = QString(p.getLastName().c_str());
    int care_req = p.getReqCareType();
    int care_rec = p.getRecCareType();
    QVariant wl_date;
    if(p.getDateAddedToWaitingList() == NULL) {
        wl_date = QVariant(QVariant::String);
    } else {
        wl_date = p.getDateAddedToWaitingList()->toString();
    }
    QVariant admit_date;
    if(p.getDateAdmitted() == NULL) {
        admit_date = QVariant(QVariant::String);
    } else {
        admit_date = p.getDateAdmitted()->toString();
    }
    QVariant location;
    if(p.getCareLocation() == NULL) {
        location = QVariant(QVariant::Int);
    } else {
        location = p.getCareLocation()->getID();
    }

    //SQL PORTION START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);
    db.transaction();
    query.prepare("UPDATE Patients SET First_Name = :fname, Last_Name = :lname, Care_Req = :reqcare, Care_Rec = :reccare, WL_Date = :wld, Admit_Date = :ad, Location = :loc "
                  "WHERE HCN = :hcn;");
    query.bindValue(":fname", first_name);
    query.bindValue(":lname", last_name);
    query.bindValue(":reqcare", care_req);
    query.bindValue(":reccare", care_rec);
    query.bindValue(":wld", wl_date);
    query.bindValue(":ad", admit_date);
    query.bindValue(":loc", location);
    query.bindValue(":hcn", hcn);
    if(!query.exec()) {
        QLOG_ERROR() << "updating the patient failed " << query.lastError().text() << p.toString().c_str();
        db.rollback();
        throw Exception("updating the patient failed", "DataManager::updatePatient");
    }
    else
        db.commit();

    QLOG_INFO() << "updating the patient was successful "  <<  p.toString().c_str();
    //SQL STATEMENTS END
}

void DataManager::updateUser(const User &u) throw(Exception)
{
    try
    {
        u.validate();
        QLOG_INFO() << "validating the object was successful " << u.toString().c_str();
    }
    catch(Exception & e) {
        QLOG_ERROR() << "validating the object failed " << u.toString().c_str()  << "\n"
                << "Message: " << e.getMessage().c_str();
        throw e;
    }

    QVariant username = QString(u.getUserName().c_str());

    QVariant password = QString(u.getPassword().c_str());
    int security_group = u.getUserType();

    //SQL START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);
    db.transaction();
    query.prepare("UPDATE Users SET Password = :pword, security_group = :sgroup WHERE Username = :uname;");
    query.bindValue(":pword", password);
    query.bindValue(":sgroup", security_group);
    query.bindValue(":uname", username);
    if(!query.exec()) {
        QLOG_ERROR() << "updating the user failed " << query.lastError().text() << " " << u.toString().c_str();
        db.rollback();
        throw Exception("updating the user failed", "DataManager::updateUser");
    }
    else
        db.commit();

    QLOG_INFO() << "updating the user was successful "  <<  u.toString().c_str();
    //SQL END
}

void DataManager::updateLocation(const Location &l) throw(Exception)
{
    try
    {
        l.validate();
        QLOG_INFO() << "validating the object was successful " << l.toString().c_str();
    }
    catch(Exception & e) {
        QLOG_ERROR() << "validating the object failed " << l.toString().c_str()  << "\n"
                << "Message: " << e.getMessage().c_str();
        throw e;
    }

    int ID = l.getID();

    QVariant name = QString(l.getName().c_str());
    int x = l.getX();
    int y = l.getY();
    int ac = l.getACBeds();
    int ccc = l.getCCCBeds();
    int ltc = l.getLTCBeds();
    int region = l.getRegion()->getID();

    //SQL START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);
    db.transaction();
    query.prepare("UPDATE Location SET name = :name, X = :x, Y = :y, AC = :ac, CCC = :ccc, LTC = :ltc, region = :reg "
                  "WHERE ID = :id;");
    query.bindValue(":name", name);
    query.bindValue(":x", x);
    query.bindValue(":y", y);
    query.bindValue(":ac", ac);
    query.bindValue(":ccc", ccc);
    query.bindValue(":ltc", ltc);
    query.bindValue(":reg", region);
    query.bindValue(":id", ID);
    if(!query.exec()) {
        QLOG_ERROR() << "updating the location failed " << query.lastError().text() << " " << l.toString().c_str();
        db.rollback();
        throw Exception("updating the location failed", "DataManager::updateLocation");
    }
    else
        db.commit();

    QLOG_INFO() << "updating the location was successful "  <<  l.toString().c_str();
    //SQL END
}

void DataManager::deletePatient(const int HCN) throw(Exception)
{
    //SQL START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);
    db.transaction();
    query.prepare("DELETE FROM Patients "
                  "WHERE HCN = :hcn;");
    query.bindValue(":hcn", HCN);
    if(!query.exec()) {
        QLOG_ERROR() << "deleting this patient failed " << HCN << " " << query.lastError().text();
        db.rollback();
    }
    else
        db.commit();

    QLOG_INFO() << "deleting this patient was successful " << HCN;
    //SQL END
}

void DataManager::deleteUser(const QString & username) throw(Exception)
{
    //SQL START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);
    db.transaction();
    query.prepare("DELETE FROM Users "
                  "WHERE Username = :user;");
    query.bindValue(":user", username);
    if(!query.exec()) {
        QLOG_ERROR() << "deleting this user failed " << username << " " << query.lastError().text();
        db.rollback();
    }
    else
        db.commit();

    QLOG_INFO() << "deleting this user was successful " << username;
    //SQL END
}

void DataManager::deleteMemento(const QDateTime & dt) throw(Exception)
{
    //SQL START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);
    db.transaction();
    query.prepare("DELETE FROM Memento "
                  "WHERE Timestamp = :ts;");
    query.bindValue(":ts", dt.toString());
    if(!query.exec()) {
        QLOG_ERROR() << "deleting this memento failed "<< dt.toString() << " " << query.lastError().text();
        db.rollback();
    }
    else
        db.commit();

    QLOG_INFO() << "deleting this memento was successful " << dt.toString();
    //SQL END
}

void DataManager::deleteLocation(const int ID) throw(Exception)
{
    //SQL START
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);
    db.transaction();
    query.prepare("DELETE FROM Location "
                  "WHERE Username = :id;");
    query.bindValue(":id", ID);
    if(!query.exec()) {
        QLOG_ERROR() << "deleting this location failed " << ID << " " << query.lastError().text();
        db.rollback();
    }
    else
        db.commit();

    QLOG_INFO() << "deleting this location was successful " << ID;
    //SQL END
}

Map * DataManager::getMap() throw(Exception)
{
    Map * m = new Map();
    QSqlQuery query(Database::getOpenDatabase());
    query.prepare("SELECT ID FROM Region;");
    if(!query.exec())
    {
        QLOG_ERROR() << "SQL getMap SELECT failed " << query.lastError().text();
        throw Exception("SQL statement error", "DataManager::getMap");
    }
    while(query.next()) {
        int ID = query.value(0).toInt();
        m->addRegion(new RegionProxy(ID));
    }
    return m;
}

Region * DataManager::getRegion(const int ID) throw(Exception)
{
    QSqlDatabase db = Database::getOpenDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT Name FROM Region "
                  "WHERE ID = :id;");
    query.bindValue(":id", ID);
    if(!query.exec()) {
        QLOG_ERROR() << "SQL getRegion SELECT failed " << ID << " " << query.lastError().text();
        throw Exception("SQL statement error", "DataManager::getRegion");
    }
    if(!query.first()) {
        QLOG_INFO() << "Could not find region " << ID;
        return NULL;
    }

    QLOG_INFO() << "getting this region " << ID  << " was successful";

    QString name = query.value(0).toString();
    Region * reg = new RegionObject(ID, name.toStdString());

    query.prepare("SELECT ID FROM Location WHERE Region = :reg;");
    query.bindValue(":reg", ID);
    if(!query.exec())
    {
        QLOG_ERROR() << "SQL getRegion SELECT failed while getting locations " << ID << " " << query.lastError().text();
        throw Exception("SQL statement error", "DataManager::getRegion");
    }
    while(query.next())
    {
        reg->addLocation(new LocationProxy(query.value(0).toInt()));
    }

    query.prepare("SELECT Patient FROM WaitingList WHERE Region = :reg;");
    query.bindValue(":reg", ID);
    if(!query.exec())
    {
        QLOG_ERROR() << "SQL getRegion SELECT failed while getting patients " << ID << " " << query.lastError().text();
        throw Exception("SQL statement error", "DataManager::getRegion");
    }
    while(query.next())
    {
        reg->addPatient(new PatientProxy(query.value(0).toInt()));
    }

    return reg;
}

QPixmap * DataManager::getRegionImage(const int ID) throw(Exception)
{
    QSqlQuery query(Database::getOpenDatabase());
    query.prepare("SELECT ImageFile FROM Region WHERE ID = :id;");
    query.bindValue(":id", ID);
    if(!query.exec())
    {
        QLOG_ERROR() << "SQL getRegionImage SELECT failed " << ID << " " << query.lastError().text();
        throw Exception("SQL statement error", "DataManager::getRegionImage");
    }
    if(!query.first())
    {
        QLOG_INFO() << "Could not find imagefile " << ID;
        return NULL;
    }
    QPixmap * pix = new QPixmap();
    pix->load(query.value(0).toString());
    return pix;
}

Location * DataManager::getLocation(const int fID) throw(Exception)
{
    QSqlQuery query(Database::getOpenDatabase());
    query.prepare("SELECT ID, Name, X, Y, AC, CCC, LTC, Region "
                  "FROM Location "
                  "WHERE ID = :lid;");
    query.bindValue(":lid", fID);
    if(!query.exec()) {
        QLOG_ERROR() << "SQL getLocation SELECT failed on getting patients " << fID << " " << query.lastError().text();
        throw Exception("SQL statement error:", "DataManager::getLocation");
    }
    if(!query.first())
    {
        QLOG_INFO() << "Could not find location " << fID;
        return NULL;
    }

    QLOG_INFO() << "getting this location " << fID  << " was successful";

    QString Name = query.value(1).toString();
    float X = query.value(2).toFloat();
    float Y = query.value(3).toFloat();
    int AC = query.value(4).toInt();
    int CCC = query.value(5).toInt();
    int LTC = query.value(6).toInt();
    Location * loc = new LocationObject(fID, Name.toStdString(), X, Y, AC, CCC, LTC);

    if(!query.value(7).isNull())
    {
        int region = query.value(7).toInt();
        loc->setRegion(new RegionProxy(region));
    }

    query.prepare("SELECT HCN FROM Patients WHERE Location = :id;");
    query.bindValue(":id", fID);
    if(!query.exec())
    {
        QLOG_ERROR() << "SQL getLocation SELECT failed while getting patients " << fID << " " << query.lastError().text();
        throw Exception("SQL statement error", "DataManager::getLocation");
    }
    while(query.next())
    {
        loc->addPatient(new PatientProxy(query.value(0).toInt()));
    }
    return loc;
}

Patient * DataManager::getPatient(const int HCN) throw(Exception)
{
    QSqlQuery query(Database::getOpenDatabase());
    query.prepare("SELECT HCN, First_Name, Last_Name, Care_Req, Care_Rec, Admit_Date, WL_Date, Location "
                  "FROM Patients "
                  "WHERE HCN = :hcn;");
    query.bindValue(":hcn", HCN);
    if(!query.exec()) {
        QLOG_ERROR() << "SQL getPatient SELECT failed " << HCN << " " << query.lastError().text();
        throw Exception("SQL statement error", "DataManager::getPatient");
    }
    if(!query.first()) {
        QLOG_INFO() << "Could not find patient" << HCN;
        return NULL;
    }

    QLOG_INFO() << "getting this patient was successful " << HCN;

    std::string fname = query.value(1).toString().toStdString();
    std::string lname = query.value(2).toString().toStdString();
    CARETYPE req_care = CARETYPE(query.value(3).toString().toInt());
    Patient * pat = new PatientObject(HCN, fname, lname, req_care);

    CARETYPE rec_care = CARETYPE(query.value(4).toString().toInt());
    pat->setRecCareType(rec_care);

    if(!query.value(5).isNull())
    {
        QDateTime * admitDate = new QDateTime(query.value(5).toDateTime());
        pat->setDateAdmitted(admitDate);
    }

    if(!query.value(6).isNull())
    {
        QDateTime * wlDate = new QDateTime(query.value(6).toDateTime());
        pat->setDateAddedToWaitingList(wlDate);
    }

    if(!query.value(7).isNull())
    {
        int location = query.value(7).toInt();
        pat->setCareLocation(new LocationProxy(location));
    }

    query.prepare("SELECT Region FROM WaitingList WHERE Patient = :pat;");
    query.bindValue(":pat", HCN);
    if(!query.exec())
    {
        QLOG_ERROR() << "SQL getPatient SELECT failed while getting regions " << HCN << " " << query.lastError().text();
        throw Exception("SQL statement error", "DataManager::getPatient");
    }
    while(query.next())
    {
        pat->addRegion(new RegionProxy(query.value(0).toInt()));
    }
    return pat;
}

User * DataManager::getUser(const QString & userName) throw(Exception)
{
    QSqlQuery query(Database::getOpenDatabase());
    query.prepare("SELECT Username, Password, security_group "
                  "FROM Users "
                  "WHERE Username = :user;");
    query.bindValue(":user", userName);
    if(!query.exec()) {
        QLOG_ERROR() << "SQL getUser SELECT failed " << userName << " " << query.lastError().text();
        throw Exception("SQL statement error:", "DataManager::getUser");
    }
    if(!query.first()) {
        QLOG_INFO() << "Could not find user " << userName;
        return NULL;
    }

    QLOG_INFO() << "getting this user was successful " << userName;

    std::string pass = query.value(1).toString().toStdString();
    int sec_group = query.value(2).toInt();
    User * user = new User(userName.toStdString(), pass, LHIN::USERTYPE(sec_group));
    return user;
}

Memento * DataManager::getMemento(const QDateTime & dt) throw(Exception)
{
    QSqlQuery query(Database::getOpenDatabase());
    query.prepare("SELECT timestamp, data "
                  "FROM Memento"
                  "WHERE timestamp = :ts;");
    query.bindValue(":ts", dt.toString());
    query.exec();
    if(!query.first()) {
        QLOG_INFO() << "Could not find memento " << dt.toString();
        return NULL;
    }

    QLOG_INFO() << "getting this memento was successful " << dt.toString();

    std::string data = query.value(1).toString().toStdString();
    Memento * mem = new Memento(dt, data);
    return mem;
}

std::list<Object *> * DataManager::getObjectList(const std::list<OBJECTS> & objs)
{
    QLOG_INFO() << "getting all objects in database to be used in search";

    std::list<Object *> * ls = new std::list<Object *>();

    bool regions = false, locations = false, patients = false, users = false, memento = false;

    if(objs.empty())
    {
        regions = true;
        locations = true;
        patients = true;
        users = true;
        memento = true;
    } else {
        std::list<OBJECTS>::const_iterator iter;
        for(iter = objs.begin(); iter != objs.end(); iter++)
        {
            switch(*iter)
            {
            case REGION:
                regions = true;
                break;
            case LOCATION:
                locations = true;
                break;
            case PATIENT:
                patients = true;
                break;
            case USER:
                users = true;
                break;
            case MEMENTO:
                memento = true;
                break;
            default:
                break;
            }
        }
    }

    QSqlQuery query(Database::getOpenDatabase());

    if(patients)
    {
        query.prepare("SELECT HCN "
                      "FROM Patients;");
        if(!query.exec())
        {
            QLOG_ERROR() << "SQL SELECT HCN FROM Patients; failed. Did not add Patient data to potential Search Results " << query.lastError().text();
        }
        else
        {
            while(query.next())
            {
                ls->push_back(getPatient(query.value(0).toInt()));
            }
        }
    }

    if(locations)
    {
        query.prepare("SELECT ID "
                      "FROM Location;");
        if(!query.exec())
        {
            QLOG_ERROR() << "SQL SELECT ID FROM Location; failed. Did not add Location data to potential Search Results " << query.lastError().text();
        }
        else
        {
            while(query.next())
            {
                ls->push_back(getLocation(query.value(0).toInt()));
            }
        }
    }

    if(users)
    {
        query.prepare("SELECT Username "
                      "FROM Users;");
        if(!query.exec())
        {
            QLOG_ERROR() << "SQL SELECT Username FROM Users; failed. Did not add User data to potential Search Results" << query.lastError().text();
        }
        else
        {
            while(query.next())
            {
                ls->push_back(getUser(query.value(0).toString()));
            }
        }
    }

    if(regions)
    {
        query.prepare("SELECT ID "
                      "FROM Region;");
        if(!query.exec())
        {
            QLOG_ERROR() << "SQL SELECT ID FROM Region; failed. Did not add Region data to potential Search Results" << query.lastError().text();
        }
        else
        {
            while(query.next())
            {
                ls->push_back(getRegion(query.value(0).toInt()));
            }
        }
    }

    if(memento)
    {
        query.prepare("SELECT Timestamp "
                      "FROM Memento;");
        if(!query.exec())
        {
            QLOG_ERROR() << "SQL SELECT Timestamp FROM Memento; failed. Did not add Memento data to potential Search Results" << query.lastError().text();
        }
        else
        {
            while(query.next())
            {
                ls->push_back(getUser(query.value(0).toString()));
            }
        }
    }

    return ls;
}



NS_END
