#ifndef PRIVATE_SECTOR_H
#define PRIVATE_SECTOR_H
#include "Driver.h"

class PrivateSector : public Driver {
private:
    static int count;
public:
    PrivateSector(const string& n, Date dob, Date lic, Address addr, Address work, MedicalCondition med)
        : Driver(n, dob, lic, addr, work, med) {}
    string getEmploymentType() const { return "PrivateSector"; }
};
int PrivateSector::count = 0;
#endif