#ifndef PATIENTOBJECT_H
#define PATIENTOBJECT_H

#include "patient.h"

NS_START

class PatientObject : public Patient
{
public:
    PatientObject(const int HCN, const std::string & first, const std::string & last, const CARETYPE req);
    PatientObject(const PatientObject &);
    virtual ~PatientObject();
    virtual std::string toString() const;
    virtual std::string toUIString() const;
    virtual void validate() const throw(Exception);
    int getHealthCardNumber() const;
    std::string getFirstName(void) const;
    void setFirstName(const std::string &);
    std::string getLastName() const;
    void setLastName(const std::string &);
    CARETYPE getReqCareType(void) const;
    void setReqCareType(const CARETYPE);
    CARETYPE getRecCareType() const;
    void setRecCareType(const CARETYPE);
    Location * getCareLocation() const;
    void setCareLocation(Location * const);
    const std::vector<Region *> & getWaitingRegions() const;
    void addRegion(Region * const);
    void removeRegion(const int);
    const QDateTime * getDateAdmitted() const;
    std::string getDateAdmittedToString() const;
    void setDateAdmitted(QDateTime * const);
    const QDateTime * getDateAddedToWaitingList() const;
    std::string getDateAddedToWaitingListToString() const;
    void setDateAddedToWaitingList(QDateTime * const);
private:
    int healthCardNumber;
    std::string firstName;
    std::string lastName;
    CARETYPE requiredCare;
    CARETYPE receivedCare;
    Location * careLocation;
    std::vector<Region *> regionsWaiting;
    QDateTime * dateAdmitted;
    QDateTime * dateAddedToWaitingList;
};

NS_END

#endif // PATIENTOBJECT_H
