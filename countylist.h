#ifndef COUNTY_LIST_H
#define COUNTY_LIST_H
#include "DriverNode.h"

class CountyList {
private:
	DriverNode* head;
	DriverNode* tail;

public:
	//Constructor
	CountyList() : head(nullptr), tail(nullptr) {}
	
	//Destructor
	~CountyList(){}
	
	//Insertion
	void insertAtHead(DriverNode* county);
void insertAtTail(DriverNode* county);
void insertAfter(DriverNode* refNode, DriverNode* newNode);
	//Removal
void remove(DriverNode* node);

	//Utility
	bool isEmpty() const;
	DriverNode* getHead() const;
	DriverNode* getTail() const;
};
#endif