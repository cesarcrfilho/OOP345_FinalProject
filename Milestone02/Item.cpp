/*--------------------SENECA COLLEGE-----------------------------
Student     : Cesar Rodrigues
Student ID  : 127381168
Email       : cda-conceicao-rodrig@myseneca.ca
Date        : Dec 17 2017
Class       : OOP345 - Object Oriented Software Development Using C++
Description : Milestone 02 - Item.cpp
---------------------------------------------------------------*/

#include <iomanip> // to manipulate ostream
#include "Item.h"
#include "Utilities.h" // to extract tokens

// forward declaration
size_t Item::field_width;

// One parameter constructor
Item::Item(const std::string& record) : description("no detailed description"), code(1) {
    bool more = true;
    size_t next_pos = -1;
    size_t field = 1;

    // extracts tokens from the string received using a Utilities object
    Utilities util;

    // lambda expression to check the token field (from 1 to 5)
    auto getTokenField = [&](std::string token) {

        switch (field) {
        // 1 is the name of the item
        case 1:
            name = token;
            break;
        // 2 is the name of the filler task
        case 2:
            filler = token;
            break;
        // 3 is the name of the remover task
        case 3:
            remover = token;
            break;
        // 4 is the integer holding the code to be printed on the item's first insertion into a product
        case 4:
            // declare a size placeholder
            std::string::size_type size;
            // convert it to integer
            code = std::stoi(token, &size);
            break;
        // 5 is a detailed description of the item
        case 5:
            description = token;
            break;
        }
    };

    // checks for fields in the item and save them using the Utilities object
    while (more) {
        try {
            getTokenField(util.nextToken(record, next_pos, more));
            field++;
        }
        catch (const std::string& err) {
            throw;
        }
    }

    // updates the width
    if (field_width < name.length()) {
        field_width = name.length();
    }
}

// empty
// returns true if the current object is in a safe empty state
bool Item::empty() const { return name.empty(); }

// operator++ overload
// increments the code to be printed on the next insertion and returns the value before incrementation
Item& Item::operator++(int) {
    code++;
    return *this;
}

// getName
// returns an unmodifiable reference to the string that contains the name of the item
const std::string& Item::getName() const { return name; }

// getFiller
// returns an unmodifiable reference to the string that contains the name of the task that inserts the item into a product
const std::string& Item::getFiller() const { return filler; }

// getRemover
// returns an unmodifiable reference to the string that contains the name of the task that extracts the item from a product
const std::string& Item::getRemover() const { return remover; }

// getCode
// returns a copy of the code to be printed on the next insertion into a product
size_t Item::getCode() const { return code; }

// display
void Item::display(std::ostream& os, bool full) const {
    os << std::left << std::setw(field_width) << std::setfill(' ')
       << name << " ["
       << std::right << std::setw(CODE_WIDTH) << std::setfill('0')
       << code
       << std::setfill(' ') << "] ";

    // if the full flag is true, this function includes a complete description of the item
    if (full) {
        os << "From "
           << std::left << std::setw(field_width)
           << name << " To " << remover << std::endl
           << std::left << std::setw(field_width + CODE_WIDTH + 1)
           << "  : " << description;
    }
    os << std::endl;
}