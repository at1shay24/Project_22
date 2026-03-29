#ifndef SELF_EMPLOYED_H
#define SELF_EMPLOYED_H
#include "Driver.h"
#include <string>

class SelfEmployed : public Driver {
public:
    SelfEmployed(const string& n, Date dob, Date lic, Address addr, Address work, MedicalCondition med)
        : Driver("SE", n, dob, lic, addr, work, med) {}
    string getEmploymentType() const override { return "SelfEmployed"; }
};
#endif