#include "Driver.h"
class Government : public Driver {
    public:
        using Driver::Driver;
        Government(const string &name, const string &id, Date dob, Date lic,
        Address addr, Address work, MedicalCondition med) : 
        Driver(name, id, dob, lic, addr, work, med) {}
        string getEmploymentType() const { return "Government"; }
};