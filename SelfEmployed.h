#ifndef SELF_EMPLOYED_H
#define SELF_EMPLOYED_H
#include "Driver.h"

class SelfEmployed : public Driver {
private:
    static int count;
public:
    SelfEmployed(const string& n, Date dob, Date lic, Address addr, Address work, MedicalCondition med)
        : Driver(n, dob, lic, addr, work, med) {}
    string getEmploymentType() const { return "SelfEmployed"; }
};
int SelfEmployed::count = 0;
#endif