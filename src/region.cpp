#include "region.h"

Region::Region(const QVariant &id, const QString &name, int x, int y, QObject *parent) :
    QObject(parent),
    id(id),
    name(name),
    x(x),
    y(y)
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

int Region::getX() const
{
    return x;
}

int Region::getY() const
{
    return y;
}
