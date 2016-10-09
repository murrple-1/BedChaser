#include "region.h"

Region::Region(const QVariant &id, const QString &name, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->name = name;
}

int Region::getID(bool *ok) const
{
    return id.toInt(ok);
}

const QString & Region::getName() const
{
    return name;
}

const QList<int> & Region::getLocationIds() const
{
    return locationIds;
}

void Region::addLocationId(int locationId)
{
    if(!locationIds.contains(locationId))
    {
        locationIds.append(locationId);
    }
}

void Region::removeLocationId(int index)
{
    locationIds.removeAt(index);
}

const QList<int> & Region::getWaitingListPatientIds() const
{
    return waitingListPatientIds;
}

void Region::addWaitingListPatientId(int patientId)
{
    if(!waitingListPatientIds.contains(patientId))
    {
        waitingListPatientIds.append(patientId);
    }
}

void Region::removeWaitingListPatientId(int index)
{
    waitingListPatientIds.removeAt(index);
}
