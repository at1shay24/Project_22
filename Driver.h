#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "Date.h"
#include "Address.h"
#include "Vector.h" 
#include "Ticket.h"
enum MedicalCondition { FIT, VISION_IMPAIRED, UPPER_EXTREMITY, LOCOMOTOR };
class Driver {
protected:
    std::string name; 
    Date dob; 
    Date licenseDate; 
    Address address; 
    Address workArea; 
    Vector<Address> frequentLocs; 
    Vector<Ticket> tickets; 
    MedicalCondition medical; 
public:
    Driver(std::string n, Date d, Date lic, Address addr, Address work, MedicalCondition med)
        : name(n), dob(d), licenseDate(lic), address(addr), workArea(work), medical(med) {}
    virtual ~Driver() {}
    virtual std::string getEmploymentType() const = 0;
    std::string getName() const { return name; }
    Date getLicenseDate() const { return licenseDate; }
};
#endif