#include "Driver.h"
class SelfEmployed : public Driver {
    public:
        using Driver::Driver;
        SelfEmployed(const string &name, const string &id, Date dob, Date  lice,
        Address addr, Address work, MedicalCondition med) : 
        Driver(name, id, dob, lic, addr, work, med){}
        string getEmploymentType() const { return "Self-Employed"; }
};