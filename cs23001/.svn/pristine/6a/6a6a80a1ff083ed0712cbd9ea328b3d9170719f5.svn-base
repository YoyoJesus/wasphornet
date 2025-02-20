/**
   * Austin  Sternberg
   * bigint - multiply.cpp
   * cs23001
   */

//This file contains all of the code test that bigint's multiply & file input methods work correctly

#include "bigint.hpp"

int main() {
     //open provided file
    std::ifstream in("data1-2.txt");
    if(!in) { //if file opening failes, alert user and exit program
        std::cerr << "Could not open data1-2.txt" <<std::endl;
        exit(1);
    }

    bigint one;
    bigint two;

    //iterate through the given values in the text file
    while(in >> one && in >> two) {
        //print the initial values of the first two values in the text file
        std::cout << "First Bigint: " << one << std::endl;
        std::cout << "Second Bigint: "  << two << std::endl;

        //add both bigints toghether and print result
        bigint result = one * two;
        std::cout << "Multiplied value of these Bigints: " << result << std::endl;
        std::cout << std::endl;
    }

    in.close();
    return 0;
}