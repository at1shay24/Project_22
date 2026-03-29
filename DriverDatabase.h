#ifndef DRIVER_DATABASE_H
#define DRIVER_DATABASE_H

#include "countylist.h"
#include "datelist.h"
#include "DriverNode.h"
#include "HashTable.h"
#include "InactiveDatabase.h"
#include "Vector.h"
#include <iostream>
#include <string>

class DriverDatabase {
    private:
        DateList dateList;
        HashTable<string, DriverNode*> idMap;
        HashTable<string, CountyList*> countyMap;
        InactiveDatabase inactiveDB;
        int totalDrivers;
    public:
        //Constructor
        DriverDatabase();
        //Destructor
        ~DriverDatabase();
        //Insertion
        void addDriver(Driver* d, const string& position = "end", const string& refID = "");
        //Removal
        bool removeByName(const string& driverID);
        //Display
        void displayRecent(int n) const;
        void displayOldest(int n) const;
        //Show inactive
        void showInactive() const;
        //Utility
        int size() const;
};

#endif