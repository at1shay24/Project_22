#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
    private:
        std::string street;
        std::string city;
        std::string county;
        std::string zipCode;

    public:
        //Constructors
        Address(const std::string &str="123 Main St", const std::string &city="Anytown",
        const std::string &county="Denton", const std::string &zip="12345");
        //Copy Constructor
        Address(const Address &other);
        //Assignment Operator
        Address& operator=(const Address &other);
        //Accessors
        std::string getStreet() const;
        std::string getCity() const;
        std::string getCounty() const;
        std::string getZip() const;
        //toString Method
        std::string toString() const;
};
#endif