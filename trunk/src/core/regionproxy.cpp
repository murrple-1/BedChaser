#include "regionproxy.h"
#include "datamanager.h"

NS_START

        RegionProxy::RegionProxy(const int ID):
        id(ID), regObj(NULL)
{}

RegionProxy::~RegionProxy()
{
    if(regObj != NULL)
    {
        delete regObj;
    }
}

void RegionProxy::prepObject() const
{
    if(regObj == NULL)
    {
        regObj = dynamic_cast<RegionObject *>(DataManager::getDataManager().getRegion(id));
    }
}

std::string RegionProxy::toString() const
{
    prepObject();
    return regObj->toString();
}

std::string RegionProxy::toUIString() const
{
    prepObject();
    return regObj->toUIString();
}

void RegionProxy::validate() const throw(Exception)
{
    prepObject();
    regObj->validate();
}

int RegionProxy::getID() const
{
    return id;
}

std::string RegionProxy::getName() const
{
    prepObject();
    return regObj->getName();
}

const std::vector<Location *> & RegionProxy::getLocations() const
{
    prepObject();
    return regObj->getLocations();
}

void RegionProxy::addLocation(Location * const l)
{
    prepObject();
    regObj->addLocation(l);
}

void RegionProxy::removeLocation(const int ID)
{
    prepObject();
    regObj->removeLocation(ID);
}

const std::vector<Patient *> & RegionProxy::getPatients() const
{
    prepObject();
    return regObj->getPatients();
}

void RegionProxy::addPatient(Patient * const p)
{
    prepObject();
    regObj->addPatient(p);
}

void RegionProxy::removePatient(const int HCN)
{
    prepObject();
    regObj->removePatient(HCN);
}

NS_END
