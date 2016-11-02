#include "facility.h"

Facility::Facility(const QVariant &id, const QString &name, const QPoint &mapOffset, int numberOfAcuteCareBeds, int numberOfComlexContinuingCareBeds, int numberOfLongTermCare, const QVariant &regionId, QObject *parent) :
    QObject(parent),
    id(id),
    name(name),
    mapOffset(mapOffset),
    numberOfAcuteCareBeds(numberOfAcuteCareBeds),
    numberOfComplexContinuingCareBeds(numberOfComlexContinuingCareBeds),
    numberOfLongTermCareBeds(numberOfLongTermCare),
    regionId(regionId)
{

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

const QPoint & Facility::getMapOffset() const
{
    return mapOffset;
}

void Facility::setMapOffset(const QPoint &mapOffset)
{
    this->mapOffset = mapOffset;
}

int Facility::getNumberOfAcuteCareBeds() const
{
    return numberOfAcuteCareBeds;
}

void Facility::setNumberOfAcuteCareBeds(const int AC)
{
    numberOfAcuteCareBeds = AC;
}

int Facility::getNumberOfComplexContinuingCareBeds() const
{
    return numberOfComplexContinuingCareBeds;
}

void Facility::setNumberOfComplexContinuingCareBeds(const int CCC)
{
    numberOfComplexContinuingCareBeds = CCC;
}

int Facility::getNumberOfLongTermCareBeds() const
{
    return numberOfLongTermCareBeds;
}

void Facility::setNumberOfLongTermCareBeds(const int LTC)
{
    numberOfLongTermCareBeds = LTC;
}

int Facility::getRegionId(bool *ok) const
{
    return regionId.toInt(ok);
}

void Facility::setRegionId(const QVariant &regionId)
{
    this->regionId = regionId;
}
