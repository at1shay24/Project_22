#ifndef INACTIVE_DATABASE_H
#define INACTIVE_DATABASE_H

#include "Driver.h"
#include "Vector.h"
#include <iostream>

class InactiveDatabase {
private:
    Vector<Driver*> storage;

public:
    void addInactive(Driver* d) {
        storage.push_back(d);
    }

    void showHistory() const {
        std::cout << "--- Inactive Driver Records ---" << std::endl;
        for (size_t i = 0; i < storage.size(); i++) {
            std::cout << storage[i]->getName() << " (Archived)" << std::endl;
        }
    }
};

#endif