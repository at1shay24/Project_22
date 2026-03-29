#ifndef DRIVER_H
#define DRIVER_H

#include "Address.h"
#include "Date.h"
#include "Ticket.h"
#include "Vector.h" 
#include <string>

using namespace std;

enum MedicalCondition { FIT, VISION_IMPAIRED, UPPER_EXTREMITY, LOCOMOTOR };
class Driver {
protected:
    string name; 
    Date dob; 
    Date licenseDate; 
    Address address; 
    Address workArea; 
    Vector<Address> frequentLocs; 
    Vector<Ticket> tickets; 
    MedicalCondition medical; 
public:
    //Constructor
    Driver(const string& n, Date d, Date lic, Address addr, Address work, MedicalCondition med)
        : name(n), dob(d), licenseDate(lic), address(addr), workArea(work), medical(med) {}
    virtual ~Driver() {}

    //Accessors
    string getName() const{return name;}
    Date getLicenseDate() const{return licenseDate;}
    Address getAddress() const{return address;}
    MedicalCondition getMedical() const{return medical;}
    virtual string getEmploymentType() const = 0;
    int getAge() const {return dob.getCurrentYear() - dob.getYear();}
};
#endif