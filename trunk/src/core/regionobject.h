#ifndef REGIONOBJECT_H
#define REGIONOBJECT_H

#include <vector>

#include "region.h"

NS_START

class RegionObject : public Region
{
public:
    RegionObject(const int ID, const std::string &);
    RegionObject(const RegionObject &);
    virtual ~RegionObject();
    virtual std::string toString() const;
    virtual std::string toUIString() const;
    virtual void validate() const throw(Exception);
    virtual int getID() const;
    virtual std::string getName() const;
    virtual const std::vector<Location *> & getLocations() const;
    virtual void addLocation(Location * const);
    virtual void removeLocation(const int ID);
    virtual const std::vector<Patient *> & getPatients() const;
    virtual void addPatient(Patient * const);
    virtual void removePatient(const int HCN);
private:
    int id;
    std::string name;
    std::vector<Location *> locations;
    std::vector<Patient *> waitingList;
};

NS_END

#endif // REGIONOBJECT_H
