#ifndef DATE_H
#define DATE_H

#include <ostream>
#include <string>
using namespace std;

class Date{
    private:
        int day;
        int month;
        int year;

    public:
        //Constructor
        Date(int d = 1, int m =1, int y = 1900);
        
        //Destructor
        ~Date();
        
        //Copy Constructor
        Date(const Date &other);
        
        //Assignment Operator
        Date& operator=(const Date &other);
        
        //Equality Operator
        bool operator==(const Date &other) const;
        
        //Less Than Operator
        bool operator<(const Date &other) const;
        
        //Accessors
        int getDay() const;
        int getMonth() const;
        int getYear() const;
        
        //Mutators
        bool setDay(int d);
        bool setMonth(int m);

        //Utility
        static int getCurrentYear();
        bool setYear(int y);
        string toString() const;

        //Stream Insertion Operator
        friend ostream &operator<<(ostream &os, const Date &d);
};
#endif