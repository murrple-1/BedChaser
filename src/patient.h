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
    Patient(const QVariant &id, int healthCardNumber, const QString &name, CareType requiredCareType, CareType receivingCareType, const QVariant &careFacilityId, const QDateTime &dateAdmitted);

    int getId(bool *success = 0) const;
    int getHealthCardNumber() const;
    const QString & getName() const;
    CareType getRequiredCareType() const;
    CareType getReceivingCareType() const;
    int getReceivingCareFacilityId(bool *ok = 0) const;
    const QDateTime & getReceivingCareDateAdmitted() const;

    void setName(const QString &);
    void setRequiredCareType(CareType);
    void setReceivingCareType(CareType);
    void setReceivingCareFacilityId(const QVariant &);
    void setDateAdmitted(const QDateTime &);
private:
    QVariant id;
    int healthCardNumber;
    QString name;
    CareType requiredCareType;
    CareType receivingCareType;
    QVariant careFacilityId;
    QDateTime dateAdmitted;
};

#endif // PATIENT_H
