/*--------------------SENECA COLLEGE-----------------------------
Student     : Cesar Rodrigues
Student ID  : 127381168
Email       : cda-conceicao-rodrig@myseneca.ca
Date        : Dec 22 2017
Class       : OOP345 - Object Oriented Software Development Using C++
Description : Milestone 03 - TaskManager.cpp
---------------------------------------------------------------*/

#include <algorithm> // find_if
#include <string>
#include "TaskManager.h"
#include "Task.h"
#include "ItemManager.h"
#include "Item.h"

// validate - one parameter
// validates each task against all of the other tasks in the base class container
void TaskManager::validate(std::ostream& os) {
    bool valid = true;

    // validates each task against all others
    for (auto& i : *this) {
        for (auto& j : *this) {
            if (&i != &j) {
                i.validate(j);
            }
        }
    }

    // checks if the task is valid
    for (auto& i : *this) {
        for (auto& j : *this) {
            if (&i != &j && !i.validate(j)) {
                valid = false;
            }
        }
    }

    // checks if all tasks were validated and displays message
    if (valid == false)
        os << "*** Not all tasks have been validated ***" << std::endl;
}

// validate - two parameter
// checks that the tasks assigned to handle each item managed by
// itemManager are tasks in the base class container
void TaskManager::validate(const ItemManager& itemManager, std::ostream& os) {

    // lambda expression
    auto compare = [&](const std::string taskName) {
        auto it = std::find_if(begin(), end(), [&](const Task& task) { return taskName == task.getName(); });
        if (it == end()) {
            os << taskName << " is unavailable" << std::endl;
        }
    };

    for (auto& item : itemManager) {
        compare(item.getFiller());
        compare(item.getRemover());
    }
}

// display
// inserts into the referenced ostream object descriptions of the tasks stored in tasks
void TaskManager::display(std::ostream& os) const {
    for (auto& tasks : *this)
        tasks.Task::display(os);
}