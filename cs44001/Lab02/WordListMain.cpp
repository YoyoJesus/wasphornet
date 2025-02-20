#include "WordList.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

std::ifstream openFile(const char* filename);
std::string cleanWord(const std::string& word);

int main(int argc, char* argv[]) {
    // Check if the program is invoked with the correct arguments
    if (argc != 2) {
        std::cout << "Error! Please invoke program with 1 argument." << std::endl;
        return 1;
    }

    // Open the file using the openFile function
    std::ifstream file = openFile(argv[1]);

    WordList wordList;

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        std::string cleanedWord;
        for (char c : line) {
            if (!std::isspace(c) && !std::ispunct(c)) {
                cleanedWord += c;
            } else if (!cleanedWord.empty()) {
                wordList.addWord(cleanedWord);
                cleanedWord.clear();
            }
        }
        if (!cleanedWord.empty()) {
            wordList.addWord(cleanedWord);
        }
    }

    // Print the WordList object
    wordList.print();

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
