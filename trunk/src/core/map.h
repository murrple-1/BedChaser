#ifndef MAP_H
#define MAP_H

#include <vector>

#include "object.h"
#include "region.h"

NS_START

        class Region;

class Map : public Object
{
public:
    Map();
    Map(const Map &);
    virtual ~Map();
    virtual std::string toString() const;
    virtual std::string toUIString() const;
    virtual void validate() const throw(Exception);
    const std::vector<Region *> & getLocations() const;
    void addRegion(Region * const);
    void removeRegion(const int);
private:
    std::vector<Region *> regions;
};

NS_END

#endif // MAP_H
