/*--------------------SENECA COLLEGE-----------------------------
Student     : Cesar Rodrigues
Student ID  : 127381168
Email       : cda-conceicao-rodrig@myseneca.ca
Date        : Dec 10 2017
Class       : OOP345 - Object Oriented Software Development Using C++
Description : Milestone 01 - Task.cpp
---------------------------------------------------------------*/

#include <string>
#include "Task.h"
#include "Utilities.h"

// forward declaration
size_t Task::field_width = 0;

// default constructor
Task::Task(const std::string& record) {
    bool moreTokens = true;
    size_t next_pos = -1;
    size_t field = 1;
        
    slots = "1";
    pNextTask[0] = nullptr;
    pNextTask[1] = nullptr;

    Utilities util;
    auto save = [&](std::string token) -> void {
        switch (field) {
        case 1:
            name = token;
            break;
        case 2: 
            slots = token;
            break;
        case 3:
            nextTask[passed] = token;
            break;
        case 4: 
            nextTask[redirect] = token;
            break;
        }
    };

    // while more tokens are available for extraction
    while (moreTokens) {
        try {
            // reads the next token
            save(util.nextToken(record, next_pos, moreTokens));
            field++;
        }
        catch (const std::string& msg) {
            std::cout << msg << std::endl;
        }
    }

    // updates the field_width if needed
    if (field_width < util.getFieldWidth()) {
        field_width = util.getFieldWidth();
    }
}

// validate
bool Task::validate(const Task& task) {
    bool isValid = true;
    for (int i = 0; i < 2; i++) {
        if (!nextTask[i].empty() && nextTask[i] == task.getName())
            pNextTask[i] = &task;
        if (!nextTask[i].empty() && !pNextTask[i])
            isValid = false;
    }
    return isValid;
}

// getName
// returns the name of the task
const std::string& Task::getName() const { return name; }

// getSlots
// returns the number of product slots in the task (converted from a string to an unsigned integer
unsigned int Task::getSlots() const { return atoi(slots.c_str()); }

// getNextTask
// returns the address of the next task associated with the parameter received
const Task* Task::getNextTask(Quality quality) const {
    if (!nextTask[quality].empty() && !pNextTask[quality]) 
        // format *** Validate [...] @ [...] ***
        throw std::string("*** Validate [" + nextTask[quality] + "] @ [" + name + "] ***");
    return pNextTask[quality];
}

// display
void Task::display(std::ostream& os) const {
    std::string msgs[] = { " Continue to : ", " Redirect to : " };
    os.setf(std::ios::left);
    os << "Task Name    : ";
    os.width(field_width + 2);
    os << "[" + name + "]" << " [" + slots + "]" << std::endl;

    for (int i = 0; i < 2; i++) {
        if (!nextTask[i].empty()) {
            os << msgs[i];
            os.width(field_width + 2);
            os << "[" + nextTask[i] + "]";
            if (!pNextTask[i]) {
                os << " *** to be validated ***";
            }
            os << std::endl;
        }
    }

}

// getFieldWidth
// returns the field width currently stored for all objects in this class
size_t Task::getFieldWidth() { return field_width; }

// HELPER FUNCTIONS //

// operator==
// e.g. Task A == Task B
bool operator==(const Task& lhs, const Task& rhs) { return (lhs.getName() == rhs.getName()); }
