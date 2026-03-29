#ifndef BUSINESS_OWNER_H
#define BUSINESS_OWNER_H
#include "Driver.h"

class BusinessOwner : public Driver {
private:
    static int count;
public:
    BusinessOwner(const string& n, Date dob, Date lic, Address addr, Address work, MedicalCondition med)
        : Driver(n, dob, lic, addr, work, med) {}
    string getEmploymentType() const { return "BusinessOwner"; }
};
int BusinessOwner::count = 0;
#endif