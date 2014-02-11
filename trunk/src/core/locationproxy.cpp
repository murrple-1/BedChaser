#include "locationproxy.h"
#include "datamanager.h"

NS_START

LocationProxy::LocationProxy(const int ID):
        id(ID), locObject(NULL)
{}

LocationProxy::~LocationProxy() {
    if(locObject != NULL) {
        delete locObject;
    }
}

void LocationProxy::prepObject() const
{
    if(locObject == NULL) {
        locObject = dynamic_cast<LocationObject *>(DataManager::getDataManager().getLocation(id));
    }
}

std::string LocationProxy::toString() const
{
    prepObject();
    return locObject->toString();
}

std::string LocationProxy::toUIString() const
{
    prepObject();
    return locObject->toUIString();
}

void LocationProxy::validate() const throw(Exception)
{
    prepObject();
    locObject->validate();
}

int LocationProxy::getID() const
{
    return id;
}

std::string LocationProxy::getName() const
{
    prepObject();
    return locObject->getName();
}

void LocationProxy::setName(const std::string & name)
{
    prepObject();
    locObject->setName(name);
}

int LocationProxy::getX() const
{
    prepObject();
    return locObject->getX();
}

void LocationProxy::setX(const int x)
{
    prepObject();
    locObject->setX(x);
}

int LocationProxy::getY() const
{
    prepObject();
    return locObject->getY();
}

void LocationProxy::setY(const int y)
{
    prepObject();
    locObject->setY(y);
}

int LocationProxy::getACBeds() const
{
    prepObject();
    return locObject->getACBeds();
}

void LocationProxy::setACBeds(const int ac)
{
    prepObject();
    locObject->setACBeds(ac);
}

int LocationProxy::getCCCBeds() const
{
    prepObject();
    return locObject->getCCCBeds();
}

void LocationProxy::setCCCBeds(const int ccc)
{
    prepObject();
    locObject->setCCCBeds(ccc);
}

int LocationProxy::getLTCBeds() const
{
    prepObject();
    return locObject->getLTCBeds();
}

void LocationProxy::setLTCBeds(const int ltc)
{
    prepObject();
    locObject->setLTCBeds(ltc);
}

const std::vector<Patient *> & LocationProxy::getPatientList() const
{
    prepObject();
    return locObject->getPatientList();
}

void LocationProxy::addPatient(Patient * const p)
{
    prepObject();
    locObject->addPatient(p);
}

void LocationProxy::removePatient(const int HCN)
{
    prepObject();
    locObject->removePatient(HCN);
}

Region * LocationProxy::getRegion() const
{
    prepObject();
    return locObject->getRegion();
}
void LocationProxy::setRegion(Region * const r)
{
    prepObject();
    locObject->setRegion(r);
}

NS_END
