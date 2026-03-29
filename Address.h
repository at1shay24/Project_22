#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
    private:
        string street;
        string city;
        string county;
        string zipCode;

    public:
        //Constructors
        Address(const string &str="123 Main St", const string &city="Anytown",
        const string &county="Denton", const string &zip="12345");
        //Copy Constructor
        Address(const Address &other);
        //Assignment Operator
        Address& operator=(const Address &other);
        //Accessors
        string getStreet() const;
        string getCity() const;
        string getCounty() const;
        string getZip() const;
        //toString Method
        string toString() const;
};
#endif