/**
   * Austin  Sternberg
   * string.cpp
   * cs23001
   */

//This program contains all of the method definitions for the string class - Project 2

#include "string.hpp"

// Default constructor: Initialize with empty string
String::String() {
    str[0] = 0;
}

// Constructor with char argument: Initialize with single char
String::String(char ch) : String() {
    str[0] = ch;
    str[1] = 0;
}

// Constructor with char array argument: Initialize with char array
String::String(const char char_array[]) {
    int loopv = 0;

    // Copy characters from char array to internal string until null character
    while (char_array[loopv] != 0){
        str[loopv] = char_array[loopv];
        ++loopv;

        // Check if loop reached max capacity
        if (loopv >= STRING_SIZE)
            break;
    }

    // Ensure null-termination
    str[loopv] = 0;
}

// Return the maximum capacity of the string
int String::capacity() const {
    return (STRING_SIZE - 1);
}

// Return the length of the string
int String::length() const {
    int result = 0;

    // Count characters until null character
    while (str[result] != '\0') {
        ++result;
    }

    return result;
}

// Access operator for modifying characters
char& String::operator[](int x) {
    return str[x];
}

// Access operator for reading characters
char String::operator[](int x) const {
    return str[x];
}

String& String::operator+=(const String& rhs) {
    int char_offset = length();
    int index = 0;

    // Check if the strings are the same, then concatenate with itself
    if (*this == rhs) {
        // Double the length by copying the current string
        while (index < char_offset) {
            str[char_offset + index] = str[index];
            ++index;
        }
        // Update the length
        char_offset *= 2;
    } else {
        // Append characters from rhs until end, capacity reached, or null character
        while (rhs.str[index] != 0 && char_offset + index < STRING_SIZE - 1) {
            str[char_offset + index] = rhs.str[index];
            ++index;
        }
        // Null-terminate the result
        str[char_offset + index] = 0;
    }

    return *this;
}

// Addition operator for concatenating strings
String operator+(String lhs, const String& rhs) {
    String result;

    int lhs_length = lhs.length();
    int rhs_length = rhs.length();
    int result_length = lhs_length + rhs_length;

    // Ensure result does not exceed capacity
    if (result_length >= STRING_SIZE)
        result_length = STRING_SIZE - 1;
    
    // Copy characters from lhs to result
    for (int i = 0; i < lhs_length && i < result_length; ++i) {
        result[i] = lhs[i];
    }

    // Append characters from rhs to result
    for (int i = 0; i < rhs_length && (i + lhs_length) < result_length; ++i) {
        result[i + lhs_length] = rhs[i];
    }

    // Null-terminate the result
    result[result_length] = 0;

    return result;
}

// Equality operator for comparing strings
bool String::operator==(const String& rhs) const {
    int index = 0;

    // Compare characters until null character or difference found
    while (str[index] != 0 && rhs.str[index] != 0 && str[index] == rhs.str[index]) {
        ++index;
    }

    // Return true if both strings are at end (reached null terminator)
    return (str[index] == rhs.str[index]);
}

// Equality operator for comparing char and string
bool operator==(char lhs, const String& rhs) {
    return String(lhs) == rhs;
}

// Less than operator for comparing strings
bool String::operator<(const String& rhs) const {
    int index = 0;

    // Compare characters until null character or difference found
    while (str[index] != 0 && rhs.str[index] != 0 && str[index] == rhs.str[index]) {
        ++index;
    }
    
    // Return comparison result
    return (str[index] < rhs.str[index]);
}

// Less than operator for comparing char array and string
bool operator<(const char lhs[], const String& rhs) {
    return String(lhs) < rhs;
}

// Less than operator for comparing char and string
bool operator<(char ch, const String& rhs) {
    return String(ch) < rhs;
}

// Substring function: Extracts a substring of the string
String String::substr(int start, int end) const {
    if (start < 0)
        start = 0;
    else if (end < 0)
        return "";
    else if (start >= length())
        return "";
    else if (end >= length())
        end = length() - 1;
    else if (start > end)
        return "";

    // Create result string and copy characters from start to end
    String result;
    for (int i = start; i < end; ++i) {
        result += str[i];
    }

    return result;
}

// Find character function: Finds the first occurrence of a character
int String::findch(int start, char ch) const {
    if (start < 0)
        start = 0;
    else if (start >= length())
        return -1;
    
    // Search for character starting from the specified position
    for (int i = start; i < length(); ++i) {
        if (str[i] == ch)
            return i;
    }

    return -1;  // Character not found
}

// Find string function: Finds the first occurrence of a string
int String::findstr(int find_length, const String& rhs) const {
    String temp = substr(find_length, length());
    char looking_for = rhs[0];
    int found_at = 0;

    // Search for the first character of rhs
    for (int i = 0; i < temp.length(); ++i) {
        if (temp[i] != looking_for) {
            found_at = -1;
            ++i;
        }

        if (temp[i] == looking_for) {
            found_at = i;
            break;
        }
    }

    // Check if the rest of rhs matches
    for (int i = found_at; i < rhs.length(); ++i) {
        if (temp[i] != rhs[i - found_at])
            found_at = -1;
    }

    return found_at;
}

// Input operator: Reads a string from input stream
std::istream& operator>>(std::istream& in, String& rhs) {
    char buff[STRING_SIZE];

    // Read characters into buffer
    if (!in.eof()) {
        in.getline(buff, STRING_SIZE);
        rhs = String(buff);
    } else {
        rhs = String();
    }

    return in;
}

// Output operator: Writes a string to output stream
std::ostream& operator<<(std::ostream& out, const String& rhs) {
    int loopv = 0;

    // Output characters until null character
    while (rhs.str[loopv] != 0) {
        out << rhs.str[loopv];
        ++loopv;
    }

    return out;
}

// Less than or equal to operator for comparing strings
bool operator<=(const String& lhs, const String& rhs) {
    return ((lhs < rhs) || (lhs == rhs)) && !(lhs > rhs);
}

// Not equal to operator for comparing strings
bool operator!=(const String& lhs, const String& rhs) {
    return (lhs > rhs) || (lhs < rhs);
}

// Greater than or equal to operator for comparing strings
bool operator>=(const String& lhs, const String& rhs) {
    return (lhs > rhs) || (lhs == rhs) && !(lhs < rhs);
}

// Greater than operator for comparing strings
bool operator>(const String& lhs, const String& rhs) {
    return !(lhs < rhs) && !(lhs == rhs);
}