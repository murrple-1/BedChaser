#include "patient.h"

Patient::Patient(const QVariant &id, int healthCareNumber, const QString &name, CareType requiredCareType, CareType receivedCareType, const QVariant &careFacilityId, const QDateTime &dateAdmitted, QObject *parent) :
    QObject(parent),
    id(id),
    healthCareNumber(healthCareNumber),
    name(name),
    requiredCareType(requiredCareType),
    receivingCareType(receivedCareType),
    careFacilityId(careFacilityId),
    dateAdmitted(dateAdmitted)
{

}

int Patient::getID(bool *success) const
{
    return id.toInt(success);
}

int Patient::getHealthCareNumber() const
{
    return healthCareNumber;
}

const QString & Patient::getName() const
{
    return name;
}

void Patient::setName(const QString &first)
{
    name = first;
}

CareType Patient::getRequiredCareType() const
{
    return requiredCareType;
}

void Patient::setRequiredCareType(CareType req)
{
    requiredCareType = req;
}

CareType Patient::getReceivingCareType() const
{
    return receivingCareType;
}

void Patient::setReceivingCareType(const CareType rec)
{
    receivingCareType = rec;
}

int Patient::getReceivingCareFacilityId(bool *ok) const
{
    return careFacilityId.toInt(ok);
}

void Patient::setReceivingCareFacilityId(const QVariant &careFacilityId)
{
    this->careFacilityId = careFacilityId;
}

const QDateTime & Patient::getReceivingCareDateAdmitted() const
{
    return dateAdmitted;
}

void Patient::setDateAdmitted(const QDateTime &dateAdmitted)
{
    this->dateAdmitted = dateAdmitted;
}
