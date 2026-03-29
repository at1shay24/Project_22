#ifndef STUDENT_H
#define STUDENT_H
#include "Driver.h"

class Student : public Driver {
private:
    static int count;
public:
    Student(const string& n, Date dob, Date lic, Address addr, Address work, MedicalCondition med)
        : Driver("STU" + to_string(++count), n, dob, lic, addr, work, med) {}
    string getEmploymentType() const override { return "Student"; }
};
int Student::count = 0;
#endif