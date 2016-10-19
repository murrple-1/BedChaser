#ifndef FACILITY_H
#define FACILITY_H

#include <QObject>

#include <QList>
#include <QVariant>

class Facility : public QObject
{
    Q_OBJECT
public:
    Facility(const QVariant &id, const QString &name, int x, int y, int AC, int CCC, int LTC, const QVariant &regionId);

    int getID(bool *ok = 0) const;
    const QString & getName() const;
    int getX() const;
    int getY() const;
    int getNumberOfAcuteCareBeds() const;
    int getNumberOfComplexContinuingCareBeds() const;
    int getNumberOfLongTermCareBeds() const;
    int getRegionId(bool *ok = 0) const;

    void setId(const QVariant &);
    void setName(const QString &);
    void setX(int);
    void setY(int);
    void setNumberOfAcuteCareBeds(int);
    void setNumberOfComplexContinuingCareBeds(int);
    void setNumberOfLongTermCareBeds(int);
    void setRegionId(const QVariant &);
private:
    QVariant id;
    QString name;
    int x;
    int y;
    int numberOfAcuteCareBeds;
    int numberOfComplexContinuingCareBeds;
    int numberOfLongTermCareBeds;
    QVariant regionId;
};

#endif // FACILITY_H
