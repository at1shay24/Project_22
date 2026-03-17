#ifndef DATE_H
#define DATE_H

#include <string>

class Date{
    private:
        int day;
        int month;
        int year;

    public:
        //TODO: Constructors
        Date(int d = 1, int m =1, int y = 1900);
        //TODO: Destructor
        ~Date();
        //TODO: Copy Constructor
        Date(const Date &other);
        //TODO: Assignment Operator
        Date& operator=(const Date &other);
        //TODO: Equality Operator
        bool operator==(const Date &other) const;
        //TODO: Less Than Operator
        bool operator<(const Date &other) const;
        //TODO: Accessors
        int getDay() const;
        int getMonth() const;
        int getYear() const;
        //TODO: Mutators
        bool setDay(int d);
        bool setMonth(int m);
        //TODO getCurrentYear Helper Function
        static int getCurrentYear();
        bool setYear(int y);
        //TODO: toString Utility
        std::string toString() const;
};
#endif