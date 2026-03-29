#include "Address.h"

//Constructor
Address::Address(const string &str, const string &city,
    const string &county, const string &zip) : street(str), city(city), county(county), zipCode(zip) {}

//Copy Constructor
Address::Address(const Address &other) : street(other.street), city(other.city), county(other.county), zipCode(other.zipCode) {}

//Copy Constructor
Address &Address::operator=(const Address &other) {
    if (this != &other) {
        street = other.street;
        city = other.city;
        county = other.county;
        zipCode = other.zipCode;
    }
    return *this;
}

string Address::getStreet() const {return street;}
string Address::getCity() const {return city;}
string Address::getCounty() const {return county;}
string Address::getZip() const {return zipCode;}

string Address::toString() const {
    return street + ", " + city + ", " + county + " TX, " + zipCode;
}