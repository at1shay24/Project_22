#include "Driver.h"
class Student : public Driver {
public:
    using Driver::Driver;
    std::string getEmploymentType() const override { return "Student"; } // [cite: 34]
};