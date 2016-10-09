#include "location.h"

Location::Location(const QVariant &id, const QString &name, int x, int y, int AC, int CCC, int LTC) :
    ACBeds(AC), CCCBeds(CCC), LTCBeds(LTC), regionId()
{
    this->id = id;
    this->name = name;
    this->x = x;
    this->y = y;
}

int Location::getID(bool *ok) const
{
    return id.toInt(ok);
}

const QString & Location::getName() const
{
    return name;
}

void Location::setName(const QString &n)
{
    name = n;
}

int Location::getX() const
{
    return x;
}

void Location::setX(const int x)
{
    this->x = x;
}

int Location::getY() const
{
    return y;
}

void Location::setY(const int y)
{
    this->y = y;
}

int Location::getACBeds() const
{
    return ACBeds;
}

void Location::setACBeds(const int AC)
{
    ACBeds = AC;
}

int Location::getCCCBeds() const
{
    return CCCBeds;
}

void Location::setCCCBeds(const int CCC)
{
    CCCBeds = CCC;
}

int Location::getLTCBeds() const
{
    return LTCBeds;
}

void Location::setLTCBeds(const int LTC)
{
    LTCBeds = LTC;
}

const QList<int> & Location::getPatientsInCareIds() const
{
    return patientsInCare;
}

void Location::addPatientInCareId(int id)
{
    if(!patientsInCare.contains(id))
    {
        patientsInCare.append(id);
    }
}

void Location::removePatientInCareId(int index)
{
    patientsInCare.removeAt(index);
}

int Location::getRegionId(bool *ok) const
{
    return regionId.toInt(ok);
}

void Location::setRegionId(const QVariant &regionId)
{
    this->regionId = regionId;
}
