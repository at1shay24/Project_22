#ifndef GOVERNMENT_H
#define GOVERNMENT_H
#include "Driver.h"

class Government : public Driver {
private:
    static int count;
public:
    Government(const string& n, Date dob, Date lic, Address addr, Address work, MedicalCondition med)
        : Driver(n, dob, lic, addr, work, med) {}
    string getEmploymentType() const { return "Government"; }
};
int Government::count = 0;
#endif