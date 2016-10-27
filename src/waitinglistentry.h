#ifndef WAITINGLISTENTRY_H
#define WAITINGLISTENTRY_H

#include <QObject>

#include <QDateTime>

class WaitingListEntry : public QObject
{
public:
    WaitingListEntry(int regionId, int patientId, const QDateTime &dateAdded, QObject *parent = 0);

    int getRegionId() const;
    int getPatientId() const;
    const QDateTime & getDateAdded() const;
private:
    int regionId;
    int patientId;
    QDateTime dateAdded;
};

#endif // WAITINGLISTENTRY_H
