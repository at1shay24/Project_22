#include "Date.h"
#include <sstream>
#include <iomanip>

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    //TODO: Add validation for day/month/year ranges. Assume input is invalid for now
}

Date::Date(const Date &other) : day(other.day), month(other.month), year(other.year) {}

Date::~Date() {}

Date &Date::operator=(const Date &other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

bool Date::operator==(const Date &other) const {
    return (day == other.day && month == other.month && year == other.year);
}

bool Date::operator<(const Date &other) const {
    if (year < other.year) return true;
    if (year == other.year && month < other.month) return true;
    if (year == other.year && month == other.month && day < other.day) return true;
    return false;
}

int Date::getDay() const {return day;}
int Date::getMonth() const {return month;}
int Date::getYear() const {return year;}

bool Date::setDay(int d) {
    if(d < 1 || d > 31) {
        throw std::invalid_argument("Day must be between 1 and 31");
        return false;
    }
    day = d;
    return true;
}
bool Date::setMonth(int m) {
    if(m < 1 || m > 12) {
        throw std::invalid_argument("Month must be between 1 and 12");
        return false;
    }
    month = m;
    return true;
}

int Date::getCurrentYear() {
    time_t t = time(nullptr);
    tm* currentTime = localtime(&t);
    return currentTime->tm_year + 1900;
}

bool Date::setYear(int y) {
    int currentYear = getCurrentYear();
    if(y < 1900 || y > currentYear + 100) {
        throw std::invalid_argument("Year must be between 1900 and " + std::to_string(currentYear + 100));
        return false;
    }
    year = y;
    return true;
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << month << "/" << std::setw(2) << day << "/" << std::setw(4) << year;
    return oss.str();
}