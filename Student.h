#ifndef STUDENT_H
#define STUDENT_H
#include "Driver.h"
#include <string>

class Student : public Driver {
public:
    Student(const string& n, Date dob, Date lic, Address addr, Address work, MedicalCondition med)
        : Driver("STU", n, dob, lic, addr, work, med) {}
    string getEmploymentType() const override { return "Student"; }
};
#endif