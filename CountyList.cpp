#include "CountyList.h"

//Constructor
CountyList::CountyList() : head(nullptr), tail(nullptr){}

//Destructor
CountyList::~CountyList(){
    head = nullptr;
    tail = nullptr; 
}

//Insertion
void CountyList::insertAtHead(DriverNode* county){
    if(!county){return;}

    county->county_prev = nullptr;
    county->county_next = head;

    if(head){head->county_prev = county;}
    else{tail = county;}
    head = county;
}

void CountyList::insertAtTail(DriverNode* county){
    if(!county){return;}

    county->county_next = nullptr;
    county->county_prev = tail;

    if(tail){tail->county_next = county;}
    else{head = county;}
    tail = county;
}

void CountyList::insertAfter(DriverNode* refNode, DriverNode* newNode){
    if(!refNode || !newNode){return;}

    newNode->county_prev = refNode;
    newNode->county_next = refNode->county_next;

    if(refNode->county_next){refNode->county_next->county_prev = newNode;}
    else{tail = newNode;}
    refNode->county_next = newNode;
}

//Removal
void CountyList::remove(DriverNode* node){
    if(!node){return;}

    //Fix previous nodes next pointer
    if(node->county_prev){node->county_prev->county_next = node->county_next;}
    else{head = node->county_next;}

    //Fix next nodes previous pointer
    if(node->county_next){node->county_next->county_prev = node->county_prev;}
    else{tail = node->county_prev;}

    node->county_next = nullptr;
    node->county_prev = nullptr;
}

//Utility
bool CountyList::isEmpty() const{return head == nullptr;}
DriverNode* CountyList::getHead() const{return head;}
DriverNode* CountyList::getTail() const{return tail;}