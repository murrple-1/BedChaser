#ifndef REGION_H
#define REGION_H

#include <QObject>

#include <QList>
#include <QVariant>
#include <QFileInfo>
#include <QPoint>

class Region : public QObject
{
    Q_OBJECT
public:
    Region(const QVariant &id, const QString &name, const QFileInfo &subMapFileInfo, const QPoint &mapOffset, QObject *parent = 0);

    int getID(bool *ok = 0) const;
    const QString & getName() const;
    const QFileInfo & getSubMapFileInfo() const;
    const QPoint & getMapOffset() const;
private:
    QVariant id;
    QString name;
    QFileInfo subMapFileInfo;
    QPoint mapOffset;
};

#endif // REGION_H
