//  String class test program
//
//  Tests: Input
//

#include "string.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

int main() {
    std::ifstream inFile("input_test.txt");
    
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    String line;
    while (inFile >> line) {
        std::cout << line << std::endl;
    }
    
    inFile.close();
    std::cout << "Done testing input operator" << std::endl;
    return 0;
}