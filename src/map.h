#ifndef MAP_H
#define MAP_H

#include <QObject>

#include <QList>

class Region;

class Map : public QObject
{
    Q_OBJECT
public:
    Map();

    const QList<int> & getRegionIds() const;
    void addRegionId(int);
    void removeRegionId(int index);
private:
    QList<int> regionIds;
};

#endif // MAP_H
