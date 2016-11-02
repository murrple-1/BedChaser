#ifndef REGION_H
#define REGION_H

#include <QObject>

#include <QList>
#include <QVariant>
#include <QPoint>

class Region : public QObject
{
    Q_OBJECT
public:
    Region(const QVariant &id, const QString &name, const QPoint &mapOffset, QObject *parent = 0);

    int getID(bool *ok = 0) const;
    const QString & getName() const;
    const QPoint & getMapOffset() const;
private:
    QVariant id;
    QString name;
    QPoint mapOffset;
};

#endif // REGION_H
