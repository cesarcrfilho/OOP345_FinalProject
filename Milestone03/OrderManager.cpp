/*--------------------SENECA COLLEGE-----------------------------
Student     : Cesar Rodrigues
Student ID  : 127381168
Email       : cda-conceicao-rodrig@myseneca.ca
Date        : Dec 22 2017
Class       : OOP345 - Object Oriented Software Development Using C++
Description : Milestone 03 - OrderManager.cpp
---------------------------------------------------------------*/

#include <algorithm> // find_if
#include "OrderManager.h"
#include "CustomerOrder.h"
#include "ItemManager.h"
#include "Item.h"

// extract
// moves a customerOrder from the back of the base class container
CustomerOrder&& OrderManager::extract() {
    return std::move(back());
}

// validate
// checks that the items requested in the customer orders are available,
// inserting a message into os for any item that is not available
void OrderManager::validate(const ItemManager& itemManager, std::ostream& os) {

    for (auto& order : *this) {
        for (size_t i = 0; i < order.noOrders(); i++) {
            auto it = std::find_if(itemManager.begin(), itemManager.end(), [&](const Item& item) { return order[i] == item.getName(); });
            if (it == itemManager.end()) {
                os << order[i] << " is unavailable\n";
            }
        }
    }
}

// display
// inserts into os descriptions of each customer order in the base class container
void OrderManager::display(std::ostream& os) const {
    for (auto& order : *this) {
        order.CustomerOrder::display(os);
    }
}