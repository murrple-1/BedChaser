#include "QsLog.h"
#include "QsLogDest.h"

#include "patientobject.h"
#include "regionproxy.h"
#include "locationproxy.h"
#include "../utils/stringbuilder.h"

NS_START

        PatientObject::PatientObject(const int HCN, const std::string & first, const std::string & last, const CARETYPE req):
        healthCardNumber(HCN), firstName(first), lastName(last), requiredCare(req), receivedCare(LHIN::NONE), careLocation(NULL), dateAdmitted(NULL), dateAddedToWaitingList(NULL)
{}

PatientObject::PatientObject(const PatientObject & p):
        healthCardNumber(p.getHealthCardNumber()), firstName(p.getFirstName()), lastName(p.getLastName()), requiredCare(p.getReqCareType()), receivedCare(p.getRecCareType())
{
    std::vector<Region *>::const_iterator iter;
    for(iter = p.getWaitingRegions().begin(); iter != p.getWaitingRegions().end(); iter++) {
        addRegion(new RegionProxy((*iter)->getID()));
    }
    if(p.getCareLocation() != NULL) {
        careLocation = new LocationProxy(p.getCareLocation()->getID());
    }

    if(p.getDateAddedToWaitingList() != NULL) {
        dateAddedToWaitingList = new QDateTime(*p.getDateAddedToWaitingList());
    }
    if(p.getDateAdmitted() != NULL) {
        dateAdmitted = new QDateTime(*p.getDateAddedToWaitingList());
    }
}

PatientObject::~PatientObject()
{
    std::vector<Region *>::iterator iter;
    for(iter = regionsWaiting.begin(); iter != regionsWaiting.end(); iter++) {
        delete *iter;
    }
    if(careLocation != NULL) {
        delete careLocation;
    }
    if(dateAddedToWaitingList != NULL) {
        delete dateAddedToWaitingList;
    }
    if(dateAdmitted != NULL) {
        delete dateAdmitted;
    }
}

std::string PatientObject::toString() const
{
    StringBuilder sb;
    sb.append(std::string("Patient: "));
    sb.append(std::string("healthCardNumber=")).append(healthCardNumber).append(' ');
    sb.append(std::string("firstName=")).append(firstName).append(' ');
    sb.append(std::string("lastName=")).append(lastName).append(' ');
    sb.append(std::string("requiredCare=")).append(requiredCare).append(' ');
    sb.append(std::string("receivedCare=")).append(receivedCare).append(' ');
    sb.append(std::string("careLocation="));
    if(careLocation == NULL) {
        sb.append(std::string("NULL"));
    } else {
        sb.append(careLocation->toString());
    }
    sb.append(' ');
    sb.append(std::string("regionsWaiting=["));
    std::vector<Region *>::const_iterator regIter;
    for(regIter = regionsWaiting.begin(); regIter != regionsWaiting.end(); regIter++) {
        sb.append((*regIter)->getID()).append(',');
    }
    sb.append(']').append(' ');
    sb.append(std::string("dateAdmitted="));
    if(dateAdmitted == NULL) {
        sb.append(std::string("NULL"));
    } else {
        sb.append(dateAdmitted->toString().toStdString());
    }
    sb.append(' ');
    sb.append(std::string("dateAddedToWaitingList"));
    if(dateAddedToWaitingList == NULL) {
        sb.append(std::string("NULL"));
    } else {
        sb.append(dateAddedToWaitingList->toString().toStdString());
    }
    return sb.toString();
}

std::string PatientObject::toUIString() const
{
    return getLastName() + ", " + getFirstName();
}

void PatientObject::validate() const throw(Exception)
{

}

int PatientObject::getHealthCardNumber() const {
    return healthCardNumber;
}

std::string PatientObject::getFirstName() const {
    return firstName;
}

void PatientObject::setFirstName(const std::string & first) {
    firstName = first;
}

std::string PatientObject::getLastName() const {
    return lastName;
}

void PatientObject::setLastName(const std::string & last) {
    lastName = last;
}

CARETYPE PatientObject::getReqCareType() const {
    return requiredCare;
}

void PatientObject::setReqCareType(const CARETYPE req) {
    requiredCare = req;
}

CARETYPE PatientObject::getRecCareType() const {
    return receivedCare;
}

void PatientObject::setRecCareType(const CARETYPE rec) {
    receivedCare = rec;
}

Location * PatientObject::getCareLocation() const {
    return careLocation;
}

void PatientObject::setCareLocation(Location * const newLoc)
{
    careLocation = newLoc;
}

const std::vector<Region *> & PatientObject::getWaitingRegions() const {
    return regionsWaiting;
}

void PatientObject::addRegion(Region * const r)
{
    if(r == NULL) {
        return;
    }
    regionsWaiting.push_back(r);
}

void PatientObject::removeRegion(const int ID)
{
    std::vector<Region *>::iterator iter;
    for(iter = regionsWaiting.begin(); iter != regionsWaiting.end(); iter++) {
        if(ID == (*iter)->getID()) {
            regionsWaiting.erase(iter);
            break;
        }
    }
}

const QDateTime * PatientObject::getDateAdmitted() const {
    return dateAdmitted;
}

std::string PatientObject::getDateAdmittedToString() const {
    return dateAdmitted->toString((QString("YYYY-MM-DDThhhh:mm:ss"))).toStdString();
}

void PatientObject::setDateAdmitted(QDateTime * const dt) {
    dateAdmitted = dt;
}

const QDateTime * PatientObject::getDateAddedToWaitingList() const {
    return dateAddedToWaitingList;
}

std::string PatientObject::getDateAddedToWaitingListToString() const {
    return dateAddedToWaitingList->toString((QString("YYYY-MM-DDThhhh:mm:ss"))).toStdString();
}

void PatientObject::setDateAddedToWaitingList(QDateTime * const dt) {
    dateAddedToWaitingList = dt;
}

NS_END
