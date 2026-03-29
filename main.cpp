/*Author:       Murphy Jacob, Atishay Jain
 *Date:         03/17/26
 *Description:  Driver Database Management System for City Transportation Department
 *Instructor:   Bhaskar Trivedi
 *Date:         03/19/26
 *Description:  Main entry point for Driver Management System
 *Instructor:   Bhaskar Trivedi*/

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
#include <ctime>
#include <iomanip>
using namespace std;

DriverDatabase activeDB;

//Declarations
void loadFromFile(const string& filename);
void showMenu();
void addDriver();
void removeDriver();
void getMostRecent(int n);
void getOldest(int n);
void displayByCategory();
void exitProgram();

// Classification helpers
int computeAge(const Date& dob);
string getAgeCategory(Driver* d);
string getExperienceCategory(Driver* d);
string getMedicalLabel(Driver* d);
string getWorkType(Driver* d);
void printDriverRow(Driver* d);

int main(){
    cout << "-== Driver Database ==-" << endl;
    loadFromFile("drivers.dat");

    int choice = 0;
    do{
        showMenu();
        if(!(cin >> choice)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
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
                if(!(cin >> n)){
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
                if(!(cin >> n)){
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else {
                    getOldest(n);
                }
                break;
            }
            case 5:
                displayByCategory();
                break;
            case 6:
                exitProgram();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while(choice != 6);
    return 0;
}

void showMenu(){
    cout << "\n--- City Driver Database Menu ---" << endl;
    cout << "1. Add New Driver Record"            << endl;
    cout << "2. Remove/Migrate Driver"            << endl;
    cout << "3. View N Most Recent Licenses"      << endl;
    cout << "4. View N Oldest Licenses"           << endl;
    cout << "5. Browse by Category"               << endl;
    cout << "6. Exit System"                      << endl;
    cout << "Selection: ";
}

void loadFromFile(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    int count = 0;
    while(getline(file, line) && count < 100){
        if(line.empty()) continue;

        stringstream ss(line);

        //Name
        string name;
        getline(ss, name, ',');

        //Date of Birth (d,m,yyyy)
        string sDay, sMonth, sYear;
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
        getline(ss, medStr, ',');

        //Skip malformed lines
        if(name.empty() || type.empty() || medStr.empty()) continue;

        int medInt = stoi(medStr);
        MedicalCondition med;
        switch(medInt){
            case 0:  med = FIT;             break;
            case 1:  med = VISION_IMPAIRED; break;
            case 2:  med = UPPER_EXTREMITY; break;
            case 3:  med = LOCOMOTOR;       break;
            default: med = FIT;             break;
        }

        Date    dob(stoi(sDay),  stoi(sMonth),  stoi(sYear));
        Date    lic(stoi(lDay),  stoi(lMonth),  stoi(lYear));
        Address homeAddr(hStreet, hCity, hCounty, hZip);
        Address workAddr(wStreet, wCity, wCounty, wZip);

        Driver* d = nullptr;
        if     (type == "Student")       d = new Student      (name, dob, lic, homeAddr, workAddr, med);
        else if(type == "Government")    d = new Government   (name, dob, lic, homeAddr, workAddr, med);
        else if(type == "SelfEmployed")  d = new SelfEmployed (name, dob, lic, homeAddr, workAddr, med);
        else if(type == "BusinessOwner") d = new BusinessOwner(name, dob, lic, homeAddr, workAddr, med);
        else if(type == "PrivateSector") d = new PrivateSector(name, dob, lic, homeAddr, workAddr, med);
        else{
            cerr << "Unknown type \"" << type << "\" on line " << (count + 1) << " — skipping." << endl;
            continue;
        }

        activeDB.addDriver(d);
        count++;
    }
    file.close();
    cout << "Loaded " << count << " drivers from file." << endl;
}

//Insertion
void addDriver(){
    string name;
    int d, m, y, ld, lm, ly, typeChoice;

    cout << "\n--- Adding a New Driver ---" << endl;
    cin.ignore();

    //Name
    cout << "Name: ";
    getline(cin, name);

    //Dates
    cout << "Date of Birth  (D M YYYY): "; cin >> d >> m >> y;
    cout << "License Date   (D M YYYY): "; cin >> ld >> lm >> ly;
    cin.ignore();

    //Home Address
    string hStreet, hCity, hCounty, hZip;
    cout << "\n-- Home Address --" << endl;
    cout << "Street: "; getline(cin, hStreet);
    cout << "City:   "; getline(cin, hCity);
    cout << "County: "; getline(cin, hCounty);
    cout << "Zip:    "; getline(cin, hZip);

    //Work Address
    string wStreet, wCity, wCounty, wZip;
    cout << "\n-- Work Address --" << endl;
    cout << "Street: "; getline(cin, wStreet);
    cout << "City:   "; getline(cin, wCity);
    cout << "County: "; getline(cin, wCounty);
    cout << "Zip:    "; getline(cin, wZip);

    //Driver type
    cout << "\nType:" << endl;
    cout << "  1. Student"        << endl;
    cout << "  2. Government"     << endl;
    cout << "  3. Self-Employed"  << endl;
    cout << "  4. Business Owner" << endl;
    cout << "  5. Private Sector" << endl;
    cout << "Selection: ";
    cin >> typeChoice;

    Date    dob(d, m, y);
    Date    lic(ld, lm, ly);
    Address homeAddr(hStreet, hCity, hCounty, hZip);
    Address workAddr(wStreet, wCity, wCounty, wZip);

    Driver* newDriver = nullptr;
    switch(typeChoice){
        case 1:  newDriver = new Student      (name, dob, lic, homeAddr, workAddr, FIT); break;
        case 2:  newDriver = new Government   (name, dob, lic, homeAddr, workAddr, FIT); break;
        case 3:  newDriver = new SelfEmployed (name, dob, lic, homeAddr, workAddr, FIT); break;
        case 4:  newDriver = new BusinessOwner(name, dob, lic, homeAddr, workAddr, FIT); break;
        default: newDriver = new PrivateSector(name, dob, lic, homeAddr, workAddr, FIT); break;
    }

    //Insertion
    cout << "\nInsert position within county list:" << endl;
    cout << "  1. Beginning"                        << endl;
    cout << "  2. End"                              << endl;
    cout << "  3. After a specific driver"          << endl;
    cout << "Selection: ";
    int posChoice;
    cin >> posChoice;

    string position = "end";
    string refName  = "";

    if(posChoice == 1){
        position = "beginning";
    } else if(posChoice == 3){
        position = "after";
        cin.ignore();
        cout << "Enter the exact name of the reference driver: ";
        getline(cin, refName);
    }

    activeDB.addDriver(newDriver, position, refName);
    cout << "Driver \"" << name << "\" added successfully." << endl;
}

//Removal and migration
void removeDriver(){
    cout << "\n--- Removing a Driver ---" << endl;
    cout << "Enter name: ";
    cin.ignore();
    string name;
    getline(cin, name);

    bool removed = activeDB.removeByName(name);
    if(removed){
        cout << "Driver moved to inactive database." << endl;
        cout << "Inactive drivers:" << endl;
        activeDB.showInactive();
    }
    else{cout << "Driver not found." << endl;}
}

//Display most recent and oldest
void getMostRecent(int n){
    cout << "\nDisplaying " << n << " most recently licensed driver(s):" << endl;
    activeDB.displayRecent(n);
}

void getOldest(int n){
    cout << "\nDisplaying " << n << " oldest licensed driver(s):" << endl;
    activeDB.displayOldest(n);
}

void exitProgram(){
    cout << "Exiting the Database. Thank You and Goodbye!" << endl;
}

//CLASSIFICATION HELPERS

//Age-based category
string getAgeCategory(Driver* d){
    int age = d->getAge();
    if(age <= 28) return "Youth (16-28)";
    if(age <= 50) return "Middle-Aged (29-50)";
    return "Senior (51+)";
}

//Experience-based category
string getExperienceCategory(Driver* d){
    int yrs = d->getLicenseDate().getCurrentYear() - d->getLicenseDate().getYear();
    if(yrs <= 5)  return "New Driver (0-5 years)";
    if(yrs <= 15) return "Moderately Experienced (6-15 years)";
    return "Highly Experienced (15+ years)";
}

string getMedicalLabel(Driver* d){
    switch(d->getMedical()){
        case FIT:             return "Fit";
        case VISION_IMPAIRED: return "Vision Impaired";
        case UPPER_EXTREMITY: return "Upper Extremity Impairment";
        case LOCOMOTOR:       return "Locomotor Disability";
        default:              return "Unknown";
    }
}

string getWorkType(Driver* d){
    if(dynamic_cast<Student*>     (d)) return "Student";
    if(dynamic_cast<Government*>  (d)) return "Government";
    if(dynamic_cast<SelfEmployed*>(d)) return "Self-Employed";
    if(dynamic_cast<BusinessOwner*>(d))return "Business Owner";
    if(dynamic_cast<PrivateSector*>(d))return "Private Sector";
    return "Unknown";
}

void printDriverRow(Driver* d){
    int age = d->getAge();
    int exp = d->getLicenseDate().getCurrentYear() - d->getLicenseDate().getYear();

    cout << left
         << setw(22) << d->getName()
         << " | Age: "     << setw(3)  << age
         << " | Exp: "     << setw(3)  << exp << " yr"
         << " | Work: "    << setw(16) << getWorkType(d)
         << " | Medical: " << setw(28) << getMedicalLabel(d)
         << " | License: " << d->getLicenseDate()
         << endl;
}

//Browse by Category
void displayByCategory(){
    int catChoice = 0;
    do{
        cout << "\n--- Browse by Category ---"  << endl;
        cout << "1. Age Group"                  << endl;
        cout << "2. Work Type"                  << endl;
        cout << "3. Experience Level"           << endl;
        cout << "4. Medical Condition"          << endl;
        cout << "5. Back to Main Menu"          << endl;
        cout << "Selection: ";

        if(!(cin >> catChoice)){
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        if(catChoice == 5) break;

        // Build the filter label from the appropriate sub-menu
        string filterLabel = "";

        if(catChoice == 1){
            //Age Group
            int sub;
            cout << "\n  Age Group:"                        << endl;
            cout << "  1. Youth        (16-28 years)"      << endl;
            cout << "  2. Middle-Aged  (29-50 years)"      << endl;
            cout << "  3. Senior       (51+  years)"       << endl;
            cout << "  Selection: ";
            cin >> sub;
            switch(sub){
                case 1:  filterLabel = "Youth (16-28)";       break;
                case 2:  filterLabel = "Middle-Aged (29-50)"; break;
                case 3:  filterLabel = "Senior (51+)";        break;
                default: cout << "Invalid selection." << endl; continue;
            }

        } else if(catChoice == 2){
            //Work Type
            int sub;
            cout << "\n  Work Type:"            << endl;
            cout << "  1. Student"              << endl;
            cout << "  2. Government"           << endl;
            cout << "  3. Self-Employed"        << endl;
            cout << "  4. Business Owner"       << endl;
            cout << "  5. Private Sector"       << endl;
            cout << "  Selection: ";
            cin >> sub;
            switch(sub){
                case 1:  filterLabel = "Student";        break;
                case 2:  filterLabel = "Government";     break;
                case 3:  filterLabel = "Self-Employed";  break;
                case 4:  filterLabel = "Business Owner"; break;
                case 5:  filterLabel = "Private Sector"; break;
                default: cout << "Invalid selection." << endl; continue;
            }

        } else if(catChoice == 3){
            //Experience Level
            int sub;
            cout << "\n  Experience Level:"                            << endl;
            cout << "  1. New Driver              (0-5  years)"       << endl;
            cout << "  2. Moderately Experienced  (6-15 years)"       << endl;
            cout << "  3. Highly Experienced      (15+  years)"       << endl;
            cout << "  Selection: ";
            cin >> sub;
            switch(sub){
                case 1:  filterLabel = "New Driver (0-5 years)";               break;
                case 2:  filterLabel = "Moderately Experienced (6-15 years)";  break;
                case 3:  filterLabel = "Highly Experienced (15+ years)";       break;
                default: cout << "Invalid selection." << endl; continue;
            }

        } else if(catChoice == 4){
            //Medical Condition
            int sub;
            cout << "\n  Medical Condition:"                    << endl;
            cout << "  1. Fit"                                  << endl;
            cout << "  2. Vision Impaired"                      << endl;
            cout << "  3. Upper Extremity Impairment"           << endl;
            cout << "  4. Locomotor Disability"                 << endl;
            cout << "  Selection: ";
            cin >> sub;
            switch(sub){
                case 1:  filterLabel = "Fit";                        break;
                case 2:  filterLabel = "Vision Impaired";            break;
                case 3:  filterLabel = "Upper Extremity Impairment"; break;
                case 4:  filterLabel = "Locomotor Disability";       break;
                default: cout << "Invalid selection." << endl; continue;
            }

        } else {
            cout << "Invalid category." << endl;
            continue;
        }

        //Traverse and print matching drivers
        cout << "\n--- Drivers: " << filterLabel << " ---" << endl;

        int found = 0;
        DriverNode* curr = activeDB.getHead();

        while(curr){
            Driver* d = curr->driver;
            bool match = false;

            switch(catChoice){
                case 1: match = (getAgeCategory(d)       == filterLabel); break;
                case 2: match = (getWorkType(d)           == filterLabel); break;
                case 3: match = (getExperienceCategory(d) == filterLabel); break;
                case 4: match = (getMedicalLabel(d)       == filterLabel); break;
            }

            if(match){
                printDriverRow(d);
                found++;
            }
            curr = curr->date_next;
        }

        if(found == 0)
            cout << "No drivers found in this category." << endl;
        else
            cout << "\nTotal: " << found << " driver(s) found." << endl;

    } while(catChoice != 5);
}
