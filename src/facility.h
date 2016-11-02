#ifndef FACILITY_H
#define FACILITY_H

#include <QObject>

#include <QList>
#include <QVariant>
#include <QPoint>

class Facility : public QObject
{
    Q_OBJECT
public:
    Facility(const QVariant &id, const QString &name, const QPoint &mapOffset, int numberOfAcuteCareBeds, int numberOfComplexContinuingCareBeds, int numberOfLongTermCareBeds, const QVariant &regionId, QObject *parent = 0);

    int getID(bool *ok = 0) const;
    const QString & getName() const;
    const QPoint & getMapOffset() const;
    int getNumberOfAcuteCareBeds() const;
    int getNumberOfComplexContinuingCareBeds() const;
    int getNumberOfLongTermCareBeds() const;
    int getRegionId(bool *ok = 0) const;

    void setId(const QVariant &);
    void setName(const QString &);
    void setMapOffset(const QPoint &);
    void setNumberOfAcuteCareBeds(int);
    void setNumberOfComplexContinuingCareBeds(int);
    void setNumberOfLongTermCareBeds(int);
    void setRegionId(const QVariant &);
private:
    QVariant id;
    QString name;
    QPoint mapOffset;
    int numberOfAcuteCareBeds;
    int numberOfComplexContinuingCareBeds;
    int numberOfLongTermCareBeds;
    QVariant regionId;
};

#endif // FACILITY_H
