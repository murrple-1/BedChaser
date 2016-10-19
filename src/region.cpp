#include "region.h"

Region::Region(const QVariant &id, const QString &name, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->name = name;
}

int Region::getID(bool *ok) const
{
    return id.toInt(ok);
}

const QString & Region::getName() const
{
    return name;
}
