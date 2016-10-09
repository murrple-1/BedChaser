#include "map.h"

Map::Map()
{

}

const QList<int> & Map::getRegionIds() const
{
    return regionIds;
}

void Map::addRegionId(int regionId)
{
    regionIds.append(regionId);
}

void Map::removeRegionId(int index)
{
    regionIds.removeAt(index);
}
