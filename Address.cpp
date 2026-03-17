#include "Address.h"

Address::Address(const std::string & str, const std::string &city,
    const std::string &county, const std::string &zip) : street(str), city(city), county(county), zipCode(zip) {}

Address::Address(const Address &other) : street(other.street), city(other.city), county(other.county), zipCode(other.zipCode) {}

Address &Address::operator=(const Address &other) {
    if (this != &other) {
        street = other.street;
        city = other.city;
        county = other.county;
        zipCode = other.zipCode;
    }
    return *this;
}

std::string Address::getStreet() const {return street;}
std::string Address::getCity() const {return city;}
std::string Address::getCounty() const {return county;}
std::string Address::getZip() const {return zipCode;}

std::string Address::toString() const {
    return street + ", " + city + ", " + county + " TX, " + zipCode;
}