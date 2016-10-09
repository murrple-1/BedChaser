#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>

#include <QList>
#include <QVariant>
#include <QDateTime>

typedef enum
{
    NONE,
    CCC,
    LTC,
    AC
} CARETYPE;

class Patient : public QObject
{
    Q_OBJECT
public:
    Patient(int HCN, const QString &first, const QString &last, CARETYPE req);

    int getHealthCardNumber() const;
    const QString & getFirstName() const;
    const QString & getLastName() const;
    CARETYPE getReqCareType() const;
    CARETYPE getRecCareType() const;
    int getCareLocationId(bool *ok = 0) const;
    const QList<int> & getWaitingRegions() const;
    const QDateTime & getDateAdmitted() const;
    const QDateTime & getDateAddedToWaitingList() const;

    void setFirstName(const QString &);
    void setLastName(const QString &);
    void setRequiredCareType(CARETYPE);
    void setReceivedCareType(CARETYPE);
    void setCareLocationId(const QVariant &);
    void addWaitingRegionId(int);
    void removeWaitingRegionId(int);
    void setDateAdmitted(const QDateTime &);
    void setDateAddedToWaitingList(const QDateTime &);
private:
    int healthCardNumber;
    QString firstName;
    QString lastName;
    CARETYPE requiredCare;
    CARETYPE receivedCare;
    QVariant careLocationId;
    QList<int> waitingRegionIds;
    QDateTime dateAdmitted;
    QDateTime dateAddedToWaitingList;
};

#endif // PATIENT_H
