#ifndef REGION_H
#define REGION_H

#include <QObject>

#include <QList>
#include <QVariant>

class Region : public QObject
{
    Q_OBJECT
public:
    Region(const QVariant &id, const QString &name, QObject *parent = 0);

    int getID(bool *ok = 0) const;
    const QString & getName() const;
    const QList<int> & getFacilityIds() const;
    const QList<int> & getWaitingListPatientIds() const;

    void addFacilityId(int id);
    void removeFacilityId(int index);
    void addWaitingListPatientId(int id);
    void removeWaitingListPatientId(int index);
private:
    QVariant id;
    QString name;
    QList<int> facilityIds;
    QList<int> waitingListPatientIds;
};

#endif // REGION_H
