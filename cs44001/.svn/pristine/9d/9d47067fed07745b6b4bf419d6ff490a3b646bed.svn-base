// Lab01 - Diff
// This program compares two files line by line and outputs the differences
// The differences are marked by a '^' character under the first differing character
// 1/17/2025
// Austin Sternberg

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

// Function Prototypes
std::ifstream openFile(const char*);
int compare(const std::string&, const std::string&);
void printCaret(const std::string&, const std::string&, const std::string&, int);
void compareFiles(std::ifstream&, std::ifstream&, const char*, const char*);

int main(int argc, char* argv[]) {
    // Check if the program is invoked with the correct arguments
    if (argc != 3) {
        std::cout << "Error! Please invoke program with 2 arguments." << std::endl;
        return 1;
    }

    // Open the files using the openFile function
    std::ifstream file1 = openFile(argv[1]);
    std::ifstream file2 = openFile(argv[2]);

    // Compare the files
    compareFiles(file1, file2, argv[1], argv[2]);

    return 0;
}

// Function to open a file and check for errors
std::ifstream openFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error! Could not open file: " << filename << std::endl;
        exit(1); // Exit if the file cannot be opened
    }
    return file;
}

// Function to compare two strings character-by-character
int compare(const std::string& line1, const std::string& line2) {
    int len = std::min(line1.length(), line2.length());
    for (int i = 0; i < len; i++) {
        if (line1[i] != line2[i]) return i;
    }
    // If one line is longer, consider the first differing position as the length of the shorter line
    if (line1.length() != line2.length()) return len;
    return -1; // Lines are identical
}

// Function to print the caret for the first difference
void printCaret(const std::string& text1, const std::string& text2, const std::string& filename, int lineCount) {

    // Print the caret after the lines are displayed
    int space = (filename.length() + std::to_string(lineCount).length() + 4);
    for (int i = 0; i < space; ++i) { //It proved way easier to do a loop than try and calculate the number of spaces needed
        std::cout << " ";
    }

    // Loop to print spaces until the first mismatch
    for (int i = 0; text1[i] == text2[i] && i < std::min(text1.length(), text2.length()); ++i) {
        std::cout << " ";
    }

    // Print the caret
    std::cout << "^" << std::endl;
}

// Function to compare two files line-by-line
void compareFiles(std::ifstream& file1, std::ifstream& file2, const char* file1Name, const char* file2Name) {
    
    int lineCount = 1;
    while (!file1.eof() || !file2.eof()) {
        
        std::string text1, text2;

        // Handle end-of-file for either file
        if (file1.eof()) {
            text1 = "";
        }
        if (file2.eof()) {
            text2 = "";
        }

        // Read lines from both files
        std::getline(file1, text1);
        std::getline(file2, text2);

        // If the lines are different, print them and the caret
        if (text1 != text2) {
            std::cout << file1Name << ": " << lineCount << ": " << text1 << std::endl;
            std::cout << file2Name << ": " << lineCount << ": " << text2 << std::endl;

            // Print the caret showing where the lines differ
            printCaret(text1, text2, file1Name, lineCount);
        }

        ++lineCount;
    }
}
