/*--------------------SENECA COLLEGE-----------------------------
Student     : Cesar Rodrigues
Student ID  : 127381168
Email       : cda-conceicao-rodrig@myseneca.ca
Date        : Dec 17 2017
Class       : OOP345 - Object Oriented Software Development Using C++
Description : Milestone 02 - CustomerOrder.cpp
---------------------------------------------------------------*/

#include <iomanip> // to manipulate ostream
#include <vector> // to hold the items for the dynamic array
#include "CustomerOrder.h"
#include "CustomerItem.h"
#include "Item.h"
#include "Utilities.h"

// forward declaration
size_t CustomerOrder::field_width;

// One parameter constructor - string ref
CustomerOrder::CustomerOrder(const std::string& record)
    : order(nullptr), nOrders(0) {

    bool more = true;
    size_t next_pos = -1;
    size_t field = 1;

    // extracts tokens from the string received using a Utilities object
    Utilities util;
    // vector to hold the items
    std::vector<std::string> items;

    // lambda expression to check the token field
    auto getTokenField = [&](std::string token) {

        switch (field) {
        // 1 is the customer name field
        case 1:
            name = token;
            break;
        // 2 is the product name field
        case 2:
            product = token;
            break;
        default:
            items.push_back(token);
            nOrders++;
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

    // allocate memory for the CustomerItems object
    order = new CustomerItem[nOrders];

    // loop through the vector and transfer the items
    for (size_t i = 0; i < items.size(); i++) {
        order[i] = CustomerItem(items[i]);
    }

    // updates the width
    if (field_width < util.getFieldWidth()) {
        field_width = util.getFieldWidth();
    }
}

// Copy constructor - throw exception
CustomerOrder::CustomerOrder(const CustomerOrder& src) { throw std::string("*** Error: copy constructor not available ***"); }

// Move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& src) NOEXCEPT {
    order = nullptr;
    *this = std::move(src);
}

// Move assignment operator
CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& rhs) NOEXCEPT {
    if (this != &rhs) {
        // deallocate memory
        delete[] order;

        // assign the values
        name = rhs.name;
        product = rhs.product;
        order = rhs.order;
        nOrders = rhs.nOrders;

        // reset the values
        rhs.name = "";
        rhs.product = "";
        rhs.order = nullptr;
        rhs.nOrders = 0;
    }
    return std::move(*this);
}

// Destructor
CustomerOrder::~CustomerOrder() {
    delete[] order;
    order = nullptr;
}

// empty
// returns true if the current object is in a safe empty state
bool CustomerOrder::empty() const {
    return name.empty() && product.empty() && nOrders == 0;
}

// noOrders
// returns the number of customer items in the current object
size_t CustomerOrder::noOrders() const { return nOrders; }

// operator[] overload
// returns a reference to the name of customer item i; reports an exception if the index is out of bounds
const std::string& CustomerOrder::operator[](unsigned int i) const {
    if (i >= nOrders) throw "index out of bounds";

    return order[i].getName();
}

// fill
// searches through the customer items and fills those order for the
// customer items identified by item if any have not been filled
void CustomerOrder::fill(Item& item) {
    for (size_t i = 0; i < nOrders; i++) {
        if (order[i].asksFor(item) && order[i].isFilled() == false) {
            order[i].fill(item.getCode());
            item++;
        }
    }
}

// remove
// searches through the customer items and removes those items
// identified by the name of item if the corresponding part of the order has been filled
void CustomerOrder::remove(Item& item) {
    for (size_t i = 0; i < nOrders; i++) {
        if (order[i].asksFor(item) && order[i].isFilled()) {
            order[i].clear();
        }
    }
}

// display
void CustomerOrder::display(std::ostream& os) const {
    os << std::left << std::setw(field_width)
       << name
       << std::right << std::setw(0)
       << " : " << product << std::endl;

    // loop thourgh the CustomerItems object, fillind the ostream object
    for (size_t i = 0; i < nOrders; i++) {
        order[i].display(os);
    }
}
