#ifndef DATE_LIST_H
#define DATE_LIST_H
#include "DriverNode.h"

class DateList {
private:
	DriverNode* head;
	DriverNode* tail;
	
public:
	//Constructor
	DateList();

	//Destructor
	~DateList();

	//Insertion
	void insertSorted(DriverNode* node);

	//Removal
	void remove(DriverNode* node);

	//Utility
	bool isEmpty() const;
	DriverNode* getHead() const;
	DriverNode* getTail() const;
};
#endif