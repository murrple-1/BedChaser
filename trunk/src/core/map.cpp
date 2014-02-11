#include "map.h"
#include "../utils/stringbuilder.h"

#include "QsLog.h"
#include "QsLogDest.h"

NS_START

        Map::Map()
{}

Map::Map(const Map & m)
{
    std::vector<Region *>::const_iterator iter;
    for(iter = m.getLocations().begin(); iter != m.getLocations().end(); iter++) {
        addRegion(*iter);
    }
}

Map::~Map()
{}

std::string Map::toString() const
{
    StringBuilder sb;
    sb.append(std::string("Map: "));
    sb.append(std::string("regions=["));
    std::vector<Region *>::const_iterator regIter;
    for(regIter = regions.begin(); regIter != regions.end(); regIter++) {
        sb.append((*regIter)->getID()).append(',');
    }
    sb.append(']');
    return sb.toString();
}

std::string Map::toUIString() const
{
    return "";
}

void Map::validate() const throw(Exception)
{

}

const std::vector<Region *> & Map::getLocations() const {
    return regions;
}

void Map::addRegion(Region * const r) {

    QLOG_INFO() << "Map::addRegion\n";

    try {
        regions.push_back(r);
        QLOG_INFO() << "Adding a region to the map was successful " << r->toString().c_str() << "\n";
    }
    catch(Exception & e) {
        QLOG_ERROR() << "Adding a region to the map failed " << r->toString().c_str() << "\n"
                << " Cause: " << e.getCause().c_str() << "\n" << "Message: " << e.getMessage().c_str() << "\n";
    }
}

void Map::removeRegion(const int ID) {

    QLOG_INFO() << "Map::removeRegion\n";

    std::vector<Region *>::iterator iter;

    try {
        for(iter = regions.begin(); iter != regions.end(); iter++) {
            if(ID == (*iter)->getID()) {
                regions.erase(iter);
                break;
            }
        }
        QLOG_INFO() << "Removing a region from the map was successful " << ID << "\n";
    }
    catch(Exception & e) {
        QLOG_ERROR() << "Removing a region from a map failed " << ID << "\n"
                << " Cause: " << e.getCause().c_str() << "\n" << "Message: " << e.getMessage().c_str() << "\n";
    }
}

NS_END
