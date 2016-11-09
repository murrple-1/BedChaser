#include "region.h"

Region::Region(const QVariant &id, const QString &name, const QFileInfo &subMapFileInfo, const QPoint &mapOffset, QObject *parent) :
    QObject(parent),
    id(id),
    name(name),
    subMapFileInfo(subMapFileInfo),
    mapOffset(mapOffset)
{

}

int Region::getID(bool *ok) const
{
    return id.toInt(ok);
}

const QString & Region::getName() const
{
    return name;
}

const QFileInfo & Region::getSubMapFileInfo() const
{
    return subMapFileInfo;
}

const QPoint & Region::getMapOffset() const
{
    return mapOffset;
}
