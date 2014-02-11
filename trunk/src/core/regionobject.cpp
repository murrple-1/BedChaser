#include "QsLog.h"
#include "QsLogDest.h"

#include "regionobject.h"
#include "locationproxy.h"
#include "patientproxy.h"
#include "../utils/stringbuilder.h"

NS_START

        RegionObject::RegionObject(const int ID, const std::string & aName):
        id(ID), name(aName)
{
}

RegionObject::RegionObject(const RegionObject & r):
        id(r.getID()), name(r.getName())
{
    std::vector<Location *>::const_iterator locIter;
    for(locIter = r.getLocations().begin(); locIter != r.getLocations().end(); locIter++) {
        addLocation(new LocationProxy((*locIter)->getID()));
    }
    std::vector<Patient *>::const_iterator patIter;
    for(patIter = r.getPatients().begin(); patIter != r.getPatients().end(); patIter++) {
        addPatient(new PatientProxy((*patIter)->getHealthCardNumber()));
    }
}

RegionObject::~RegionObject()
{
    std::vector<Location *>::const_iterator locIter;
    for(locIter = locations.begin(); locIter != locations.end(); locIter++) {
        delete *locIter;
    }
    std::vector<Patient *>::const_iterator patIter;
    for(patIter = waitingList.begin(); patIter != waitingList.end(); patIter++) {
        delete *patIter;
    }
}

std::string RegionObject::toString() const
{
    StringBuilder sb;
    sb.append(std::string("Region: "));
    sb.append(std::string("id=")).append(id).append(' ');
    sb.append(std::string("name=")).append(name).append(' ');
    sb.append(std::string("locations=["));
    std::vector<Location *>::const_iterator locIter;
    for(locIter = locations.begin(); locIter != locations.end(); locIter++) {
        sb.append((*locIter)->toString()).append(',');
    }
    sb.append(']').append(' ');
    sb.append(std::string("waitingList=["));
    std::vector<Patient *>::const_iterator patIter;
    for(patIter = waitingList.begin(); patIter != waitingList.end(); patIter++) {
        sb.append((*patIter)->getHealthCardNumber()).append(',');
    }
    sb.append(']');
    return sb.toString();
}

std::string RegionObject::toUIString() const
{
    return getName();
}

void RegionObject::validate() const throw(Exception)
{

}

int RegionObject::getID() const {
    return id;
}

std::string RegionObject::getName() const
{
    return name;
}

const std::vector<Location *> & RegionObject::getLocations() const {
    return locations;
}

void RegionObject::addLocation(Location * const l) {
    if(l == NULL)
    {
        return;
    }
    std::vector<Location *>::iterator iter;
    for(iter = locations.begin(); iter != locations.end(); iter++) {
        if(l->getID() == (*iter)->getID()) {
            return;
        }
    }
    locations.push_back(l);
}

void RegionObject::removeLocation(const int ID) {
    std::vector<Location *>::iterator iter;
    for(iter = locations.begin(); iter != locations.end(); iter++) {
        if(ID == (*iter)->getID()) {
            locations.erase(iter);
            break;
        }
    }
}

const std::vector<Patient *> & RegionObject::getPatients() const {
    return waitingList;
}

void RegionObject::addPatient(Patient * const p)
{
    if(p == NULL)
    {
        return;
    }
    std::vector<Patient *>::const_iterator iter;
    for(iter = waitingList.begin(); iter != waitingList.end(); iter++) {
        if(p->getHealthCardNumber() == (*iter)->getHealthCardNumber()) {
            return;
        }
    }
    waitingList.push_back(p);
}

void RegionObject::removePatient(const int HCN)
{
    std::vector<Patient *>::iterator iter;
    for(iter = waitingList.begin(); iter != waitingList.end(); iter++) {
        if(HCN == (*iter)->getHealthCardNumber()) {
            waitingList.erase(iter);
            break;
        }
    }
}

NS_END
