//
// File:        logentry.hpp
//
// Version:     1.0
// Date:        3/13/24
// Author:      Austin Sternberg
//
// Description: Class definition for a log entry.
//
//
//
 
#ifndef CS_LOGENTRY_H_
#define CS_LOGENTRY_H_

#include "string.hpp"
#include <iostream>
#include <vector>
#include <map>

class Date {
public:
    Date() {};
    Date(const String&);

    friend std::ostream& operator<<(std::ostream& out, const Date& rhs);
private:
    String day = "", month = "", year = "";
};

class Time {
public:
    Time() {};
    Time(const String&);

    friend std::ostream& operator<<(std::ostream& out, const Time& rhs);
private:
    String hour = "", minute = "", second = "";
};

class LogEntry {
public:
    LogEntry() {};
    LogEntry(const String&);

    String get_host() const { return host; };
    int get_num_of_bytes() const { return number_of_bytes; };

    friend std::ostream& operator<<(std::ostream&, const LogEntry&);

private:
    String host = "";
    Date date;
    Time time;
    String request = "";
    String status = "";
    int number_of_bytes = 0; // Initialize to 0
};

std::vector<LogEntry> parse(std::istream&);
void output_all(std::ostream&, const std::vector<LogEntry>&);
void by_host(std::ostream&, const std::vector<LogEntry>&);
int byte_count(const std::vector<LogEntry>&);
void print_unique_ips(const std::vector<LogEntry>&);

#endif