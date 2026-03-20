#include "Driver.h"
class Government : public Driver {
public:
    using Driver::Driver;
    std::string getEmploymentType() const override { return "Government"; } // [cite: 36]
};