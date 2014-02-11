#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>

#include "object.h"
#include "patient.h"
#include "region.h"

NS_START

class Patient;
class Region;

class Location : public Object
{
public:
    Location();
    virtual ~Location();
    virtual std::string toString() const = 0;
    virtual std::string toUIString() const = 0;
    virtual void validate() const throw(Exception) = 0;
    virtual int getID() const = 0;
    virtual std::string getName() const = 0;
    virtual void setName(const std::string &) = 0;
    virtual int getX() const = 0;
    virtual void setX(const int) = 0;
    virtual int getY() const = 0;
    virtual void setY(const int) = 0;
    virtual int getACBeds() const = 0;
    virtual void setACBeds(const int) = 0;
    virtual int getCCCBeds() const = 0;
    virtual void setCCCBeds(const int) = 0;
    virtual int getLTCBeds() const = 0;
    virtual void setLTCBeds(const int) = 0;
    virtual const std::vector<Patient *> & getPatientList() const = 0;
    virtual void addPatient(Patient * const) = 0;
    virtual void removePatient(const int HCN) = 0;
    virtual Region * getRegion() const = 0;
    virtual void setRegion(Region * const) = 0;
};

NS_END

#endif // LOCATION_H
