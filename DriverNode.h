#ifndef DRIVER_NODE_H
#define DRIVER_NODE_H
#include "Driver.h"

struct DriverNode {
    Driver* driver;
    DriverNode* date_next;
    DriverNode* date_prev;
    DriverNode* county_next;
    DriverNode* county_prev;
    DriverNode(Driver* d) : driver(d), 
        date_next(nullptr), date_prev(nullptr), 
        county_next(nullptr), county_prev(nullptr) {}
};
#endif