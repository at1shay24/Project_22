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
    string id;
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
        Driver(const string& id, const string& n, Date d, Date lic,
           Address addr, Address work, MedicalCondition med)
        : id(id), name(n), dob(d), licenseDate(lic), address(addr),
          workArea(work), medical(med) {}
    virtual ~Driver() {}

    //Accessors
    string getName() const{return name;}
    Date getLicenseDate() const{return licenseDate;}
    Address getAddress() const{return address;}
    virtual string getEmploymentType() const = 0;
    string getID() const { return id; }
    int getAge() const {
    return Date::getCurrentYear() - dob.getYear();
    }
    string getAgeCategory() const {
    int age = getAge();
    if(age <= 28) return "Youth";
    else if(age <= 50) return "Middle-aged";
    else return "Senior";
    }
    int getExperienceYears() const {
    return Date::getCurrentYear() - licenseDate.getYear();
    }
    string getExperienceCategory() const {
    int exp = getExperienceYears();
    if(exp <= 5) return "New";
    else if(exp <= 15) return "Moderate";
    else return "Highly Experienced";
    }
};
#endif