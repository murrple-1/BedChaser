#ifndef LOCATIONOBJECT_H
#define LOCATIONOBJECT_H

#include "location.h"

NS_START

class LocationObject : public Location
{
public:
    LocationObject(const int ID, const std::string name, const int anX, const int aY, const int AC, const int CCC, const int LTC);
    LocationObject(const LocationObject &);
    virtual ~LocationObject();
    virtual std::string toString() const;
    virtual std::string toUIString() const;
    virtual void validate() const throw(Exception);
    virtual int getID() const;
    virtual std::string getName() const;
    virtual void setName(const std::string &);
    virtual int getX() const;
    virtual void setX(const int);
    virtual int getY() const;
    virtual void setY(const int);
    virtual int getACBeds() const;
    virtual void setACBeds(const int);
    virtual int getCCCBeds() const;
    virtual void setCCCBeds(const int);
    virtual int getLTCBeds() const;
    virtual void setLTCBeds(const int);
    virtual const std::vector<Patient *> & getPatientList() const;
    virtual void addPatient(Patient * const);
    virtual void removePatient(const int HCN);
    virtual Region * getRegion() const;
    virtual void setRegion(Region * const);
private:
    int id;
    std::string name;
    int x;
    int y;
    int ACBeds;
    int CCCBeds;
    int LTCBeds;
    std::vector<Patient *> patientsInCare;
    Region * region;
};

NS_END

#endif // LOCATIONOBJECT_H
