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
        if(!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a choice between 1 and 5: ";
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
                std::cout << "Enter the number of most recent drivers to display: ";
                if(!(std::cin >> n)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                } else {
                    getMostRecent(n);
                }
                break;
            }
            case 4: {
                int n;
                std::cout << "Enter the number of oldest drivers to display: ";
                if(!(std::cin >> n)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                } else {
                    getOldest(n);
                }
                break;
            }
            case 5:
                exitProgram();
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }while (choice != 5);
    return 0;
}

void showMenu(){
    std::cout << "\n--- City Driver Database Menu ---" << std::endl;
    std::cout << "1. Add New Driver Record" << std::endl;
    std::cout << "2. Remove/Migrate Driver" << std::endl;
    std::cout << "3. View N Most Recent Licenses" << std::endl;
    std::cout << "4. View N Oldest Licenses" << std::endl;
    std::cout << "5. Exit System" << std::endl;
    std::cout << "Selection: ";
}

void loadFromFile(const std::string &filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    int count = 0;
    while(std::getline(file, line) && count < 100){
        std::stringstream ss(line);
        std::string name, sDay, sMonth, sYear, lDay, lMonth, lYear, street, city, county, zip, type, medStr;
         std::getline(ss, name, ',');
        std::getline(ss, sDay, ','); std::getline(ss, sMonth, ','); std::getline(ss, sYear, ',');
        std::getline(ss, lDay, ','); std::getline(ss, lMonth, ','); std::getline(ss, lYear, ',');
        std::getline(ss, street, ','); std::getline(ss, city, ','); std::getline(ss, county, ','); std::getline(ss, zip, ',');
        std::getline(ss, type, ',');
        std::getline(ss, medStr, ',');  // medical condition as string

        int medInt = std::stoi(medStr);
        MedicalCondition med;
        switch(medInt){
            case 0: 
                med = FIT; 
                break;
            case 1: 
                med = VISION_IMPAIRED; 
                break;
            case 2: 
                med = UPPER_EXTREMITY; 
                break;
            case 3: 
                med = LOCOMOTOR; 
                break;
            default: 
                med = FIT;
                break;
        }

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
        
        activeDB.addDriver(d);
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
    std::cout << "Type (1. Student, 2. Government, 3. SelfEmployed, 4. BusinessOwner, 5. PrivateSector): ";
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