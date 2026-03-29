/*Author:       Murphy Jacob, Atishay Jain
 *Date:         03/17/26
 *Description:  
 *Instructor:   Bhaskar Trivedi
 *Date:         03/19/26
 *Description:  Main entry point for Driver Management System
 *Instructor:   Bhaskar Trivedi*/
/*TODO LIST:
Todd: CountyList and DateList implementation
*/
#include "Address.h"
#include "Date.h"
#include "DriverDatabase.h"
#include "DriverNode.h"
#include "Government.h"
#include "InactiveDatabase.h"
#include "SelfEmployed.h"
#include "Student.h"
#include "Ticket.h"
#include "Vector.h"
#include "BusinessOwner.h"
#include "PrivateSector.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

 DriverDatabase activeDB;


 void loadFromFile(const std::string &filename);
 void showMenu();
 void addDriver();
 void removeDriver();
 void getMostRecent(int n);
 void getOldest(int n);
 void exitProgram();

int main(){
    std::cout << "-== Driver Database ==-" << std::endl;
    loadFromFile("drivers.dat");

    int choice = 0;
    do{
        showMenu();
        if(!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a choice between 1 and 5: ";
            continue;
        }
        switch(choice){
            case 1:
                addDriver();
                break;
            case 2:
                removeDriver();
                break;
            case 3: {
                int n;
                cout << "Enter the number of most recent drivers to display: ";
                if(!(cin >> n)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else {
                    getMostRecent(n);
                }
                break;
            }
            case 4: {
                int n;
                cout << "Enter the number of oldest drivers to display: ";
                if(!(cin >> n)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else {
                    getOldest(n);
                }
                break;
            }
            case 5:
                exitProgram();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }while (choice != 5);
    return 0;
}

void showMenu(){
    cout << "\n--- City Driver Database Menu ---" << endl;
    cout << "1. Add New Driver Record" << endl;
    cout << "2. Remove/Migrate Driver" << endl;
    cout << "3. View N Most Recent Licenses" << endl;
    cout << "4. View N Oldest Licenses" << endl;
    cout << "5. Exit System" << endl;
    cout << "Selection: ";
}

void loadFromFile(const string &filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    int count = 0;
    while(getline(file, line) && count <= 100){
        if(line.empty()) continue;
        stringstream ss(line);

        //Name
        string name;
        getline(ss, name, ',');
        if(name.empty()) continue;
        getline(ss, sDay, ','); getline(ss, sMonth, ','); getline(ss, sYear, ',');

        //License Issue Date (d,m,yyyy)
        string lDay, lMonth, lYear;
        getline(ss, lDay, ','); getline(ss, lMonth, ','); getline(ss, lYear, ',');

        //Home Address
        string hStreet, hCity, hCounty, hZip;
        getline(ss, hStreet, ','); getline(ss, hCity, ',');
        getline(ss, hCounty, ','); getline(ss, hZip, ',');

        //Work Address
        string wStreet, wCity, wCounty, wZip;
        getline(ss, wStreet, ','); getline(ss, wCity, ',');
        getline(ss, wCounty, ','); getline(ss, wZip, ',');

        //Driver Type and Medical Condition
        string type, medStr;
        getline(ss, type, ',');
        type.erase(remove(type.begin(), type.end(), '\r'), type.end());
        getline(ss, medStr, ',');  // medical condition as string
        medStr.erase(remove(medStr.begin(), medStr.end(), '\r'), medStr.end());

        if(medStr.empty()) continue;
        int medInt = stoi(medStr);
        MedicalCondition med;
        switch(medInt){
            case 0:  med = FIT;              break;
            case 1:  med = VISION_IMPAIRED;  break;
            case 2:  med = UPPER_EXTREMITY;  break;
            case 3:  med = LOCOMOTOR;        break;
            default: med = FIT;              break;
        }

        Date    dob(stoi(sDay),  stoi(sMonth),  stoi(sYear));
        Date    lic(stoi(lDay),  stoi(lMonth),  stoi(lYear));
        Address homeAddr(hStreet, hCity, hCounty, hZip);
        Address workAddr(wStreet, wCity, wCounty, wZip);

        Driver* d = nullptr;
        Date dob(std::stoi(sDay), std::stoi(sMonth), std::stoi(sYear));
        Date lic(std::stoi(lDay), std::stoi(lMonth), std::stoi(lYear));
        Address addr(street, city, county, zip);

        if(type == "Student") 
            d = new Student(name, dob, lic, addr, addr, med);
        else if(type == "Government")
            d = new Government(name, dob, lic, addr, addr, med);
        else if(type == "SelfEmployed")
            d = new SelfEmployed(name, dob, lic, addr, addr, med);
        else if(type == "BusinessOwner")
            d = new BusinessOwner(name, dob, lic, addr, addr, med);
        else if(type == "PrivateSector")
            d = new PrivateSector(name, dob, lic, addr, addr, med);
        
        if(d) activeDB.addDriver(d);
        count++;
    }
    file.close();
    std::cout << "Loaded " << count << " drivers from file." << std::endl;
}

void addDriver(){
    std::string name, street, city, county, zip;
    int d, m, y, ld, lm, ly, typeChoice;
    
    std::cout << "--- Adding a New Driver ---" << std::endl;
    std::cin.ignore();
    std::cout << "Name: "; std::getline(std::cin, name);
    std::cout << "DOB (D M Y): "; std::cin >> d >> m >> y;
    std::cout << "License Date (D M Y): "; std::cin >> ld >> lm >> ly;
    std::cin.ignore();
    std::cout << "Street: "; std::getline(std::cin, street);
    std::cout << "City: "; std::getline(std::cin, city);
    std::cout << "County: "; std::getline(std::cin, county);
    std::cout << "Zip: "; std::getline(std::cin, zip);
    std::cout << "Type (1. Student, 2. Government, 3. Self Employed, 4. Business Owner, 5. Private Sector): ";
    std::cin >> typeChoice;

    Driver* newDriver = nullptr;
    if(typeChoice == 1) newDriver = new Student(name, Date(d,m,y), Date(ld,lm,ly), Address(street, city, county, zip), Address(), FIT);
    else if(typeChoice == 2) newDriver = new Government(name, Date(d,m,y), Date(ld,lm,ly), Address(street, city, county, zip), Address(), FIT);
    else if(typeChoice == 3) newDriver = new SelfEmployed(name, Date(d,m,y), Date(ld,lm,ly), Address(street, city, county, zip), Address(), FIT);
    else if(typeChoice == 4) newDriver = new BusinessOwner(name, Date(d,m,y), Date(ld,lm,ly), Address(street, city, county, zip), Address(), FIT);
    else newDriver = new PrivateSector(name, Date(d,m,y), Date(ld,lm,ly), Address(street, city, county, zip), Address(), FIT);
    
    activeDB.addDriver(newDriver);
}

void removeDriver(){
    std::string name;
    std::cout << "--- Removing a Driver ---" << std::endl;
    std::cout << "Enter Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
   bool removed = activeDB.removeByName(name);
    if(removed) {
    std::cout << "Driver moved to inactive database." << std::endl;
    } else {
    std::cout << "Driver not found." << std::endl;
    }
}

void getMostRecent(int n){
    std::cout << "Displaying the " << n << " most recent drivers:" << std::endl;
    activeDB.displayRecent(n);
}

void getOldest(int n){
    std::cout << "Displaying the " << n << " oldest drivers:" << std::endl;
    activeDB.displayOldest(n);
}

void exitProgram(){
    std::cout << "Exiting the Database. Thank You and Goodbye!" << std::endl;
}