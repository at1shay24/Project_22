#ifndef DRIVER_DATABASE_H
#define DRIVER_DATABASE_H

#include "DriverNode.h"
#include "Vector.h"
#include <iostream>

class DriverDatabase {
private:
    DriverNode* head; 
    DriverNode* tail; 
    int totalDrivers;

public:
    DriverDatabase() : head(nullptr), tail(nullptr), totalDrivers(0) {}
    ~DriverDatabase() {
        DriverNode* curr = head;
        while (curr) {
            DriverNode* next = curr->date_next;
            delete curr->driver; 
            delete curr;         
            curr = next;
        }
    }
    void addDriver(Driver* newDriver) {
        DriverNode* newNode = new DriverNode(newDriver);
        
        if (!head) {
            head = tail = newNode;
        } 
        else if (newDriver->getLicenseDate() < head->driver->getLicenseDate()) {
            newNode->date_next = head;
            head->date_prev = newNode;
            head = newNode;
        } 
        else if (!(newDriver->getLicenseDate() < tail->driver->getLicenseDate())) {
            newNode->date_prev = tail;
            tail->date_next = newNode;
            tail = newNode;
        } 
        else {
            DriverNode* curr = head;
            while (curr && curr->driver->getLicenseDate() < newDriver->getLicenseDate()) {
                curr = curr->date_next;
            }
            newNode->date_next = curr;
            newNode->date_prev = curr->date_prev;
            curr->date_prev->date_next = newNode;
            curr->date_prev = newNode;
        }
        totalDrivers++;
    }
    void displayRecent(int n) {
        DriverNode* curr = tail;
        int count = 0;
        while (curr && count < n) {
            std::cout << curr->driver->getName() << " | License: " 
                      << curr->driver->getLicenseDate().toString() << std::endl;
            curr = curr->date_prev;
            count++;
        }
    }
    void displayOldest(int n) {
        DriverNode* curr = head;
        int count = 0;
        while (curr && count < n) {
            std::cout << curr->driver->getName() << " | License: " 
                      << curr->driver->getLicenseDate().toString() << std::endl;
            curr = curr->date_next;
            count++;
        }
    }
    int size() const { return totalDrivers; }
};
#endif