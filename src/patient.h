#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>

#include <QList>
#include <QVariant>
#include <QDateTime>

typedef enum
{
    CareTypeNone,
    CareTypeComplexContinuingCare,
    CareTypeLongTermCare,
    CareTypeAcuteCare
} CareType;

class Patient : public QObject
{
    Q_OBJECT
public:
    Patient(int HCN, const QString &first, const QString &last, CareType req);

    int getHealthCardNumber() const;
    const QString & getFirstName() const;
    const QString & getLastName() const;
    CareType getReqCareType() const;
    CareType getRecCareType() const;
    int getCareFacilityId(bool *ok = 0) const;
    const QList<int> & getWaitingRegions() const;
    const QDateTime & getDateAdmitted() const;
    const QDateTime & getDateAddedToWaitingList() const;

    void setFirstName(const QString &);
    void setLastName(const QString &);
    void setRequiredCareType(CareType);
    void setReceivedCareType(CareType);
    void setCareFacilityId(const QVariant &);
    void addWaitingRegionId(int);
    void removeWaitingRegionId(int);
    void setDateAdmitted(const QDateTime &);
    void setDateAddedToWaitingList(const QDateTime &);
private:
    int healthCardNumber;
    QString firstName;
    QString lastName;
    CareType requiredCare;
    CareType receivedCare;
    QVariant careFacilityId;
    QList<int> waitingRegionIds;
    QDateTime dateAdmitted;
    QDateTime dateAddedToWaitingList;
};

#endif // PATIENT_H
