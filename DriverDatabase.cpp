#include "DriverDatabase.h"
#include <iostream>

//Constructor
DriverDatabase::DriverDatabase() : totalDrivers(0){}

//Destructor
DriverDatabase::~DriverDatabase(){
    DriverNode* curr = dateList.getHead();
    while(curr){
        DriverNode* next = curr->date_next;
        delete curr->driver;
        delete curr;
        curr = next;
    }
}

//Insertion
void DriverDatabase::addDriver(Driver* d, const string& position, const string& refID){
    if(!d){return;}

    //Create new node
    DriverNode* newNode = new DriverNode(d);

    //Insert into dateList
    dateList.insertSorted(newNode);

    //Get county
    string county = d->getAddress().getCounty();

    //Find or create a county list
    CountyList** clistPtr = countyMap.find(county);
    CountyList* clist = nullptr;
    if(clistPtr){clist = *clistPtr;}
    else{
        clist = new CountyList();
        countyMap.insert(county, clist);
    }

    //Insert into county list
    if(position == "beginning"){clist->insertAtHead(newNode);}
    else if(position == "end"){clist->insertAtTail(newNode);}
    else if(position == "after"){
        DriverNode** refNodePtr = idMap.find(refID);
        if(refNodePtr && *refNodePtr){clist->insertAfter(*refNodePtr, newNode);}
        else{
            std::cerr << "Reference driver not found. Inserting at tail." << std::endl;
            clist->insertAtTail(newNode);
        }
    }
    else{
        std::cerr << "Invalid position. Inserting at tail." << std::endl;
        clist->insertAtTail(newNode);
    }

    //Index by driver ID
    idMap.insert(d->getName(), newNode);
    totalDrivers++;
}

//Removal
bool DriverDatabase::removeByName(const string& driverID){
    //Find by ID
    DriverNode** nodePtr = idMap.find(driverID);
    if(!nodePtr || !*nodePtr){
        std::cerr << "Driver ID not found." << std::endl;
        return false;
    }
    DriverNode* node = *nodePtr;

    //Remove from dateList
    dateList.remove(node);
    string county = node->driver->getAddress().getCounty();
    CountyList** clistPtr = countyMap.find(county);
    if(clistPtr && *clistPtr){
        (*clistPtr)->remove(node);
        if((*clistPtr)->isEmpty()){
            delete *clistPtr;
            countyMap.remove(county);
        }
    }

    //Remove from ID map
    idMap.remove(driverID);

    //Move to inactive database
    inactiveDB.addInactive(node->driver);

    //Delete the node
    delete node;
    totalDrivers--;
    return true;
}

//Display
void DriverDatabase::displayRecent(int n) const{
    if(dateList.isEmpty()){
        std::cout << "No drivers in database." << std::endl;
        return;
    }

    DriverNode* curr = dateList.getTail();
    int count = 0;
    while(curr && count < n){
        std::cout << curr->driver->getName() << " | License: " << 
        curr->driver->getName() << std::endl;
        curr = curr->date_prev;
        count++;
    }
}

void DriverDatabase::displayOldest(int n) const{
    if(dateList.isEmpty()){
        std::cout << "No driver in database." << std::endl;
        return;
    }

    DriverNode* curr = dateList.getHead();
    int count = 0;
    while(curr && count < n){
        std::cout << curr->driver->getName() << " | License: " << 
        curr->driver->getName() << std::endl;
        curr = curr->date_next;
        count++;
    }
}

//Show inactive
void DriverDatabase::showInactive() const{inactiveDB.showHistory();}

int DriverDatabase::size() const{return totalDrivers;}
