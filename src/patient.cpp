#include "patient.h"

Patient::Patient(int HCN, const QString &first, const QString &last, CARETYPE req) :
    healthCardNumber(HCN), firstName(first), lastName(last), requiredCare(req), receivedCare(NONE), careLocationId(), dateAdmitted(), dateAddedToWaitingList()
{

}

int Patient::getHealthCardNumber() const
{
    return healthCardNumber;
}

const QString & Patient::getFirstName() const
{
    return firstName;
}

void Patient::setFirstName(const QString &first)
{
    firstName = first;
}

const QString & Patient::getLastName() const
{
    return lastName;
}

void Patient::setLastName(const QString &last)
{
    lastName = last;
}

CARETYPE Patient::getReqCareType() const
{
    return requiredCare;
}

void Patient::setRequiredCareType(CARETYPE req)
{
    requiredCare = req;
}

CARETYPE Patient::getRecCareType() const
{
    return receivedCare;
}

void Patient::setReceivedCareType(const CARETYPE rec)
{
    receivedCare = rec;
}

int Patient::getCareLocationId(bool *ok) const
{
    return careLocationId.toInt(ok);
}

void Patient::setCareLocationId(const QVariant &careLocationId)
{
    this->careLocationId = careLocationId;
}

const QList<int> & Patient::getWaitingRegions() const
{
    return waitingRegionIds;
}

void Patient::addWaitingRegionId(int waitingRegionId)
{
    waitingRegionIds.append(waitingRegionId);
}

void Patient::removeWaitingRegionId(int index)
{
    waitingRegionIds.removeAt(index);
}

const QDateTime & Patient::getDateAdmitted() const
{
    return dateAdmitted;
}

void Patient::setDateAdmitted(const QDateTime &dateAdmitted)
{
    this->dateAdmitted = dateAdmitted;
}

const QDateTime & Patient::getDateAddedToWaitingList() const
{
    return dateAddedToWaitingList;
}

void Patient::setDateAddedToWaitingList(const QDateTime &dateAddedToWaitingList)
{
    this->dateAddedToWaitingList = dateAddedToWaitingList;
}
