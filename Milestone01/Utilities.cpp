/*--------------------SENECA COLLEGE-----------------------------
Student     : Cesar Rodrigues
Student ID  : 127381168
Email       : cda-conceicao-rodrig@myseneca.ca
Date        : Dec 10 2017
Class       : OOP345 - Object Oriented Software Development Using C++
Description : Milestone 01 - Utilities.cpp
---------------------------------------------------------------*/

#include "Utilities.h"

// forward declaration
char Utilities::delimiter = ' ';
std::ofstream Utilities::logFile;

// default constructor
Utilities::Utilities() : field_width(1) { }

// setFieldWidth
// resets the field width of the current object to fw
void  Utilities::setFieldWidth(size_t fw) { field_width = fw; }

// getFieldWidth
// returns the field width of the current object
size_t Utilities::getFieldWidth() const { return field_width; }

// nextToken
// returns the next token found and sets more to true if
// the record contains more tokens after the extracted token; false otherwise
const std::string Utilities::nextToken(const std::string& record, size_t& next_pos, bool& more) {
        
    size_t current_pos = next_pos + 1;

    next_pos = record.find_first_of(delimiter, current_pos);
    (next_pos == std::string::npos) ? more = false : more = true;

    std::string token = record.substr(current_pos, next_pos - current_pos);
    
    // trim the whitespaces
    if (token.length() > 1) {
        unsigned fPos = token.find_first_not_of(" \a\b\f\n\r\t\v");
        unsigned lPos = token.find_last_not_of(" \a\b\f\n\r\t\v");
        if (fPos != std::string::npos)
            token = std::string(token, fPos, lPos - fPos + 1);
    }

    if (token.empty()) {
        more = false;
        throw std::string(record + "<-- *** no token found before the delimiter ***");
    }

    // updates the field width
    if (field_width < token.length()) {
        field_width = token.length();
    }

    return token;
}

// setDelimiter
// resets the delimiter for this class to the character received
void  Utilities::setDelimiter(const char newDelimiter) { delimiter = newDelimiter; }

// setLogFile
// opens a log file for writing and truncation
void Utilities::setLogFile(const char* logfile) {
    logFile.open(logfile, std::ofstream::out | std::ofstream::trunc);
}

// getLogFile
// returns a modifiable reference to the log file
std::ofstream& Utilities::getLogFile() { return logFile; }