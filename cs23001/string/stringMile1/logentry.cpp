//
//
// File:        logentry.cpp  
//       
// Version:     1.0
// Date:        
// Author:      
//
// Description: Class implementation for a log entry.
//
//
 
#include "string.hpp"
#include "logentry.hpp"
#include <iostream>
#include <vector>

// REQUIRES:
// ENSURES:
LogEntry::LogEntry(const String& line) {
    //Use split to create LogEntry
    //std::vector<String> logEntryParts = line.split(' ');

}

// REQUIRES:
// ENSURES:
std::vector<LogEntry> parse(std::istream& in) {
    std::vector<LogEntry> result;

    return result;
}

// REQUIRES:
// ENSURES:
void output_all(std::ostream& out, const std::vector<LogEntry>&) {
    
}

// REQUIRES:
// ENSURES:
void by_host(std::ostream& out, const std::vector<LogEntry>&) {

}

// REQUIRES:
// ENSURES:
int byte_count(const std::vector<LogEntry>&) {
    
    return 0;
}

