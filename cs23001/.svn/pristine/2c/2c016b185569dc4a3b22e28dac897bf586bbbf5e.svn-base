/**
   * Austin  Sternberg
   * fileio
   * cs23001
   */

//This file contains the code to read data & text provided and output them in a speficied way

#include <iostream>
#include <fstream>

//prototypes
void fileio_read();
void fileio_data_math();

int main() {
    fileio_read();
    std::cout << std::endl;
    fileio_data_math();
    return 0;
}

//take text file and break into seperate words per line
void fileio_read() {
    std::ifstream file ("fileio-text.txt");

    if(!file.is_open()) 
        std::cout << "Unable to open file" << std::endl;
    
    else {
        char ch;
        file.get(ch);

        //loop through till end of file
        while(!file.eof()){
            //if whitespace is found, start new line
            if (ch != ' ')
                std::cout << ch;
            //otherwise print word
            else
                std::cout << std::endl;
            file.get(ch);
        }

        file.close();
    }
}

//take numbers as input and add across lines
void fileio_data_math() {
    std::ifstream file ("fileio-data-1.txt");

    if(!file.is_open()) 
        std::cout << "Unable to open file" << std::endl;
    
    else {
        int lhs = 0, rhs = 0;
        char ch;
        //interate through till end of file
        while(!file.eof()){
            //set lhs to first value then move to next
            file >> lhs;
            file.get(ch);

            //set rhs to next value then move again
            file >> rhs;
            file.get(ch);

            //final confirmation of not being at the end of the file
            if(!file.eof())
                std::cout << rhs + lhs << std::endl;
        }
    }

    file.close(); 
}