//  String class test program
//
//  Tests: Input
//

#include "string.hpp"
#include <cassert>
#include <fstream>

//===========================================================================
int main () {
    std::ifstream inFile;
    inFile.open("input_test.txt");
    
    char line[STRING_SIZE];
    while(inFile.getline(line, STRING_SIZE)) {
        String one(line);
        std::cout << one << std::endl;
    }
    
    inFile.close();
    std::cout << "Done testing input operator" << std::endl;
}