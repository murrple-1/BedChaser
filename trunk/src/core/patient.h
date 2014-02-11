#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>
#include <QDateTime>

#include "object.h"
#include "region.h"
#include "location.h"

NS_START

class Location;
class Region;

enum CARETYPE {
    NONE,       //0
    CCC,        //1
    LTC,        //2
    AC          //3
};

class Patient : public Object
{
public:
    Patient();
    virtual ~Patient();
    virtual std::string toString() const = 0;
    virtual std::string toUIString() const = 0;
    virtual void validate() const throw(Exception) = 0;
    virtual int getHealthCardNumber() const = 0;
    virtual std::string getFirstName(void) const = 0;
    virtual void setFirstName(const std::string &) = 0;
    virtual std::string getLastName() const = 0;
    virtual void setLastName(const std::string &) = 0;
    virtual CARETYPE getReqCareType(void) const = 0;
    virtual void setReqCareType(const CARETYPE) = 0;
    virtual CARETYPE getRecCareType() const = 0;
    virtual void setRecCareType(const CARETYPE) = 0;
    virtual Location * getCareLocation() const = 0;
    virtual void setCareLocation(Location * const) = 0;
    virtual const std::vector<Region *> & getWaitingRegions() const = 0;
    virtual void addRegion(Region * const) = 0;
    virtual void removeRegion(const int) = 0;
    virtual const QDateTime * getDateAdmitted() const = 0;
    virtual void setDateAdmitted(QDateTime * const) = 0;
    virtual const QDateTime * getDateAddedToWaitingList() const = 0;
    virtual void setDateAddedToWaitingList(QDateTime * const) = 0;
};

NS_END

#endif // PATIENT_H
