#ifndef DATE_LIST_H
#define DATE_LIST_H
#include <iostream>
#include <string>
#include "DriverNode.h"

class datelist {
private:
	DriverNode* head;
	DriverNode* tail;
	

public:
	datelist() : head(nullptr), tail(nullptr) {}
	DriverNode* insertSorted(DriverNode* head) {
	
		DriverNode* sorted = nullptr;
		DriverNode* curr = head;
		while (curr != nullptr) {
			DriverNode* county_unsorted = curr->county_next;
			if (sorted == nullptr || curr->county_next < sorted->county_next) {
				curr->county_next = sorted;
				sorted = curr;
			}
			else {
				DriverNode* temp = sorted;
				while (temp->county_next != nullptr && temp->county_next < curr->county_next) {
					temp = temp->county_next;
				}
				curr->county_next = temp->county_next;
				temp->county_next = curr;
			}
			curr = county_unsorted;
		}
		return sorted;
	}
	void remove(DriverNode* head, DriverNode* tail) {
		DriverNode* curr = head;
		while (curr->date_next->date_next != nullptr) {
			curr = curr->date_next;
		}
		DriverNode* tail = curr->date_next;
		curr->date_next = nullptr;
		delete tail;

	}


};
#endif