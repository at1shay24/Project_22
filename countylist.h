#ifndef COUNTY_LIST_H
#define COUNTY_LIST_H
#include <iostream>
#include <string>
#include "DriverNode.h"

class countylist {
private:
	DriverNode* head;
	DriverNode* tail;


public:
	countylist() : head(nullptr), tail(nullptr) {}
	void insertAtHead(DriverNode* county) {
		DriverNode* newNode = new DriverNode(county);
		if (head == NULL) {
			head = newNode;
		}
		else {
			newNode->county_next = head;
			head->county_prev = newNode;
			head = newNode;
		}
	}
	void insertAtTail(DriverNode* county) {
		DriverNode* newNode = new DriverNode(county);
		if (tail == NULL) {
			tail = newNode;
		}
		else {
			newNode->county_prev = tail;
			tail->county_next = newNode;
			tail = newNode;
		}
	}
	void insertAfter(DriverNode* county) {
		DriverNode* newnode = new DriverNode(county);
		newnode->county_next = county->county_next;
		county->county_next = newnode;

	}
	void remove(DriverNode* head, DriverNode* tail) {
		DriverNode* curr = head;
		while (curr->county_next->county_next != nullptr) {
			curr = curr->county_next;
		}
		DriverNode* tail = curr->county_next;
		curr->county_next = nullptr;
		delete tail;
	}

};
#endif