/*--------------------SENECA COLLEGE-----------------------------
Student     : Cesar Rodrigues
Student ID  : 127381168
Email       : cda-conceicao-rodrig@myseneca.ca
Date        : Dec 17 2017
Class       : OOP345 - Object Oriented Software Development Using C++
Description : Milestone 02 - CustomerItem.cpp
---------------------------------------------------------------*/

#include <iomanip> // to manipulate ostream
#include "CustomerItem.h"
#include "Item.h"

// One parameter constructor
CustomerItem::CustomerItem(const std::string& customerItem)
    : name(customerItem), filled(false), code(0) { }

// asksFor
// returns true if the current object asks for item; false otherwise
bool CustomerItem::asksFor(const Item& item) const { return name == item.getName(); }

// isFilled
// returns true if the current object's request has been filled
bool CustomerItem::isFilled() const { return filled; }

// fill
// sets the item code for the current object to the value received
// and switches the status of the current object to filled
void CustomerItem::fill(const unsigned int c) {
    code = c;
    filled = true;
}

// clear
// resets the item code for the current object to 0
// and resets the status of the current object to not filled
void CustomerItem::clear() {
    code = 0;
    filled = false;
}

// getName
// returns the name of the requested component
const std::string& CustomerItem::getName() const { return name; }

// display
void CustomerItem::display(std::ostream& os) const {
    // set the prefix based on the filled value
    const std::string prefix = filled ? " + [" : " - [";

    os << prefix
       << std::setw(CODE_WIDTH) << std::setfill('0')
       << code << "] "
       << std::setfill(' ')
       << name << std::endl;
}