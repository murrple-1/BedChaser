#include "QsLog.h"
#include "QsLogDest.h"

#include "locationobject.h"
#include "patientproxy.h"
#include "regionproxy.h"
#include "../utils/stringbuilder.h"

NS_START

        LocationObject::LocationObject(const int ID, const std::string aName, const int anX, const int aY, const int AC, const int CCC, const int LTC):
        id(ID), name(aName),x(anX), y(aY), ACBeds(AC), CCCBeds(CCC), LTCBeds(LTC), region(NULL)
{}

LocationObject::LocationObject(const LocationObject & loc):
        id(loc.getID()), x(loc.getX()), y(loc.getY()), ACBeds(loc.getACBeds()), CCCBeds(loc.getCCCBeds()), LTCBeds(loc.getLTCBeds())
{
    if(loc.getRegion() != NULL)
    {
        region = new RegionProxy(loc.getRegion()->getID());
    }
    std::vector<Patient *>::const_iterator iter;
    for(iter = loc.getPatientList().begin(); iter != loc.getPatientList().end(); iter++) {
        addPatient(new PatientProxy((*iter)->getHealthCardNumber()));
    }
}

LocationObject::~LocationObject()
{
    std::vector<Patient *>::iterator iter;
    for(iter = patientsInCare.begin(); iter != patientsInCare.end(); iter++) {
       delete *iter;
    }
}

std::string LocationObject::toString() const
{
    StringBuilder sb;
    sb.append(std::string("Location: "));
    sb.append(std::string("id=")).append(id).append(' ');
    sb.append(std::string("name=").append(name)).append(' ');
    sb.append(std::string("x=")).append(x).append(' ');
    sb.append(std::string("y=")).append(y).append(' ');
    sb.append(std::string("ACBeds=")).append(ACBeds).append(' ');
    sb.append(std::string("CCCBeds=")).append(CCCBeds).append(' ');
    sb.append(std::string("LTCBeds=")).append(LTCBeds).append(' ');
    sb.append(std::string("patientsInCare=["));
    std::vector<Patient *>::const_iterator patIter;
    for(patIter = patientsInCare.begin(); patIter != patientsInCare.end(); patIter++) {
        sb.append((*patIter)->getHealthCardNumber()).append(',');
    }
    sb.append(']');
    return sb.toString();
}

std::string LocationObject::toUIString() const
{
    return getName();
}

void LocationObject::validate() const throw(Exception)
{

}

int LocationObject::getID() const {
    return id;
}

std::string LocationObject::getName() const {
    return name;
}

void LocationObject::setName(const std::string & n) {
    name = n;
}

int LocationObject::getX() const {
    return x;
}

void LocationObject::setX(const int x) {
    this->x = x;
}

int LocationObject::getY() const {
    return y;
}

void LocationObject::setY(const int y) {
    this->y = y;
}

int LocationObject::getACBeds() const {
    return ACBeds;
}

void LocationObject::setACBeds(const int AC) {
    ACBeds = AC;
}

int LocationObject::getCCCBeds() const {
    return CCCBeds;
}

void LocationObject::setCCCBeds(const int CCC) {
    CCCBeds = CCC;
}

int LocationObject::getLTCBeds() const {
    return LTCBeds;
}

void LocationObject::setLTCBeds(const int LTC) {
    LTCBeds = LTC;
}

const std::vector<Patient *> & LocationObject::getPatientList() const {
    return patientsInCare;
}

void LocationObject::addPatient(Patient * const p)
{
    if(p == NULL)
    {
        return;
    }
    std::vector<Patient *>::iterator iter;
    for(iter = patientsInCare.begin(); iter != patientsInCare.end(); iter++) {
        if(p->getHealthCardNumber() == (*iter)->getHealthCardNumber())
        {
            return;
        }
    }
    patientsInCare.push_back(p);
}

void LocationObject::removePatient(const int HCN)
{
    std::vector<Patient *>::iterator iter;
    for(iter = patientsInCare.begin(); iter != patientsInCare.end(); iter++) {
        if(HCN == (*iter)->getHealthCardNumber()) {
            patientsInCare.erase(iter);
            break;
        }
    }
}

Region * LocationObject::getRegion() const {
    return region;
}

void LocationObject::setRegion(Region * const r) {
    region = r;
}

NS_END
