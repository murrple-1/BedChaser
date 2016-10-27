#include "waitinglistentry.h"

WaitingListEntry::WaitingListEntry(int regionId, int patientId, const QDateTime &dateAdded, QObject *parent) :
    QObject(parent),
    regionId(regionId),
    patientId(patientId),
    dateAdded(dateAdded)
{

}

int WaitingListEntry::getRegionId() const
{
    return regionId;
}

int WaitingListEntry::getPatientId() const
{
    return patientId;
}

const QDateTime & WaitingListEntry::getDateAdded() const
{
    return dateAdded;
}
