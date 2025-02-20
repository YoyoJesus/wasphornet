//
//
// File:        logentry.cpp  
//       
// Version:     1.0
// Date:        3/13/24
// Author:      Austin Sternberg
//
// Description: Class implementation for a log entry.
//
//
 
#include "string.hpp"
#include "logentry.hpp"
#include <iostream>
#include <vector>

Date::Date(const String& dateStr) {
    // Assuming dateStr format: 18/Sep/2002
    //std::cout << "DEBUG PASS 1: " << dateStr << std::endl;
    day = dateStr.substr(0, 1);
    month = dateStr.substr(3, 5);
    year = dateStr.substr(7, 10);
}

Time::Time(const String& timeStr) {
    // Assuming timeStr format: :12:05:25
    //std::cout << "DEBUG PASS 2: " << timeStr << std::endl;
    hour = timeStr.substr(1, 2); // Start at index 11 for hour
    minute = timeStr.substr(4, 5); // Start at index 14 for minute
    second = timeStr.substr(7, 8); // Start at index 17 for second
}


LogEntry::LogEntry(const String& line) {
    std::vector<String> logEntryParts = line.split(' ');
    //std::cout << line << std::endl;
    if (logEntryParts.size() != 10)
        return;

    /*
    //Debug for loop
    for (int i = 0; i < int(logEntryParts.size()); ++i) {
        std::cout << "Part " << i << " " << logEntryParts[i] << " " << std::endl;
    }
    */

    host = logEntryParts[0];
    //std::cout << "Debug host " << host << std::endl;

    // Extracting date and time
    String dateTime = logEntryParts[3] + " " + logEntryParts[4];
    //std::cout << "Debug TIMEDATE " << dateTime << std::endl;

    date = Date(dateTime.substr(1, 11)); // Extract date from "[18/Sep/2002"
    //std::cout << "Debug Date " << date << std::endl;

    time = Time(dateTime.substr(12, 20)); // Extract time from ":12:05:25"
    //std::cout << "Debug Time " << time << std::endl;

    // Combining request parts
    request = logEntryParts[5] + " " + logEntryParts[6] + " " + logEntryParts[7];
    //std::cout << "Debug request " << request << std::endl;

    status = logEntryParts[8];
    //std::cout << "Debug Status " << status << std::endl;

    String temp = logEntryParts[9];
    //std::cout << "Debug SIZE " << temp << std::endl;
    if (temp != "-")
        number_of_bytes = temp.toInt();
    else
        number_of_bytes = 0;
}


std::vector<LogEntry> parse(std::istream& in) {
    std::vector<LogEntry> result;
    String line;
    char ch;

    // check for EOF
    while (!in.eof()) {
        in.get(ch);
        if (ch == '\n' && line !="") {  // End of a log entry
            //std::cout << result.size() << std::endl;
            result.push_back(line);
            line = "";
        } else {
            line += ch;
        }
        //std::cout << line << std::endl;
    }

    return result;
}

void output_all(std::ostream& out, const std::vector<LogEntry>& rhs) {
    std::cout << "Output all called " << std::endl;
    for (int i = 0; i < int(rhs.size()); ++i) {
        out << rhs[i] << '\n';
    }
}

void by_host(std::ostream& out, const std::vector<LogEntry>& rhs) {
    std::cout << "By Host" << std::endl;
    for (int i = 0; i < int(rhs.size()); ++i) {
        out << "Host: " << rhs[i].get_host() << std::endl;
    }
}

int byte_count(const std::vector<LogEntry>& rhs) {
    int result = 0;

    for (int i = 0; i < int(rhs.size()); ++i) {
        result += rhs[i].get_num_of_bytes();
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const Date& rhs) {
    out << rhs.month << " " << rhs.day << " " << rhs.year;
    return out;
}

std::ostream& operator<<(std::ostream& out, const LogEntry& rhs) {
    out << "Host: " << rhs.host << std::endl;
    out << "Date: " << rhs.date << std::endl;
    out << "Time: " << rhs.time << std::endl;
    out << "Request " << rhs.request << std::endl;
    out << "Status " << rhs.status <<std::endl;
    out << "Data Transmitted: " << rhs.get_num_of_bytes() << std::endl;

    return out;
}

std::ostream& operator<<(std::ostream& out, const Time& rhs) {
    out << rhs.hour << ":" << rhs.minute<< ":" << rhs.second;
    return out;
}


//IP function:
void print_unique_ips(const std::vector<LogEntry>& logEntries) {
    std::map<String, int> uniqueIPs;

    for (size_t i = 0; i < logEntries.size(); ++i) {
        const LogEntry& entry = logEntries[i];
        uniqueIPs[entry.get_host()]++;
    }

    std::cout << "Unique IP Addresses:" << std::endl;
    for (std::map<String, int>::const_iterator it = uniqueIPs.begin(); it != uniqueIPs.end(); ++it) {
        std::cout << it->first << std::endl;
    }
    std::cout << "Total unique IP Addresses: " << (uniqueIPs.size()) << std::endl;
}

/*Explanation of my challenge function:

This function uses the std::map library to create a string that stores address.
The map library ensure that anything added to the string will be unique, so we 
can avoid duplicate IP address.

From there, the function iterates through every possible log request in the log
file, storing just the unique host IPs.The map is also used as a count of these
IP addresses.

The second loop prints out the unique IP addresses, one per line until we run
out of entries. From there the last line prints out the count of these IPs using
the size of the map string minus 1 to account for the terminating character.

*/