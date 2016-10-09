#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>

#include <QList>
#include <QVariant>

class Location : public QObject
{
    Q_OBJECT
public:
    Location(const QVariant &id, const QString &name, int x, int y, int AC, int CCC, int LTC);

    int getID(bool *ok = 0) const;
    const QString & getName() const;
    int getX() const;
    int getY() const;
    int getACBeds() const;
    int getCCCBeds() const;
    int getLTCBeds() const;
    const QList<int> & getPatientsInCareIds() const;
    int getRegionId(bool *ok = 0) const;

    void setId(const QVariant &);
    void setName(const QString &);
    void setX(int);
    void setY(int);
    void setACBeds(int);
    void setCCCBeds(int);
    void setLTCBeds(int);
    void addPatientInCareId(int id);
    void removePatientInCareId(int index);
    void setRegionId(const QVariant &);
private:
    QVariant id;
    QString name;
    int x;
    int y;
    int ACBeds;
    int CCCBeds;
    int LTCBeds;
    QList<int> patientsInCare;
    QVariant regionId;
};

#endif // LOCATION_H
