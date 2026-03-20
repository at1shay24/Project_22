/*Author:       Murphy Jacob
 *Date:         03/17/26
 *Description:  
 *Instructor:   Bhaskar Trivedi*/
/*Author:       Atishay Jain
 *Date:         03/19/26
 *Description:  Main entry point for Driver Management System
 *Instructor:   Bhaskar Trivedi*/
 #include <iostream>
 #include <string>
 #include <sstream>
 #include <string>
 #include <fstream>
 #include "Date.h"
 #include "Address.h"
 #include "Vector.h"
#include "Ticket.h"
#include "DriverNode.h"
#include "Government.h"
#include "Student.h"
//#include "DriverDatabase.h".   not being used rn
 //TODO Include headers for Driver, DriverNode, DateList, CountyList, HashTable, DriverDatabase, etc.
 //TODO Declare global DriverDatabase object

 void loadFromFile(const std::string &filename);
 void showMenu();
 void addDriver();
 void removeDriver();
 void getMostRecent(int n);
 void getOldest(int n);
 void exitProgram();

int main(){
    std::cout << "-== Driver Database ==-" << std::endl;
    //TODO Create DriverDatabase and load data from file
    loadFromFile("drivers.dat");

    int choice = 0;
    do{
        showMenu();
       if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        switch(choice){
            case 1:
                addDriver();
                break;
            case 2:
                removeDriver();
                break;
            case 3:
                int n;
                std::cout << "Enter the number of most recent drivers to display: ";
                std::cin >> n;
                getMostRecent(n);
                break;
            case 4:
                std::cout << "Enter the number of oldest drivers to display: ";
                std::cin >> n;
                getOldest(n);
                break;
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
        //TODO: Parse the line and create driver objects and insert into DriverDatabase
        count++;
    }
    file.close();
    std::cout << "Loaded " << count << " drivers from file." << std::endl;
}

void addDriver(){
    std::cout << "--- Adding a New Driver ---" << std::endl;
    //TODO: Prompt for driver details and ask for an insertion point and refID if needed
    //Call DriverDatabase.addDriver(driver)
}

void removeDriver(){
    std::cout << "--- Removing a Driver ---" << std::endl;
    //Prompt for a license number and call DriverDatabase.removeDriver(driverID)
}

void getMostRecent(int n){
    std::cout << "Displaying the " << n << " most recent drivers:" << std::endl;
    //TODO Call DriverDatabase.getMostRecentLicenses(n) and display the results
}

void getOldest(int n){
    std::cout << "Displaying the " << n << " oldest drivers:" << std::endl;
    //TODO: Call DriverDatabase.getOldestLicenses(n) and display the results
}

void exitProgram(){
    std::cout << "Exiting the Database. Thank You and Goodbye!" << std::endl;
    //TODO: Any cleanup (Destructors should handle it)
}