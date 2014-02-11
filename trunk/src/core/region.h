#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>

#include "object.h"
#include "location.h"
#include "patient.h"

NS_START

class Patient;
class Location;

class Region : public Object
{
public:
    Region();
    virtual ~Region();
    virtual std::string toString() const = 0;
    virtual std::string toUIString() const = 0;
    virtual void validate() const throw(Exception) = 0;
    virtual int getID() const = 0;
    virtual std::string getName() const = 0;
    virtual const std::vector<Location *> & getLocations() const = 0;
    virtual void addLocation(Location * const) = 0;
    virtual void removeLocation(const int ID) = 0;
    virtual const std::vector<Patient *> & getPatients() const = 0;
    virtual void addPatient(Patient * const) = 0;
    virtual void removePatient(const int HCN) = 0;
};

NS_END

#endif // REGION_H
