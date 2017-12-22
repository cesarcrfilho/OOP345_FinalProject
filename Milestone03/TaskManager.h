#ifndef TASKMANAGER_H__
#define TASKMANAGER_H__

// Manager Milestone - TaskManager Interface
// TaskManager.h
// Chris Szalwinski
// v1.0 - 14/11/2015
// v2.0 - 23/02/2016
#include <iostream>
#include <vector>

class Task;
class ItemManager;

class TaskManager : public std::vector<Task> {
public:
    void validate(std::ostream&);
    void validate(const ItemManager&, std::ostream&);
    void display(std::ostream&) const;
};

#endif //!TASKMANAGER_H__