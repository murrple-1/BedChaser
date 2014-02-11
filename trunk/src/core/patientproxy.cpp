#include "patientproxy.h"
#include "datamanager.h"

NS_START

        PatientProxy::PatientProxy(const int hcn):
        healthCardNumber(hcn), patObj(NULL)
{}

PatientProxy::~PatientProxy()
{
    if(patObj != NULL)
    {
        delete patObj;
    }
}

void PatientProxy::prepObject() const
{
    if(patObj == NULL)
    {
        patObj = dynamic_cast<PatientObject *>(DataManager::getDataManager().getPatient(healthCardNumber));
    }
}

std::string PatientProxy::toString() const
{
    prepObject();
    return patObj->toString();
}

std::string PatientProxy::toUIString() const
{
    prepObject();
    return patObj->toUIString();
}

void PatientProxy::validate() const throw(Exception)
{
    prepObject();
    patObj->validate();
}

int PatientProxy::getHealthCardNumber() const
{
    return healthCardNumber;
}

std::string PatientProxy::getFirstName(void) const
{
    prepObject();
    return patObj->getFirstName();
}

void PatientProxy::setFirstName(const std::string & f)
{
    prepObject();
    patObj->setFirstName(f);
}

std::string PatientProxy::getLastName() const
{
    prepObject();
    return patObj->getLastName();
}

void PatientProxy::setLastName(const std::string & l)
{
    prepObject();
    patObj->setLastName(l);
}

CARETYPE PatientProxy::getReqCareType(void) const
{
    prepObject();
    return patObj->getReqCareType();
}

void PatientProxy::setReqCareType(const CARETYPE ct)
{
    prepObject();
    patObj->setReqCareType(ct);
}

CARETYPE PatientProxy::getRecCareType() const
{
    prepObject();
    return patObj->getRecCareType();
}

void PatientProxy::setRecCareType(const CARETYPE ct)
{
    prepObject();
    patObj->setRecCareType(ct);
}

Location * PatientProxy::getCareLocation() const
{
    prepObject();
    return patObj->getCareLocation();
}

void PatientProxy::setCareLocation(Location * const loc)
{
    prepObject();
    patObj->setCareLocation(loc);
}

const std::vector<Region *> & PatientProxy::getWaitingRegions() const
{
    prepObject();
    return patObj->getWaitingRegions();
}

void PatientProxy::addRegion(Region * const r)
{
    prepObject();
    patObj->addRegion(r);
}

void PatientProxy::removeRegion(const int rID)
{
    prepObject();
    patObj->removeRegion(rID);
}

const QDateTime * PatientProxy::getDateAdmitted() const
{
    prepObject();
    return patObj->getDateAdmitted();
}

void PatientProxy::setDateAdmitted(QDateTime * const dt)
{
    prepObject();
    patObj->setDateAdmitted(dt);
}

const QDateTime * PatientProxy::getDateAddedToWaitingList() const
{
    prepObject();
    return patObj->getDateAddedToWaitingList();
}

void PatientProxy::setDateAddedToWaitingList(QDateTime * const dt)
{
    prepObject();
    patObj->setDateAddedToWaitingList(dt);
}

NS_END
