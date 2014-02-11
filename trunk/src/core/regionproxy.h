#ifndef REGIONPROXY_H
#define REGIONPROXY_H

#include <vector>

#include "region.h"
#include "regionobject.h"

NS_START

class RegionProxy : public Region
{
public:
    RegionProxy(const int ID);
    virtual ~RegionProxy();
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
    void prepObject() const;

    int id;
    mutable RegionObject * regObj;
};

NS_END

#endif // REGIONPROXY_H
