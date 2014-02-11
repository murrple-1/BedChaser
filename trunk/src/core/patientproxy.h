#ifndef PATIENTPROXY_H
#define PATIENTPROXY_H

#include "patient.h"
#include "patientobject.h"

NS_START

class PatientProxy : public Patient
{
public:
    PatientProxy(const int);
    virtual ~PatientProxy();
    virtual std::string toString() const;
    virtual std::string toUIString() const;
    virtual void validate() const throw(Exception);
    virtual int getHealthCardNumber() const;
    virtual std::string getFirstName(void) const;
    virtual void setFirstName(const std::string &);
    virtual std::string getLastName() const;
    virtual void setLastName(const std::string &);
    virtual CARETYPE getReqCareType(void) const;
    virtual void setReqCareType(const CARETYPE);
    virtual CARETYPE getRecCareType() const;
    virtual void setRecCareType(const CARETYPE);
    virtual Location * getCareLocation() const;
    virtual void setCareLocation(Location * const);
    virtual const std::vector<Region *> & getWaitingRegions() const;
    virtual void addRegion(Region * const);
    virtual void removeRegion(const int);
    virtual const QDateTime * getDateAdmitted() const;
    virtual void setDateAdmitted(QDateTime * const);
    virtual const QDateTime * getDateAddedToWaitingList() const;
    virtual void setDateAddedToWaitingList(QDateTime * const);
private:
    void prepObject() const;

    int healthCardNumber;
    mutable PatientObject * patObj;
};

NS_END

#endif // PATIENTPROXY_H
