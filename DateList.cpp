#include "DateList.h"

//Constructor
DateList::DateList() : head(nullptr), tail(nullptr) {}

//Destructor
DateList::~DateList(){
    head = nullptr;
    tail = nullptr;
}

//Insertion
void DateList::insertSorted(DriverNode* node){
    if(!node){return;}

    //Case if empty list
    if(!head){
        head = tail = node;
        node->date_prev = nullptr;
        node->date_next = nullptr;
        return;
    }

    const Date& newDate = node->driver->getLicenseDate();

    //Case if new node is oldest
    if(newDate < head->driver->getLicenseDate()){
        node->date_next = head;
        node->date_prev = nullptr;
        head->date_prev = node;
        head = node;
        return;
    }

    //Case if new node is newest
    if(!(newDate < tail->driver->getLicenseDate())){
        node->date_next = head;
        node->date_prev = nullptr;
        tail->date_next = node;
        tail = node;
        return;
    }

    //Case if new node is in middle
    DriverNode* curr = head;
    while(curr && curr->driver->getLicenseDate() < newDate){
        curr = curr->date_next;
    }

    //Insert before curr
    node->date_next = curr;
    node->date_prev = curr->date_prev;
    if(curr->date_prev){curr->date_prev->date_next = node;}
    curr->date_prev = node;
}

//Removal
void DateList::remove(DriverNode* node){
    if(!node){return;}

    //Update neigbors pointers
    if(node->date_prev){node->date_prev->date_next = node->date_next;}
    else{head = node->date_next;}

    if(node->date_next){node->date_next->date_prev = node->date_prev;}
    else{tail = node->date_prev;}

    node->date_next = nullptr;
    node->date_prev = nullptr;
}

//Utility
bool DateList::isEmpty() const{return head == nullptr;}
DriverNode* DateList::getHead() const{return head;}
DriverNode* DateList::getTail() const{return tail;}