#ifndef GOVERNMENT_H
#define GOVERNMENT_H
#include "Driver.h"
#include <string>

class Government : public Driver {
public:
    Government(const string& n, Date dob, Date lic, Address addr, Address work, MedicalCondition med)
        : Driver("GOV", n, dob, lic, addr, work, med) {}
    string getEmploymentType() const override { return "Government"; }
};
#endif