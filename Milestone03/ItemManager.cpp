/*--------------------SENECA COLLEGE-----------------------------
Student     : Cesar Rodrigues
Student ID  : 127381168
Email       : cda-conceicao-rodrig@myseneca.ca
Date        : Dec 22 2017
Class       : OOP345 - Object Oriented Software Development Using C++
Description : Milestone 03 - ItemManager.cpp
---------------------------------------------------------------*/

#include "ItemManager.h"

// display
// inserts into os descriptions of each item stored in the base class container.
// The bool parameter specifies whether a full description of the item should be inserted.
void ItemManager::display(std::ostream& os, bool fullDesc) const {
    // for range based loop
    for (auto& item : *this)
        item.display(os, fullDesc);
}