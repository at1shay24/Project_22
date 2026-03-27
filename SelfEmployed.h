#include "Driver.h"
class SelfEmployed : public Driver {
    public:
    using Driver::Driver;
    std::string getEmploymentType() const override { return "Self-Employed"; }
};