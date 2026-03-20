#ifndef TICKET_H
#define TICKET_H

#include "Date.h"
#include "Address.h"

class Ticket {
private:
    Date issueDate; 
    Address location; 

public:
    Ticket() : issueDate(Date()), location(Address()) {}
    Ticket(Date d, Address a) : issueDate(d), location(a) {}

    std::string toString() const {
        return "Date: " + issueDate.toString() + " | City: " + location.getCity();
    }
};

#endif