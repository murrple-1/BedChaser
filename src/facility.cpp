#include "facility.h"

Facility::Facility(const QVariant &id, const QString &name, int x, int y, int AC, int CCC, int LTC) :
    ACBeds(AC), CCCBeds(CCC), LTCBeds(LTC), regionId()
{
    this->id = id;
    this->name = name;
    this->x = x;
    this->y = y;
}

int Facility::getID(bool *ok) const
{
    return id.toInt(ok);
}

const QString & Facility::getName() const
{
    return name;
}

void Facility::setName(const QString &n)
{
    name = n;
}

int Facility::getX() const
{
    return x;
}

void Facility::setX(const int x)
{
    this->x = x;
}

int Facility::getY() const
{
    return y;
}

void Facility::setY(const int y)
{
    this->y = y;
}

int Facility::getACBeds() const
{
    return ACBeds;
}

void Facility::setACBeds(const int AC)
{
    ACBeds = AC;
}

int Facility::getCCCBeds() const
{
    return CCCBeds;
}

void Facility::setCCCBeds(const int CCC)
{
    CCCBeds = CCC;
}

int Facility::getLTCBeds() const
{
    return LTCBeds;
}

void Facility::setLTCBeds(const int LTC)
{
    LTCBeds = LTC;
}

const QList<int> & Facility::getPatientsInCareIds() const
{
    return patientsInCare;
}

void Facility::addPatientInCareId(int id)
{
    if(!patientsInCare.contains(id))
    {
        patientsInCare.append(id);
    }
}

void Facility::removePatientInCareId(int index)
{
    patientsInCare.removeAt(index);
}

int Facility::getRegionId(bool *ok) const
{
    return regionId.toInt(ok);
}

void Facility::setRegionId(const QVariant &regionId)
{
    this->regionId = regionId;
}
