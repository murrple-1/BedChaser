#ifndef LOCATIONPROXY_H
#define LOCATIONPROXY_H

#include "location.h"
#include "locationobject.h"

NS_START

class LocationProxy : public Location
{
public:
    LocationProxy(const int);
    virtual ~LocationProxy();
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
    void prepObject() const;
    int id;
    mutable LocationObject * locObject;
};

NS_END

#endif // LOCATIONPROXY_H
