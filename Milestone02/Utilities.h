#ifndef UTILITIES_H__
#define UTILITIES_H__

// Milestone 1 - Utilities Interface
// Utilities.h
// Chris Szalwinski
// v1.0 - 24/10/2015
// v2.0 - 23/02/2016
#include <string>
#include <fstream>

class Utilities {
    size_t field_width;           // maximum field width needed 
    static char delimiter;        // field delimiter character
    static std::ofstream logFile; // log file
public:
    Utilities();
    size_t getFieldWidth() const;
    const std::string nextToken(const std::string&, size_t&, bool&);
    static void setDelimiter(const char);
    static void setLogFile(const char*);
    void setFieldWidth(size_t fw);
    static std::ofstream& getLogFile();
};

#endif //!UTILITIES_H__
